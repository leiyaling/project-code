#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include "board.h"
#include <rededa/board/board_c.h>
#include "board_controller.h"
#include "common.h"
// #include "board_controller_log.h"

#include "project_manager/inc/project_manager.h"
#include "project_manager/inc/project_manager_c_interface.h"

using namespace rededa;

class RBoardTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
    static std::vector<rhandle_t> mIDs;
    // RBoard logic{1};
};

std::vector<rhandle_t> RBoardTest::mIDs = {};

TEST_F(RBoardTest, board_regist_callback)
{
    auto callback = [](int handle)
    {
        std::cout << "test callback: " << handle << std::endl;
        return 0;
    };
    EXPECT_EQ(board_regist_callback(callback), BOARD_ERROR_CODE1);
    EXPECT_EQ(board_regist_callback(nullptr), BOARD_ERROR_CODE4);
}

TEST_F(RBoardTest, board_regist_close_callback)
{
    auto callback = [](bool aResult)
    {
        if(aResult)
        {
            std::cout << "exit" << std::endl;
        }
        else
        {
            std::cout << "file not saved" << std::endl;
        }
    };
    EXPECT_EQ(board_regist_close_callback(callback), BOARD_ERROR_CODE1);
    EXPECT_EQ(board_regist_close_callback(nullptr), BOARD_ERROR_CODE4);
}

TEST_F(RBoardTest, board_new)
{
    auto secondID = board_new("pathSecond", "nameSecond", BoardMode::PKG);
    std::cout << "path new test:" << board_get_current_file_path(secondID) << std::endl;
    EXPECT_EQ(secondID, mIDs.size() + 1);
    ASSERT_STREQ(board_get_data(secondID).path, "pathSecond\\nameSecond");
    ASSERT_STREQ(board_get_data(secondID).boardName, "nameSecond");
    ASSERT_EQ(board_check_project_type(secondID), BoardMode::PKG);
    mIDs.push_back(secondID);
    EXPECT_TRUE(!mIDs.empty());
    // std::cout << board_get_current_file_path(secondID) << std::endl;
}

TEST_F(RBoardTest, board_get_data)
{
    EXPECT_TRUE(!mIDs.empty());
    for (auto &id : mIDs)
    {
        auto boardData = board_get_data(id);
        std::string boardName{"board"};
        boardName.append(std::to_string(id));
        EXPECT_EQ(boardData.width, 600);
        EXPECT_EQ(boardData.height, 500);
        EXPECT_EQ(boardData.accuracy, 1);
        EXPECT_EQ(boardData.originX, 1);
        EXPECT_EQ(boardData.originy, 2);
        ASSERT_STREQ(boardData.boardName, "nameSecond");
        ASSERT_STREQ(boardData.unitName, "mm");
        ASSERT_STREQ(boardData.path, "pathSecond\\nameSecond");

        // board assemble 未装配
        // EXPECT_LE(boardData.moduleID.layerID, 0);
        EXPECT_LE(boardData.moduleID.colorID, 0);
        // EXPECT_LE(boardData.moduleID.itemHolderID, 0);
        EXPECT_LE(boardData.moduleID.vialistID, 0);

        EXPECT_GT(boardData.moduleID.layerID, 0);
        // EXPECT_GT(boardData.moduleID.colorID, 0);
        EXPECT_GT(boardData.moduleID.itemHolderID, -1);
        // EXPECT_GT(boardData.moduleID.vialistID, 0);
        EXPECT_GT(boardData.moduleID.selectionID, -1);

        // // board assemble 未装配
        // EXPECT_TRUE(boardData.moduleID.renderID.mScene == nullptr);
        // EXPECT_TRUE(boardData.moduleID.renderID.mContext == nullptr);
        // EXPECT_TRUE(boardData.moduleID.renderID.mTransform == nullptr);
        // EXPECT_TRUE(boardData.moduleID.renderID.msurface == nullptr);
        // EXPECT_TRUE(boardData.moduleID.renderID.mRender == nullptr);

        EXPECT_TRUE(boardData.moduleID.renderID.mScene != nullptr);
        EXPECT_TRUE(boardData.moduleID.renderID.mContext != nullptr);
        EXPECT_TRUE(boardData.moduleID.renderID.mTransform != nullptr);
        EXPECT_TRUE(boardData.moduleID.renderID.msurface != nullptr);
        EXPECT_TRUE(boardData.moduleID.renderID.mRender != nullptr);

        // board settings 未装配
        // EXPECT_LE(boardData.moduleID.stateID.drawLineID, 0);
        // EXPECT_LE(boardData.moduleID.settingsID.level0, 0);
        // EXPECT_LE(boardData.moduleID.settingsID.level1, 0);
        // EXPECT_LE(boardData.moduleID.settingsID.level2, 0);
        // EXPECT_LE(boardData.moduleID.settingsID.level3, 0);

        EXPECT_GT(boardData.moduleID.stateID.drawComplexCopperID, -1);
        EXPECT_GT(boardData.moduleID.stateID.drawComplexCopperStateID, -1);
        EXPECT_GT(boardData.moduleID.stateID.drawLineID, -1);
        EXPECT_GT(boardData.moduleID.settingsID.level0, 0);
        // EXPECT_GT(boardData.moduleID.settingsID.level1, 0);
        // EXPECT_GT(boardData.moduleID.settingsID.level2, 0);
        // EXPECT_GT(boardData.moduleID.settingsID.level3, 0);
    }
    EXPECT_EQ(board_get_data(0).boardName, nullptr);
    EXPECT_EQ(board_get_data(-1).boardName, nullptr);
}

TEST_F(RBoardTest, board_save)
{
    EXPECT_TRUE(!mIDs.empty());
    for (auto &id : mIDs)
    {
        EXPECT_EQ(board_save(id), BOARD_ERROR_CODE5);
    }
    EXPECT_EQ(board_save(0), BOARD_ERROR_CODE2);
    EXPECT_EQ(board_save(-1), BOARD_ERROR_CODE2);
}

TEST_F(RBoardTest, board_get_current_file_path)
{
    std::string filename = __FILE__;
    for (auto &id : mIDs)
    {
        ASSERT_STREQ(board_get_data(id).path, "pathSecond\\nameSecond");
        const char *result = board_get_current_file_path(id);
        ASSERT_STREQ(result, "pathSecond\\nameSecond");
    }
    ASSERT_STREQ(board_get_current_file_path(-1), "");
    ASSERT_STREQ(board_get_current_file_path(0), "");
}

TEST_F(RBoardTest, board_load)
{
    EXPECT_TRUE(!mIDs.empty());
    for (auto &id : mIDs)
    {
        std::cout << "board id:" << id << std::endl;
        EXPECT_EQ(board_load(id), BOARD_ERROR_CODE5);
    }
    EXPECT_EQ(board_load(0), BOARD_ERROR_CODE2);
    EXPECT_EQ(board_load(-1), BOARD_ERROR_CODE2);
}

TEST_F(RBoardTest, board_check_project_type)
{
    EXPECT_TRUE(!mIDs.empty());
    for (auto &id : mIDs)
    {
        EXPECT_EQ(board_check_project_type(id), BoardMode::PKG);
        // EXPECT_EQ(board_set_path(id, "test.redpkg"), 0);
        // EXPECT_EQ(board_check_project_type(id), 2);
        // EXPECT_EQ(board_set_path(id, "test.json"), 0);
        // EXPECT_EQ(board_check_project_type(id), 0);
        // EXPECT_EQ(board_set_path(id, ""), 0);
        // EXPECT_EQ(board_check_project_type(id), 0);
    }
    EXPECT_EQ(board_check_project_type(0), BoardMode::INVALID_TYPE);
    EXPECT_EQ(board_check_project_type(-1), BoardMode::INVALID_TYPE);
}

TEST_F(RBoardTest, board_release)
{
    for (auto &id : mIDs)
    {
        board_release(id);
        EXPECT_EQ(board_load(id), BOARD_ERROR_CODE2);
    }
}

TEST_F(RBoardTest, board_regist_designloader)
{
    EXPECT_TRUE(board_regist_designloader(BoardMode::PKG));
    EXPECT_TRUE(board_regist_designloader(BoardMode::PCB));
    EXPECT_FALSE(board_regist_designloader(BoardMode::EDIT_COPPER));
    RProjectManager &manager = RProjectManager::getInstance();
    auto loaders = manager.getLoaders();
    auto newPathPCB = test_board::getRBoardTestResourcePath("pcb.redpcb");
    auto newPathPKG = test_board::getRBoardTestResourcePath("pkg.redpkg");
    auto loadPathPCB = test_board::getRBoardTestCurrentExistResourcePath("test_save_pcb.redpcb");
    auto loadPathPKG = test_board::getRBoardTestCurrentExistResourcePath("test_save_pkg.redpkg");
    for(auto &loader : loaders)
    {
        if(loader->getExtension() == "redpkg")
        {
            auto design = loader -> newDesign(newPathPKG.string());
            if(!design)
            {
                continue;
            }
            std::cout << design -> name() << std::endl;
            loader -> load(loadPathPKG.string());
            std::cout << loader->getExtension() << std::endl;
        }
        if(loader->getExtension() == "redpcb")
        {
            auto design = loader -> newDesign(newPathPCB.string());
            if(!design)
            {
                continue;
            }
            std::cout << design -> name() << std::endl;
            loader -> load(loadPathPCB.string());
            std::cout << loader->getExtension() << std::endl;
        }
    }
    // EXPECT_TRUE(manager.getTempDesign(newPathPCB.string()) != nullptr);
    // EXPECT_TRUE(manager.getTempDesign(newPathPKG.string()) != nullptr);
    char* output = (char*)malloc(1024 * sizeof(char));
    int size = 1024;
    auto j = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/a.redpcb"]})", nullptr, &size);
    auto i = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/a.redpcb"]})", output, &size);
    j = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/a.redpcb"]})", nullptr, &size);
    auto k = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/b.redpcb"]})", output, &size);
    j = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/a.redpkg"]})", nullptr, &size);
    auto l = project_manager_exec(5, R"({"parameters": ["C:/Users/Jasonqiu/redproject/rededa_board/test/data/c.redpkg"]})", output, &size);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 0);
    EXPECT_EQ(k, 0);
    EXPECT_EQ(l, 0);
    // manager.getTempDesign(newPathPKG.string());

    // manager.createDesign("a/a", newPathPCB.string());
    // manager.createDesign("a/a", newPathPKG.string());
}

// TEST_F(RBoardTest, smoking) {
//     ASSERT_EQ(logic.api(1, nullptr), 0);
// }