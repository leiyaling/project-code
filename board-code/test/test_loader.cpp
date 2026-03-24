#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <memory>

#include "rededa/board/loader/pcb_loader.h"
#include "rededa/board/loader/pkg_loader.h"
#include "board.h"
#include "board_controller.h"
#include "rededa/board/board_c.h"
#include "common.h"

class LoaderTestSuite : public testing::Test
{
  public:
    LoaderTestSuite() = default;
    ~LoaderTestSuite() override = default;

  protected:
    rededa::RPcbLoader mPcbLoader;
    rededa::RPkgLoader mPkgLoader;

    void SetUp() override {
        mPcbLoader = rededa::RPcbLoader();
        mPkgLoader = rededa::RPkgLoader();
    }
};

// TEST_F(LoaderTestSuite, newDesign){
//     EXPECT_TRUE(mPcbLoader.newDesign("test.redpkg") == nullptr);
//     EXPECT_TRUE(mPcbLoader.newDesign("te*st.redpcb") == nullptr);
//     EXPECT_TRUE(mPcbLoader.newDesign("test.redpcb") != nullptr);
//     EXPECT_TRUE(mPkgLoader.newDesign("test.redpcb") == nullptr);
//     EXPECT_TRUE(mPkgLoader.newDesign("te*st.redpcb") == nullptr);
//     auto pkgDesign = mPkgLoader.newDesign("test.redpkg");
//     EXPECT_TRUE(pkgDesign != nullptr);
//     auto design = std::dynamic_pointer_cast<rededa::RBoard>(pkgDesign);
//     EXPECT_FALSE(design == nullptr);
//     EXPECT_STREQ(board_get_current_file_path(design->handle()), "test.redpkg");
// }

// TEST_F(LoaderTestSuite, load){
//     mPcbLoader = rededa::RPcbLoader();
//     mPkgLoader = rededa::RPkgLoader();
//     auto loadPathPCB = test_board::getRBoardTestCurrentExistResourcePath("test_save_pcb.redpcb");
//     auto loadPathPKG = test_board::getRBoardTestCurrentExistResourcePath("test_save_pkg.redpkg");
//     auto illegalPath = test_board::getRBoardTestResourcePath("line<>_save_1.tproto");
//     EXPECT_FALSE(mPcbLoader.load(loadPathPCB.string()));
//     EXPECT_FALSE(mPkgLoader.load(loadPathPKG.string()));
//     EXPECT_TRUE(mPcbLoader.newDesign("test.redpcb") != nullptr);
//     EXPECT_TRUE(mPkgLoader.newDesign("test.redpkg") != nullptr);
//     EXPECT_FALSE(mPcbLoader.load(illegalPath.string()));
//     EXPECT_TRUE(mPcbLoader.load(loadPathPCB.string()));
//     EXPECT_FALSE(mPcbLoader.load(loadPathPKG.string()));
//     EXPECT_FALSE(mPkgLoader.load(illegalPath.string()));
//     EXPECT_TRUE(mPkgLoader.load(loadPathPKG.string()));
//     EXPECT_FALSE(mPkgLoader.load(loadPathPCB.string()));
// }

TEST_F(LoaderTestSuite, getExtension){
    EXPECT_STREQ(mPcbLoader.getExtension().c_str(), "redpcb");
    EXPECT_STREQ(mPkgLoader.getExtension().c_str(), "redpkg");
}