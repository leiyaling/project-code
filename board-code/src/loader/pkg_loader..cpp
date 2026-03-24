#include "rededa/board/loader/pkg_loader.h"
#include "../board.h"
#include "../board_controller.h"

#include <regex>
#include <filesystem>
#include <iostream>

namespace rededa
{
// RIDesignLoader::~RIDesignLoader()=default;
// RIDesignLoader::RIDesignLoader()=default;
RPkgLoader::RPkgLoader() : mDesignExtension(std::string{"redpkg"})
{
    mDesignID = -1;
}

RPkgLoader::~RPkgLoader()
{
}

std::shared_ptr<RIDesign> RPkgLoader::newDesign(std::string aPath)
{
    auto &controller = RBoardController::instance();
    auto pkgDesign = controller.create();
    pkgDesign -> setBoardPath(aPath);
    pkgDesign -> setBoardProduct(BoardProduct::REDPKG);
    pkgDesign -> setBoardMode(BoardMode::PKG);
    if(!pkgDesign -> save(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    if(!pkgDesign -> open(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    pkgDesign -> setUp();
    return pkgDesign;
}

std::shared_ptr<RIDesign> RPkgLoader::load(std::string aPath)
{
    auto &controller = RBoardController::instance();
    auto pkgDesign = controller.create();
    pkgDesign -> setBoardPath(aPath);
    pkgDesign -> setBoardProduct(BoardProduct::REDPKG);
    pkgDesign -> setBoardMode(BoardMode::PKG);
    if(!pkgDesign -> open(aPath))
    {
        return std::shared_ptr<RIDesign>();
    }
    pkgDesign -> setUp();
    return pkgDesign;
}

std::string RPkgLoader::getExtension() const
{
    return mDesignExtension;
}

bool RPkgLoader::removeDesign(std::shared_ptr<RIDesign> aDesign)
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

bool RPkgLoader::pathCheck(const std::string &aPath)
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

bool RPkgLoader::extensionCheck(const std::string &aPath)
{
    std::regex extensionPattern(R"(\.)" + mDesignExtension + R"($)",
                                std::regex_constants::icase);
    return std::regex_search(aPath, extensionPattern);
}
}