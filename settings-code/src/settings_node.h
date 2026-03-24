#ifndef B158D601_5231_4995_8DA3_B579C4F296AF
#define B158D601_5231_4995_8DA3_B579C4F296AF

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <map>
namespace rededa
{
    class RSettingsNode : public std::enable_shared_from_this<RSettingsNode>
    {
    public:
        RSettingsNode(const std::string &aName, const nlohmann::json &aValue);

        void addChild(const std::shared_ptr<RSettingsNode> &aChild);

        std::shared_ptr<RSettingsNode> getChild(const std::string &aKey);

        nlohmann::json getValue() const;

        void setValue(const nlohmann::json &value);

        void setParent(std::shared_ptr<RSettingsNode> parent);

        std::shared_ptr<RSettingsNode> getParent() const;

        std::string getName() const;

        void updateParentValue();

        std::string mName;
        std::vector<std::shared_ptr<RSettingsNode>> mChildren;
        nlohmann::json mValue;
        std::shared_ptr<RSettingsNode> mParent;
    };
} // namespace rededa

#endif /* B158D601_5231_4995_8DA3_B579C4F296AF */
