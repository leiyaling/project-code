#include "settings_db_dao.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <fstream>
#include <iostream>
namespace rededa
{
    nlohmann::json RDBSettingsDAO::loadSettings()
    {
        nlohmann::json jsonData;

        return jsonData;
    }
    int RDBSettingsDAO::saveSettings(const nlohmann::json& mJson)
    {
        return -1;
    }
} // namespace rededa
