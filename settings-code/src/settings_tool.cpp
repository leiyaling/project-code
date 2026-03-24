#include "settings_tool.h"
namespace rededa
{
    std::vector<std::string> split(const std::string &input, const std::string &delimiter)
    {
        std::vector<std::string> result;
        std::string str = input;
        size_t pos = 0;

        while ((pos = str.find(delimiter)) != std::string::npos)
        {
            std::string token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiter.size());
        }

        if (!str.empty())
        {
            result.push_back(str);
        }

        return result;
    }
} // namespace rededa
