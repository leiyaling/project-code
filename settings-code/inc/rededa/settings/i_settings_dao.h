#ifndef _SETTINGS_I_SETTINGS_DAO_H
#define _SETTINGS_I_SETTINGS_DAO_H

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <string>
namespace rededa
{
    class IRSettingsDAO
    {
    public:
        virtual ~IRSettingsDAO() = default;
        virtual nlohmann::json loadSettings() = 0;
        virtual int saveSettings(const nlohmann::json &aJson) = 0;
    };
} // namespace rededa

#endif //_SETTINGS_I_SETTINGS_DAO_H