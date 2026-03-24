#include <gtest/gtest.h>
#include "board_assemble.h"
using namespace rededa;

class TestBoardAssembleSuite : public testing::Test{
public:
    TestBoardAssembleSuite()=default;
    ~TestBoardAssembleSuite()override=default;

protected:
    BoardAssemble mAssemble;

    void SetUp() override {
        mAssemble = rededa::BoardAssemble();
    }
};


TEST_F(TestBoardAssembleSuite, InitialState){
    EXPECT_TRUE(mAssemble.getScenePtr() == nullptr);
    EXPECT_TRUE(mAssemble.getRenderPtr() == nullptr);
    EXPECT_TRUE(mAssemble.getTransformPtr() == nullptr);
    EXPECT_TRUE(mAssemble.getSurfacePtr() == nullptr);
    EXPECT_TRUE(mAssemble.getContextPtr() == nullptr);
    // EXPECT_TRUE(mAssemble.getLayerManager() == nullptr);
    EXPECT_EQ(mAssemble.getItemHolderID(), -1);
    EXPECT_EQ(mAssemble.getBaseOperateMachineID(), -1);
    EXPECT_EQ(mAssemble.getDrawLineMachineID(), -1);
    EXPECT_EQ(mAssemble.getSelectionID(), -1);
    EXPECT_EQ(mAssemble.getDrawComplexCopperMachineID(), -1);
    EXPECT_EQ(mAssemble.getSettingID(), -1);
    // EXPECT_EQ(mAssemble.getColorManagerID(), -1);
    // EXPECT_EQ(mAssemble.getLayerManagerID(), -1);
    EXPECT_EQ(mAssemble.getStateDrawComplexCopperID(), -1);
}

TEST_F(TestBoardAssembleSuite, assemble){

}


TEST_F(TestBoardAssembleSuite, AfterAssembleState){
    mAssemble.assemble();
    EXPECT_TRUE(mAssemble.getScenePtr() != nullptr);
    std::cout << "scene:" << mAssemble.getScenePtr() << std::endl;
    EXPECT_TRUE(mAssemble.getRenderPtr() != nullptr);
    EXPECT_TRUE(mAssemble.getTransformPtr() != nullptr);
    EXPECT_TRUE(mAssemble.getSurfacePtr() != nullptr);
    EXPECT_TRUE(mAssemble.getContextPtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getLayerManager() != nullptr);
    EXPECT_GT(mAssemble.getItemHolderID(), -1);
    EXPECT_GT(mAssemble.getBaseOperateMachineID(), -1);
    EXPECT_EQ(mAssemble.getSettingID(), 1);
    EXPECT_GT(mAssemble.getSelectionID(), -1);
    EXPECT_GT(mAssemble.getDrawComplexCopperMachineID(), -1);
    EXPECT_GT(mAssemble.getDrawLineMachineID(), 0);
    // EXPECT_EQ(mAssemble.getColorManagerID(), 1);
    // EXPECT_EQ(mAssemble.getLayerManagerID(), 1);
    EXPECT_GT(mAssemble.getStateDrawComplexCopperID(), -1);
}

TEST_F(TestBoardAssembleSuite, AfterModuleConnectState){
    // mAssemble.assemble();
    // mAssemble.createModuleConnection();
    // EXPECT_EQ(mAssemble.getDrawLineMachineID(), 0);
    // EXPECT_TRUE(mAssemble.getScenePtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getRenderPtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getTransformPtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getSurfacePtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getRenderPtr() != nullptr);
    // EXPECT_TRUE(mAssemble.getRenderPtr() != nullptr);
    // EXPECT_EQ(mAssemble.getItemHolderID(), 0);
    // EXPECT_EQ(mAssemble.getDrawLineID(), 0);
    // EXPECT_EQ(mAssemble.getSettingID(SettingsProduct::REDEDA_PKG), 1);
}