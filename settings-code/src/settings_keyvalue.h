#ifndef E5844997_0A41_41D3_8294_23FBEB78D881
#define E5844997_0A41_41D3_8294_23FBEB78D881
#include "settings_node.h"
#include <nlohmann/json.hpp>
#include <map>
namespace rededa
{
    class RSettingsKeyValue
    {
    public:
        RSettingsKeyValue() {}

        void addKeyValuePair(const std::string &key, const nlohmann::json &value)
        {
            mKeyValueMap[key] = value;
        }



        nlohmann::json getJsonValue(const std::string &key) const
        {
            auto it = mKeyValueMap.find(key);
            if (it != mKeyValueMap.end())
            {
                return it->second;
            }
            return nullptr;
        }

        nlohmann::json toJsonValue() const
        {
            return mKeyValueMap;
        }

    private:
        // std::string mKey;
        // std::string mValue;
        std::map<std::string, nlohmann::json> mKeyValueMap;
    };

} // namespace rededa

#endif /* E5844997_0A41_41D3_8294_23FBEB78D881 */
