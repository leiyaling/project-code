#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "board.h"
#include "board_data.h"
#include "rededa_layer_manager/data/layermanager.h"
#include "common.h"

class BoardTestSuite :public ::testing::Test{

public:
    BoardTestSuite() : mBoard(rededa::RBoard(10)){};
    ~BoardTestSuite() override = default;

protected:
    rededa::RBoard mBoard;

};

TEST_F(BoardTestSuite, InitialState){
    EXPECT_EQ(mBoard.getLayerManagerID(),-1 );
    EXPECT_STREQ(mBoard.name().c_str(),std::string{"default"}.c_str() );
    EXPECT_TRUE(!mBoard.name().empty());
}

TEST_F(BoardTestSuite, save){
    auto savePathPCB = test_board::getRBoardTestResourcePath("test_save_pcb.redpcb");
    auto savePathPKG = test_board::getRBoardTestResourcePath("test_save_pkg.redpkg");
    mBoard.setUp();
    rededa::BoardData bdPCB = {1000, 1200, 1, 2, 3, "cm", "a/a/a.redpcb"};
    rededa::BoardData bdPKG = {2000, 2200, 4, 5, 6, "mm", "a/a/a.redpkg"};
    mBoard.setBoardData(bdPKG);
    // mBoard.setBoardName("testsave");
    EXPECT_FALSE(savePathPCB.empty());
    EXPECT_FALSE(savePathPKG.empty());
    EXPECT_FALSE(mBoard.save(savePathPCB.string()));
    EXPECT_TRUE(mBoard.save(savePathPKG.string()));
    auto boardDataPKG = mBoard.getBoardData();
    EXPECT_STREQ(boardDataPKG.path.c_str(), savePathPKG.string().c_str());
    EXPECT_STREQ(mBoard.name().c_str(), "test_save_pkg");
    mBoard.setBoardMode(BoardMode::PCB);
    mBoard.setBoardData(bdPCB);
    EXPECT_FALSE(mBoard.save(savePathPKG.string()));
    EXPECT_TRUE(mBoard.save(savePathPCB.string()));
    auto boardDataPCB = mBoard.getBoardData();
    EXPECT_STREQ(boardDataPCB.path.c_str(), savePathPCB.string().c_str());
    EXPECT_STREQ(mBoard.name().c_str(), "test_save_pcb");
}

TEST_F(BoardTestSuite, load){
    auto loadPathPCB = test_board::getRBoardTestCurrentExistResourcePath("test_save_pcb.redpcb");
    auto loadPathPKG = test_board::getRBoardTestCurrentExistResourcePath("test_save_pkg.redpkg");
    auto savePathPCB = test_board::getRBoardTestResourcePath("test_save_pcb_1.redpcb");
    auto savePathPKG = test_board::getRBoardTestResourcePath("test_save_pkg_1.redpkg");
    mBoard.setUp();
    mBoard.setBoardMode(BoardMode::PKG);
    // mBoard.setBoardName("testload");
    EXPECT_FALSE(loadPathPCB.empty());
    EXPECT_FALSE(savePathPCB.empty());
    EXPECT_FALSE(loadPathPKG.empty());
    EXPECT_FALSE(savePathPKG.empty());
    EXPECT_FALSE(mBoard.open(loadPathPCB.string()));
    EXPECT_TRUE(mBoard.open(loadPathPKG.string()));
    auto boardDataPKG = mBoard.getBoardData();
    EXPECT_EQ(boardDataPKG.width, 2000);
    EXPECT_EQ(boardDataPKG.height, 2200);
    EXPECT_EQ(boardDataPKG.accuracy, 4);
    EXPECT_EQ(boardDataPKG.originX, 5);
    EXPECT_EQ(boardDataPKG.originY, 6);
    EXPECT_STREQ(boardDataPKG.unitName.c_str(), "mm");
    EXPECT_STREQ(boardDataPKG.path.c_str(), loadPathPKG.string().c_str());
    EXPECT_TRUE(mBoard.save(savePathPKG.string()));
    EXPECT_FALSE(mBoard.save(savePathPCB.string()));
    mBoard.setBoardMode(BoardMode::PCB);
    EXPECT_FALSE(mBoard.open(loadPathPKG.string()));
    EXPECT_TRUE(mBoard.open(loadPathPCB.string()));
    auto boardDataPCB = mBoard.getBoardData();
    EXPECT_EQ(boardDataPCB.width, 1000);
    EXPECT_EQ(boardDataPCB.height, 1200);
    EXPECT_EQ(boardDataPCB.accuracy, 1);
    EXPECT_EQ(boardDataPCB.originX, 2);
    EXPECT_EQ(boardDataPCB.originY, 3);
    EXPECT_STREQ(boardDataPCB.unitName.c_str(), "cm");
    EXPECT_STREQ(boardDataPCB.path.c_str(), loadPathPCB.string().c_str());
    EXPECT_TRUE(mBoard.save(savePathPCB.string()));
    EXPECT_FALSE(mBoard.save(savePathPKG.string()));
}

TEST_F(BoardTestSuite, rename){
    std::string boardName{"board rename"};
    mBoard.setUp();
    EXPECT_TRUE(mBoard.rename(boardName));
    EXPECT_STREQ(mBoard.name().c_str(), boardName.c_str());
}

TEST_F(BoardTestSuite, getSettingModel){
    mBoard.setUp();
    EXPECT_TRUE(mBoard.getSettingModel() == nullptr);
}

TEST_F(BoardTestSuite, getRenderPtr){
    mBoard.setUp();
    rededa::RenderPointer render = mBoard.getRenderPtr();
    EXPECT_TRUE(render.mContext != nullptr);
    EXPECT_TRUE(render.mRender != nullptr);
    EXPECT_TRUE(render.mScene != nullptr);
    EXPECT_TRUE(render.msurface != nullptr);
    EXPECT_TRUE(render.mTransform != nullptr);
}

TEST_F(BoardTestSuite, getLayerManager){
    mBoard.setUp();
    auto layermanager = mBoard.getLayerManager();
    EXPECT_TRUE(layermanager != nullptr);
}

TEST_F(BoardTestSuite, getLayerManagerID){
    mBoard.setUp();
    auto layermanagerid = mBoard.getLayerManagerID();
    EXPECT_GT(layermanagerid, 0);
}

TEST_F(BoardTestSuite, getItemHolderID)
{
    mBoard.setUp();
    EXPECT_GT(mBoard.getItemHolderID(), 1);
}

TEST_F(BoardTestSuite, getDrawLineID)
{
    mBoard.setUp();
    EXPECT_GT(mBoard.getDrawLineID(), 1);
}

TEST_F(BoardTestSuite, getSelectionID)
{
    mBoard.setUp();
    EXPECT_GT(mBoard.getSelectionID(), 0);
}

TEST_F(BoardTestSuite, getDrawComplexCopperMachineID)
{
    mBoard.setUp();
    EXPECT_GT(mBoard.getDrawComplexCopperMachineID(), -1);
}

TEST_F(BoardTestSuite, getStateDrawComplexCopperID)
{
    mBoard.setUp();
    EXPECT_GT(mBoard.getStateDrawComplexCopperID(), -1);
}