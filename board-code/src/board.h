#ifndef _DD08B8EB_0805_4A04_AEAD_A3369D343B86_
#define _DD08B8EB_0805_4A04_AEAD_A3369D343B86_

#include "rededa/board/common/common.h"
#include "rededa/board/error.h"
// #include "settings_model/settings_data.h"
#include "project_manager/inc/i_design.h"
#include "board_data.h"
#include "board_dao.h"
#include "board_assemble.h"
#include <memory>
#include <vector>
#include <functional>

class RLayerManager;
namespace rededa {
class  RBoard : public RIDesign {
public:
    explicit RBoard(rhandle_t handle);

    inline rhandle_t handle() const {return mHandle;}

  // rerror_t api(int param1, int* param2) override;

    void setUp();
    void setBoardData(const BoardData &aBoardData);
    void setBoardName(const std::string &name);
    void setBoardPath(const std::string &aBoardPath);
    void setBoardMode(const BoardMode &aBoardMode);
    void setBoardProduct(const BoardProduct &aBoardProduct);
    static void registCallback(int(*callback)(int));
    static void registCloseCallback(void(*closeCallback)(bool));

    int getLayerManagerID() const;
    int getColorManagerID() const;
    int getItemHolderID() const;
    int getViaListID() const;
    int getDrawLineID() const;
    int getDrawComplexCopperMachineID() const;
    int getStateDrawComplexCopperID() const;
    int getSelectionID() const;
    int getSettingID() const;
    const RenderPointer getRenderPtr() const;
    const BoardData &getBoardData() const;
    std::shared_ptr<RLayerManager> getLayerManager() const;
    const std::string &getBoardName() const;
    const std::string &getBoardFileName() const;
    BoardMode getBoardMode() const;
    BoardProduct getBoardProduct() const;
    bool checkBoardDefault() const;
    bool checkBoardSaved() const;
    
    RBoardErrCode addItem();

    /**
     * @brief 获取设计名称
     *
     * @return std::string 设计名称
     */
    std::string name() override;

    /**
     * @brief 保存设计
     *
     * @param aPath 设计文件路径
     * @return bool 是否保存成功
     */
    bool save(const std::string &aPath) override;

    /**
     * @brief 打开设计
     *
     * @param aPath 设计文件路径
     * @return bool 是否打开成功
     */
    bool open(const std::string &aPath) override;

    /**
     * @brief 重命名设计
     *
     * @param aNewName 设计新名称
     * @return bool 是否重命名成功
     */
    bool rename(const std::string &aNewName) override;
    
    /**
     * @brief 获取setting model
     *
     * @return   std::shared_ptr<IRSettings>
     */
    std::shared_ptr<IRSettings> getSettingModel() override;

    /**
     * @brief 关闭设计
     *
     * @return bool 是否关闭成功
     */
    bool close() override;
    void testRLog() const;

private:
    rhandle_t mHandle{INVALID_HANDLE};
    std::unique_ptr<rededa::BoardAssemble> mBoardAssemble;
    BoardData mData;
    std::string mName;
    BoardMode mMode;
    BoardProduct mProduct;
    std::unique_ptr<RBoardFileDao> mBoardFileDAO;
    bool mIsDefaultBoard;
    bool mIsDataChanged;
    static std::function<int(int)> mCallback;
    static std::function<void(bool)> mCloseCallback;

    std::string getPathFileName(const std::string& aPath);
    bool extensionCheck(const std::string& aPath);
};

}  // namespace rededa


#endif  // _DD08B8EB_0805_4A04_AEAD_A3369D343B86_ // NOLINT

