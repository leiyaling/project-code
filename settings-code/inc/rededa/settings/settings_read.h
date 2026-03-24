#ifndef _SETTINGS_SETTINGS_READ_H
#define _SETTINGS_SETTINGS_READ_H
#include "common.h"
#include "settings_data.h"
#include "i_settings.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
namespace rededa
{
    class RSettings;
    class REDEDA_SETTINGS_API RSettingsRead
    {
    public:
        RSettingsRead();

        /**
         * @brief  注册settings
         * @param aSettings   settings实例
         * @return int 返回值为 settings的句柄
         */
        int addRSettings(std::shared_ptr<IRSettings> aSettings);

        /**
         * @brief  通过句柄拿到settings
         * @param aHandle   settings句柄
         * @return std::shared_ptr<IRSettings> 返回值为 settings
         */
        std::shared_ptr<IRSettings> getRSettings(rhandle_t aHandle);

        /**
         * @brief  通过句柄删除settings
         * @param aHandle   settings句柄
         * @return int 返回值为 0 表示成功， -1 表示失败
         */
        int removeRSettings(rhandle_t aHandle);

        /**
         * @brief  查找settings的项
         * @param aKey   查找的项
         * @param aSettingProduct   settings产品
         * @return int 返回值为 0 表示成功， -1 表示失败
         */
        std::string getValue(const std::string &aKey, SettingsProduct aSettingProduct);

    private:
        rhandle_t mHandle;
        std::unordered_map<int, std::shared_ptr<IRSettings>> mData;
        std::unordered_map<SettingsProduct, std::vector<int>> mProductToId;
    };

} // namespace rededa

#endif /* _SETTINGS_SETTINGS_READ_H */
