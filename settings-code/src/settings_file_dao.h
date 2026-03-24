#ifndef _SETTINGS_SETTINGS_FILE_DAO_H
#define _SETTINGS_SETTINGS_FILE_DAO_H
#include "rededa/settings/i_settings_dao.h"
namespace rededa
{
    class RFileSettingsDAO final: public IRSettingsDAO
    {
    public:
        explicit RFileSettingsDAO(const std::string &aPath) : mFilePath(aPath) {}
        nlohmann::json loadSettings() override;
        int saveSettings(const nlohmann::json &aJson) override;

    private:
        std::string mFilePath;
    };
} // namespace rededa

#endif //_SETTINGS_SETTINGS_FILE_DAO_H