#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <string>

#include "board_dao.h"
#include "board_data.h" 
#include "common.h"

#include <memory>

class DAOTestSuite : public testing::Test
{
  public:
    DAOTestSuite() = default;
    ~DAOTestSuite() override = default;

  protected:
    rededa::RBoardFileDao mBoardFileDAO;

    void SetUp() override {
        mBoardFileDAO = rededa::RBoardFileDao();
    }
};

TEST_F(DAOTestSuite, save){
    auto callback = [](const std::string& path){
        std::cout << "callback show path" << path << std::endl;
    }; 
    EXPECT_FALSE(mBoardFileDAO.save(callback));
    mBoardFileDAO.setName("testDAO");
    auto savePathPCB = test_board::getRBoardTestResourcePath("testDAO.redpkg");
    EXPECT_FALSE(savePathPCB.empty());
    mBoardFileDAO.setPath(savePathPCB.string());
    EXPECT_TRUE(mBoardFileDAO.save(callback));
}

TEST_F(DAOTestSuite, load){
    mBoardFileDAO = rededa::RBoardFileDao();
    auto callback = [](const rededa::BoardData &boardData, const std::string& path){
        std::cout << "callback show path" << path << std::endl;
    };
    EXPECT_FALSE(mBoardFileDAO.load(callback));
    mBoardFileDAO.setName("testDAO.redpcb");
    auto savePathPCB = test_board::getRBoardTestResourcePath("testDAO.redpkg");
    EXPECT_FALSE(savePathPCB.empty());
    mBoardFileDAO.setPath(savePathPCB.string());
    EXPECT_TRUE(mBoardFileDAO.load(callback));
}