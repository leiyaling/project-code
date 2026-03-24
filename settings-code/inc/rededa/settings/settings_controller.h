#ifndef _SETTINGS_SETTINGS_CONTRALLOR_H
#define _SETTINGS_SETTINGS_CONTRALLOR_H

#include <memory>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "common.h"
#include "settings_read.h"
#include "i_settings.h"

namespace rededa
{
  class RSettings;
  class REDEDA_SETTINGS_API RSettingsController final
  {
  public:
  
    static RSettingsController &instance();

    /**
     * @brief 通过产品类型创建设置实例
     *
     * 根据提供的产品类型创建一个新的设置实例。
     *
     * @param aSettingProduct 要创建的设置实例对应的产品类型
     * @return std::shared_ptr<IRSettings> 返回新创建的设置实例的智能指针，如果创建失败，则返回空指针
     */
    std::shared_ptr<IRSettings> createByProduct(SettingsProduct aSettingProduct);

    /**
     * @brief 注册设置实例
     *
     * 将一个设置实例注册到系统中，以便可以通过句柄访问。
     *
     * @param aSettings 要注册的设置实例的智能指针
     * @return int 返回注册成功的句柄，如果注册失败，则返回-1
     */
    int registerRSetting(std::shared_ptr<IRSettings> aSettings);

    /**
     * @brief 通过句柄获取设置实例
     *
     * 根据提供的句柄获取对应的设置实例。
     *
     * @param aHandle 要获取的设置实例的句柄
     * @return std::shared_ptr<IRSettings> 返回对应的设置实例的智能指针，如果句柄无效，则返回空指针
     */
    std::shared_ptr<IRSettings> getRSettings(rhandle_t aHandle);

    /**
     * @brief 通过句柄删除设置实例
     *
     * 根据提供的句柄从系统中删除对应的设置实例。
     *
     * @param aHandle 要删除的设置实例的句柄
     * @return int 返回操作结果，0表示删除成功，-1表示删除失败
     */
    int deleteRSettings(rhandle_t aHandle);

    /**
     * @brief 获取SettingsRead
     *
     * @return RSettingsRead& 返回获取SettingsRead
     */
    RSettingsRead &getRSettingsRead();

  protected:
    // RSettingsController() = default;
    RSettingsController(RSettingsController const &) = delete;
    RSettingsController operator=(RSettingsController const &) = delete;

  private:
    RSettingsController() : mRead(std::make_shared<RSettingsRead>()) {}
    std::shared_ptr<RSettingsRead> mRead;
  };

}

#endif /* _SETTINGS_SETTINGS_CONTRALLOR_H */
