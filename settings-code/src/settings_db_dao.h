
#ifndef _SETTINGS_DB_SETTINGSDAO_
#define _SETTINGS_DB_SETTINGSDAO_
#include "rededa/settings/i_settings_dao.h"
namespace rededa
{
    class RDBSettingsDAO final : public IRSettingsDAO
    {
    public:
        explicit RDBSettingsDAO(const std::string &aConnStr) : mConnectionString(aConnStr) {}
        nlohmann::json loadSettings() override;
        int saveSettings(const nlohmann::json &aJson) override;

    private:
        std::string mConnectionString;
    };
} // namespace rededa

#endif //_SETTINGS_DB_SETTINGSDAO_
