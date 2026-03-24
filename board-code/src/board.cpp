#include "board.h"
#include "rededa/board/error.h"
#include "board_controller_log.h"
#include "rededa_layer_manager/api/ilayermanager.h"
#include "rededa_layer_manager/data/layermanager.h"

#include <regex>
#include <iostream>
namespace rededa
{
std::function<int(int)> RBoard::mCallback = {};
std::function<void(bool)> RBoard::mCloseCallback = {};

RBoard::RBoard(rhandle_t handle)
    : mHandle(handle),
      mBoardAssemble(std::make_unique<BoardAssemble>()),
      mData({600, 500, 1, 1, 2, "mm", "nullpath"}),
      mName("default"),
      mMode(BoardMode::PKG),
      mProduct(BoardProduct::REDPKG),
      mBoardFileDAO(std::make_unique<RBoardFileDao>())
{
}
// rerror_t RBoard::api(int param1, int *param2)
// {
//   auto &log = getRBoardLogger();
//   log.info("RBoard::api");
//   return 0;
// }

void RBoard::setUp()
{
    // 装配
    mBoardAssemble->assemble();
    mBoardAssemble->createModuleConnection();
    if(mCallback)
    {
        rededa::RLoggerWrapper l{"boardCallbackTest"};
        l.info("callback start");
        auto callbackResult = mCallback(mHandle);
        auto result = "callback result: " + std::to_string(callbackResult);
        l.info(result.c_str());
        l.info("callback end");
    }
    // mData.accuracy = 1;
    // mData.height = 500;
    // mData.width = 600;
    // mData.originX = 1;
    // mData.originY = 2;
    // mData.unitName = "mm";
    // mData.path = "nullpath";
}

const BoardData &RBoard::getBoardData() const
{
    return mData;
}

int RBoard::getLayerManagerID() const
{
    return mBoardAssemble->getLayerManagerID();
}

int RBoard::getColorManagerID() const
{
    // return mBoardAssemble->getColorManagerID();
    return -1;
}

int RBoard::getItemHolderID() const
{
    return mBoardAssemble->getItemHolderID();
}

int RBoard::getViaListID() const
{
    // return mBoardAssemble->getViaListID();
    return -1;
}

int RBoard::getDrawLineID() const
{
    return mBoardAssemble->getDrawLineMachineID();
}

int RBoard::getSelectionID() const
{
    return mBoardAssemble->getSelectionID();
}

int rededa::RBoard::getDrawComplexCopperMachineID() const
{
    return mBoardAssemble->getDrawComplexCopperMachineID();
}

int rededa::RBoard::getStateDrawComplexCopperID() const
{
    return mBoardAssemble->getStateDrawComplexCopperID();
}

std::shared_ptr<RLayerManager> RBoard::getLayerManager() const
{
    return mBoardAssemble->getLayerManager();
}

const std::string &RBoard::getBoardName() const
{
    return mName;
}

void RBoard::setBoardData(const BoardData &aBoardData)
{
    mData = aBoardData;
    mIsDataChanged = true;
}

void RBoard::setBoardPath(const std::string &aBoardPath)
{
    mData.path = aBoardPath;
    mIsDataChanged = true;
}

void RBoard::setBoardName(const std::string &name)
{
    mName = name;
}

void RBoard::setBoardMode(const BoardMode &aBoardMode)
{
    mMode = aBoardMode;
}

void RBoard::setBoardProduct(const BoardProduct &aBoardProduct)
{
    mProduct = aBoardProduct;
}

void RBoard::registCallback(int (*callback)(int))
{
    mCallback = callback;
}

void RBoard::registCloseCallback(void (*closeCallback)(bool))
{
    mCloseCallback = closeCallback;
}

//返回当前文件路径
const std::string &RBoard::getBoardFileName() const
{
    return mData.path;
}

const RenderPointer RBoard::getRenderPtr() const
{
    RenderPointer render;
    render.mScene = static_cast<void *>(mBoardAssemble->getScenePtr());
    render.mContext = static_cast<void *>(mBoardAssemble->getContextPtr());
    render.mTransform = static_cast<void *>(mBoardAssemble->getTransformPtr());
    render.msurface = static_cast<void *>(mBoardAssemble->getSurfacePtr());
    render.mRender = static_cast<void *>(mBoardAssemble->getRenderPtr());
    // render.mScene = nullptr;
    // render.mContext = nullptr;
    // render.mTransform = nullptr;
    // render.msurface = nullptr;
    // render.mRender = nullptr;
    return render;
}

int RBoard::getSettingID() const
{
    return mBoardAssemble->getSettingID();
}

bool RBoard::checkBoardDefault() const
{
    return mIsDefaultBoard;
}

bool RBoard::checkBoardSaved() const
{
    return !mIsDataChanged;
}

BoardMode RBoard::getBoardMode() const
{
    return mMode;
}

BoardProduct RBoard::getBoardProduct() const
{
    return mProduct;
}

bool RBoard::save(const std::string &aPath)
{
    auto &logger = getRBoardLogger();
    // if(!mBoardAssemble || !mBoardFileDAO)
    // {
    //     return false;
    // }
    if(!mBoardFileDAO)
    {
        return false;
    }
    // auto itemHolder = mBoardAssemble -> getItemHolder();
    // if(!itemHolder)
    // {
    //     return false;
    // }
    auto fileName = getPathFileName(aPath);
    mBoardFileDAO -> setPath(aPath);
    mBoardFileDAO -> setName(fileName);
    mBoardFileDAO -> setBoardData(mData);
    mBoardFileDAO -> setMode(mMode);
    auto callback = [&](const std::string& path){
        logger.info("Assemble save start");
        // mBoardAssemble->setPath(path);
        // mBoardAssemble->getItemHolder()->save();
        logger.info("Assemble save end");
    };
    if(!mBoardFileDAO -> save(callback))
    {
        return false;
    }
    mData.path = aPath;
    mName = fileName;
    return true;
}

bool RBoard::open(const std::string &aPath)
{
    auto& logger = getRBoardLogger();
    // // if(!mBoardAssemble || !mBoardFileDAO)
    // // {
    // //     return false;
    // // }
    if(!mBoardFileDAO)
    {
        return false;
    }
    auto fileName = getPathFileName(aPath);
    mBoardFileDAO -> setPath(aPath);
    mBoardFileDAO -> setName(fileName);
    mBoardFileDAO -> setMode(mMode);
    // auto itemHolder = mBoardAssemble -> getItemHolder();
    // if(!itemHolder)
    // {
    //     return false;
    // }
    auto callback = [&](const BoardData &boardData, const std::string& itemHolderPath){
        logger.info("Assemble load start");
        // mBoardAssemble -> setPath(itemHolderPath);
        // mBoardAssemble -> getItemHolder() -> load();
        logger.info("Assemble load end");
        mData = boardData;
    };
    if(!mBoardFileDAO -> load(callback))
    {
        return false;
    }
    mName = fileName;
    mData.path = aPath;
    return true;
}

bool RBoard::rename(const std::string &aNewName)
{
    mName.assign(aNewName);
    if(mName.compare(aNewName) != 0)
    {
        return false;
    }
    return true;
}

std::shared_ptr<IRSettings> RBoard::getSettingModel()
{
    return std::shared_ptr<IRSettings>();
}

bool rededa::RBoard::close()
{
    if(mIsDataChanged)
    {
        if(mCloseCallback)
        {
            mCloseCallback(false);
        }
        return false;
    }
    return true;
}

std::string RBoard::name()
{
    return mName;
}

std::string RBoard::getPathFileName(const std::string& aPath)
{
    std::regex pattern(R"(([^/\\]+)\.[^/\\]+$)");
    std::smatch match;
    if(std::regex_search(aPath, match, pattern))
    {
        return match[1].str();
    }
    return "";
}

bool RBoard::extensionCheck(const std::string &aPath)
{
    std::regex pattern(R"(\.([^/\\]+)$)");
    std::smatch match;
    if(std::regex_search(aPath, match, pattern))
    {
        auto extension = match[1].str();
        if(extension.compare("redpcb") == 0 && mProduct == BoardProduct::REDPCB)
        {
            return true;
        }
        if(extension.compare("redpkg") == 0 && mProduct == BoardProduct::REDPKG)
        {
            return true;
        }
        std::cout << "extension:" << extension;
    }
    return false;
}

void RBoard::testRLog() const
{
    rededa::RLoggerWrapper l{"boardTest"};
    auto e = l.acquireLogger();
    l.info("error code {}", e);
    l.log(0, "hello 0");
    l.log(1, "hello 1");
    l.log(2, "hello 2");
    l.log(3, "hello 3");
    l.log(4, "hello 4");
    l.log(5, "hello 5");
    l.log(6, "hello 6");
    // 默认的 log 级别会 打印 bad_alloc 错误
    l.log(7, "hello 7");

    // debug trace debug 模式下不能使用
    l.debug("hello debug!");
    l.trace("hello trace");

    l.info("hello info!");
    l.warn("hello warn");
    l.fatal("hello fatal");
    l.error("hello err");
}
}