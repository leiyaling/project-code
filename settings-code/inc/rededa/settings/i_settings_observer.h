#ifndef _I_SETTINGS_OBSERVER_H
#define _I_SETTINGS_OBSERVER_H

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

namespace rededa
{
    class IRSettingsObserver
    {
    public:
        /**
         * @brief 当单个设置项发生变化时触发的回调函数
         *
         * 当设置系统中的某个特定设置项的值发生变化时，该函数会被调用。
         *
         * @param aKey 发生变化的设置项的键（key），通常是一个以点分隔的字符串，表示设置项的路径。
         * @param aValue 发生变化的设置项的新值，以JSON格式表示。
         */
        virtual void onSettingChanged(const std::string &aKey, const nlohmann::json &aValue) = 0;

        /**
         * @brief 当所有设置数据发生变化时触发的回调函数
         *
         * @param aData 包含所有设置项新值的JSON对象。
         */
        virtual void onSettingsChangedToAllData(const nlohmann::json &aData) = 0;

    private:
    };
} // namespace rededa

#endif //_I_SETTINGS_OBSERVER_H