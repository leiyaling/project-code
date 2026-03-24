#include "common.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(test_common, get_rboard_test_current_exist_resource_path)
{
    std::string lineSave{"test_save_pcb.redpcb"};
    const std::string resourcePath{__FILE__};
    std::filesystem::path resouceDir{resourcePath};
    resouceDir = resouceDir.parent_path() / "data";

    std::filesystem::path expectTestPath{resouceDir / lineSave};
    expectTestPath.make_preferred();

    auto lineSavePath =
        test_board::getRBoardTestCurrentExistResourcePath(lineSave);
    EXPECT_STRCASEEQ(expectTestPath.string().c_str(),
                     lineSavePath.string().c_str());
    std::cout << lineSave << " resoucePath:" << lineSavePath << '\n';

    const std::string tmpFilePath{"abcdefcghijk"};
    auto tmpFileResoucePath =
        test_board::getRBoardTestCurrentExistResourcePath(tmpFilePath);
    EXPECT_STRCASEEQ("", tmpFileResoucePath.string().c_str());
    std::cout << tmpFilePath << " resoucePath:" << tmpFileResoucePath << '\n';
}

TEST(test_common, get_rboard_test_resource_path)
{
    std::string tmpFilePath{"abcdefcghijk"};
    const std::string resourcePath{__FILE__};
    std::filesystem::path resouceDir{resourcePath};
    resouceDir = resouceDir.parent_path() / "data";

    std::filesystem::path expectTestPath{resouceDir / tmpFilePath};
    expectTestPath.make_preferred();

    auto tmpFileResoucePath =
        test_board::getRBoardTestResourcePath(tmpFilePath);
    EXPECT_STRCASEEQ(expectTestPath.string().c_str(),
                     tmpFileResoucePath.string().c_str());
    std::cout << tmpFilePath << " resoucePath:" << tmpFileResoucePath << '\n';

    const std::string emptyFilePath{""};
    auto emptyFileResoucePath =
        test_board::getRBoardTestResourcePath(emptyFilePath);
    EXPECT_STRCASEEQ("", emptyFileResoucePath.string().c_str());
    std::cout << emptyFilePath << " resoucePath:" << emptyFileResoucePath << '\n';
}