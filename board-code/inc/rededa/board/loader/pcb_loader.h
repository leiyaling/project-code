#ifndef INCLUDE_BOARD_LOADER_PCBLOADER
#define INCLUDE_BOARD_LOADER_PCBLOADER
#include <filesystem>
#include <fstream>
#include <memory>
#include <rededa/project_manager/inc/i_design_loader.h>

namespace rededa
{
class RPcbLoader : public RIDesignLoader
{
  private:
    /**
     * @brief 路径合法性检查
     *
     * @param aPath 设计文件路径
     * @return bool
     */
    bool pathCheck(const std::string &aPath);

    /**
     * @brief 后缀合法性检查
     *
     * @param aExtension 设计文件路径
     * @return bool
     */
    bool extensionCheck(const std::string &aExtension);

  private:
    int mDesignID;
    std::string mDesignExtension;

  public:
    RPcbLoader();
    ~RPcbLoader();

    /**
     * @brief 新建设计的
     *
     * @param aPath 设计文件路径
     * @return std::shared_ptr<RIDesign>
     */
    std::shared_ptr<RIDesign> newDesign(std::string aPath) override;

    /**
     * @brief 加载当前路径下的项目
     *
     * @param aPath 设计文件路径
     * @return std::shared_ptr<RIDesign>
     */
    std::shared_ptr<RIDesign> load(std::string aPath) override;

    /**
     * @brief 获取后缀
     *
     * @return design loader维护的后缀
     */
    std::string getExtension() const override;

    /**
     * @brief 移除已经存在的design
     * 
     * @param aDesign 
     * @return true 
     * @return false 
     */
    bool removeDesign(std::shared_ptr<RIDesign> aDesign) override;
};
} // namespace rededa

#endif // INCLUDE_BOARD_LOADER_PCBLOADER