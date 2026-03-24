#include "rededa/settings/settings_read.h"
#include "settings.h"
#include <iostream>
namespace rededa
{
    RSettingsRead::RSettingsRead() : mHandle(0)
    {
    }
    int RSettingsRead::addRSettings(std::shared_ptr<IRSettings> aSettings)
    {
        int key = ++mHandle;
        mData[key] = aSettings;

        // 更新 productToId
        SettingsProduct product = aSettings->getProduct();
        mProductToId[product].push_back(key);

        return key;
    }

    std::shared_ptr<IRSettings> RSettingsRead::getRSettings(rhandle_t aHandle)
    {
        auto it = mData.find(aHandle);
        if (it == mData.end())
        {
            return nullptr;
        }
        return it->second;
    }

    int RSettingsRead::removeRSettings(rhandle_t aHandle)
    {
        auto it = mData.find(aHandle);
        if (it == mData.end())
        {
            return -1;
        }
        mData.erase(it);
        return 0;
    }

    std::string RSettingsRead::getValue(const std::string &aKey, SettingsProduct aSettingProduct)
    {
        std::vector<int> keys = mProductToId[aSettingProduct];
        std::string result = "";
        for (int keyi : keys)
        {
            auto it = mData.find(keyi); // RSettings
            if (it != mData.end())
            {
                result = it->second->getValue(aKey);
                if (!result.empty())
                {
                    return result;
                }
            }
        }
        return result;
    }
} // namespace rededa
