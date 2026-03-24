#include "rededa/board/loader/pcb_loader.h"
#include "../board.h"
#include "../board_controller.h"
#include <regex>
#include <filesystem>
#include <iostream>

namespace rededa
{
// RIDesignLoader::~RIDesignLoader() = default;
// RIDesignLoader::RIDesignLoader() = default;
RPcbLoader::RPcbLoader() : mDesignExtension(std::string{"redpcb"})
{
    mDesignID = -1;
}

RPcbLoader::~RPcbLoader()
{
}

std::shared_ptr<RIDesign> RPcbLoader::newDesign(std::string aPath)
{
    auto &controller = RBoardController::instance();
    auto pcbDesign = controller.create();
    pcbDesign -> setBoardPath(aPath);
    pcbDesign -> setBoardProduct(BoardProduct::REDPCB);
    pcbDesign -> setBoardMode(BoardMode::PCB);
    if(!pcbDesign -> save(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    if(!pcbDesign -> open(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    pcbDesign -> setUp();
    return pcbDesign;
}

std::shared_ptr<RIDesign> RPcbLoader::load(std::string aPath)
{
    auto &controller = RBoardController::instance();
    auto pcbDesign = controller.create();
    pcbDesign -> setBoardPath(aPath);
    pcbDesign -> setBoardProduct(BoardProduct::REDPCB);
    pcbDesign -> setBoardMode(BoardMode::PCB);
    if(!pcbDesign -> open(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    pcbDesign -> setUp();
    return pcbDesign;
}

std::string RPcbLoader::getExtension() const
{
    return mDesignExtension;
}

bool RPcbLoader::removeDesign(std::shared_ptr<RIDesign> aDesign)
{
    auto isClosed = aDesign -> close();
    if(isClosed)
    {
        auto &controller = RBoardController::instance();
        auto board = std::dynamic_pointer_cast<RBoard>(aDesign);
        if(board)
        {
            controller.destroy(board -> handle());
        }
    }
    return isClosed;
}

bool RPcbLoader::pathCheck(const std::string &aPath)
{
    std::filesystem::path path(aPath);
    std::regex illegalPattern(R"([<>\"/\\|?*])");
    for(const auto& node : path)
    {
        if(node.string().compare("\\") !=0 && std::regex_search(node.string(), illegalPattern))
        {
            return false;
        }
    }
    return true;
}

bool RPcbLoader::extensionCheck(const std::string &aPath)
{
    std::regex extensionPattern(R"(\.)" + mDesignExtension + R"($)",
                                std::regex_constants::icase);
    return std::regex_search(aPath, extensionPattern);
}

} // namespace rededa