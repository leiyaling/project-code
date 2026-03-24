#include "settings_file_dao.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <fstream>
#include <iostream>
namespace rededa
{
    nlohmann::json RFileSettingsDAO::loadSettings()
    {

        std::ifstream f{mFilePath, std::ios_base::in};

        if (!f.is_open())
        {
            return -2;
        }

        nlohmann::json jsonData;
        f >> jsonData;

        return jsonData;
    }
    int RFileSettingsDAO::saveSettings(const nlohmann::json &aJson)
    {

        std::ofstream f{mFilePath, std::ios_base::trunc | std::ios_base::out};

        if (!f.is_open())
        {
            return -1;
        }

        try
        {
            f << aJson.dump(4);
            f.flush(); 
            f.close(); 
            return 0;  
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error saving settings: " << e.what() << std::endl;
            return -1; 
        }
    }
} // namespace rededa
