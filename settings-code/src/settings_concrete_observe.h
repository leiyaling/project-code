#ifndef _CONCRETE_SETTINGS_OBSERVER_
#define _CONCRETE_SETTINGS_OBSERVER_

#include "rededa/settings/i_settings_observer.h"

namespace rededa
{
    class ConcreteSettingsObserver final: public IRSettingsObserver
    {
    public:
        void onSettingChanged(const std::string &key, const nlohmann::json &value) override
        {
            std::cout << "Setting changed: " << key << " to " << value.dump() << std::endl;
        }

        void onSettingsChangedToAllData(const nlohmann::json &data) override
        {
            std::cout << "Settings changed: " << data.dump() << std::endl;
        }
    };
} // namespace rededa

#endif //_CONCRETE_SETTINGS_OBSERVER_