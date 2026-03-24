


#include "rededa/board/board_c.h"
#include "rededa/board/error.h"
#include "rededa/board/loader/pcb_loader.h"
#include "rededa/board/loader/pkg_loader.h"
#include "project_manager/inc/project_manager.h"

#include "board_controller.h"
#include "board.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <regex>
#include <iostream>

using namespace rededa;

REDEDA_BOARD_API void board_release(rhandle_t handle)
{
    auto& ctrl = RBoardController::instance();
    ctrl.destroy(handle);
}

REDEDA_BOARD_API CBoardData board_get_data(rhandle_t handle)
{
    auto& ctrl = RBoardController::instance();
    auto board = ctrl.get(handle);
    if (board)
    {
        auto rBoard = std::dynamic_pointer_cast<RBoard>(board);
        if(rBoard)
        {
            auto &data = rBoard->getBoardData();
            auto layerID = rBoard->getLayerManagerID();
            auto colorID = rBoard->getColorManagerID();
            auto itemHolderID = rBoard->getItemHolderID();
            auto vialistID = rBoard->getViaListID();
            auto drawLineID = rBoard->getDrawLineID();
            auto selectionID = rBoard->getSelectionID();
            auto drawComplexCopperID = rBoard->getDrawComplexCopperMachineID();
            auto drawComplexCopperStateID = rBoard->getStateDrawComplexCopperID();
            auto renderPtrs = rBoard->getRenderPtr();
            auto &boardName = rBoard->getBoardName();
            auto settingID = rBoard->getSettingID();
            CRenderStruct renderStruct = {renderPtrs.mScene, renderPtrs.mContext,
                                          renderPtrs.mTransform,
                                          renderPtrs.msurface, renderPtrs.mRender};
            CStateID stateID = {drawLineID, drawComplexCopperID, drawComplexCopperStateID};
            CSettingsID settingsID = {settingID,-1, -1, -1};
            CBoardModuleID boardModuleID = {layerID,   colorID,      itemHolderID,
                                            vialistID, selectionID, renderStruct, stateID,
                                            settingsID};
            // TODO michael: 需要完善
            return {boardModuleID,     data.width,
                    data.height,       data.accuracy,
                    data.originX,      data.originY,
                    boardName.c_str(), data.unitName.c_str(),
                    data.path.c_str()};
        }
    }
    return {};
}
REDEDA_BOARD_API RBoardErrCode board_load(rhandle_t handle)
{
    auto& ctrl = RBoardController::instance();
    auto board = ctrl.get(handle);
    if(board)
    {
        auto rBoard = std::dynamic_pointer_cast<RBoard>(board);
        if(rBoard)
        {
            auto &path = rBoard -> getBoardFileName();
            if(rBoard -> open(path))
            {
                return BOARD_ERROR_CODE1;
            }
            return BOARD_ERROR_CODE5;
        }
    }
    return BOARD_ERROR_CODE2;
}

REDEDA_BOARD_API RBoardErrCode board_save(rhandle_t handle)
{
    auto& ctrl = RBoardController::instance();
    auto board = ctrl.get(handle);
    if(board)
    {
        auto rBoard = std::dynamic_pointer_cast<RBoard>(board);
        if(rBoard)
        {
            auto &path = rBoard -> getBoardFileName();
            if(rBoard -> save(path))
            {
                return BOARD_ERROR_CODE1;
            }
            return BOARD_ERROR_CODE5;
        }
    }
    return BOARD_ERROR_CODE2;
}

REDEDA_BOARD_API const char *board_get_current_file_path(rhandle_t handle)
{
    std::cout << "get controller" << std::endl;
    auto& ctrl = RBoardController::instance();
    std::cout << "get board" << std::endl;
    auto board = ctrl.get(handle);
    if(board)
    {
        std::cout << "pointer convert" << std::endl;
        auto rBoard = std::dynamic_pointer_cast<RBoard>(board);
        if(rBoard)
        {
            std::cout << "get path" << std::endl;
            auto &boardFileName = rBoard->getBoardFileName();
            if (!boardFileName.empty())
            {
                std::cout << boardFileName.c_str() << std::endl;
                return boardFileName.c_str();
            }
        }
    }
    return "";
}

REDEDA_BOARD_API BoardMode board_check_project_type(rhandle_t handle)
{
    auto& ctrl = RBoardController::instance();
    auto board = ctrl.get(handle);
    if(board)
    {
        auto rBoard = std::dynamic_pointer_cast<RBoard>(board);
        if(rBoard)
        {
            return rBoard -> getBoardMode();
        }
    }
    return BoardMode::INVALID_TYPE;
}

REDEDA_BOARD_API rhandle_t board_new(const char *path, const char *name, BoardMode type)
{
    auto& ctrl = RBoardController::instance();
    auto p = ctrl.create();
    // auto rBoard = std::dynamic_pointer_cast<RBoard>(p);
    auto filePath = std::string(path).append("\\").append(name);
    p -> setBoardPath(filePath);
    p -> setBoardName(name);
    p -> setBoardMode(type);
    p -> setUp();
    return p->handle();
}

REDEDA_BOARD_API RBoardErrCode board_regist_callback(int (*callback)(int))
{
    if(!callback)
    {
        return BOARD_ERROR_CODE4;
    }
    RBoard::registCallback(callback);
    return BOARD_ERROR_CODE1;
}

REDEDA_BOARD_API RBoardErrCode board_regist_close_callback(void (*closeCallback)(bool))
{
    if(!closeCallback)
    {
        return BOARD_ERROR_CODE4;
    }
    RBoard::registCloseCallback(closeCallback);
    return BOARD_ERROR_CODE1;
}

bool board_regist_designloader(BoardMode type)
{
    RProjectManager& manager = RProjectManager::getInstance();
    switch(type)
    {
        case BoardMode::PKG:
        {
            auto pcbLoader = std::make_shared<RPkgLoader>();
            manager.registerLoader(pcbLoader);
            break;
        }
        case BoardMode::PCB:
        {
            auto pkgLoader = std::make_shared<RPcbLoader>();
            manager.registerLoader(pkgLoader);
            break;
        }
        default:
            return false;
            break;
    }
    return true;
}
