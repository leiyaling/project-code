#include "settings_node.h"
#include <iostream>

namespace rededa
{

    RSettingsNode::RSettingsNode(const std::string &aName, const nlohmann::json &aValue)
        : mName(aName), mValue(aValue)
    {
        // if (aValue.is_object())
        // {
        //     for (auto it = aValue.begin(); it != aValue.end(); ++it)
        //     {
        //         const std::string childKey = it.key();
        //         const nlohmann::json &childValue = it.value();
        //         auto childNode = std::make_shared<RSettingsNode>(childKey, childValue);
        //         addChild(childNode);
        //     }
        // }
        // else if (aValue.is_array())
        // {
        //     for (size_t i = 0; i < aValue.size(); ++i)
        //     {
        //         const std::string arrayKey = std::to_string(i);
        //         const nlohmann::json &arrayValue = aValue[i];
        //         auto arrayChildNode = std::make_shared<RSettingsNode>(arrayKey, arrayValue);
        //         addChild(arrayChildNode);
        //     }
        // }
    }

    void RSettingsNode::addChild(const std::shared_ptr<RSettingsNode> &aChild)
    {
        if (aChild)
        {
            mChildren.push_back(aChild);
            aChild->setParent(shared_from_this());
        }
    }

    std::shared_ptr<RSettingsNode> RSettingsNode::getChild(const std::string &aKey)
    {
        for (const auto &child : mChildren)
        {
            if (child->getName() == aKey)
            {
                return child;
            }
        }
        return nullptr;
    }

    void RSettingsNode::setParent(std::shared_ptr<RSettingsNode> parent)
    {
        mParent = parent;
    }

    std::shared_ptr<RSettingsNode> RSettingsNode::getParent() const
    {
        return mParent;
    }

    void RSettingsNode::setValue(const nlohmann::json &value)
{
    // 将当前节点的值设置为传入的 JSON 值
    mValue = value;

    // 如果值是对象类型，递归设置子节点
    if (value.is_object())
    {
        for (auto it = value.begin(); it != value.end(); ++it)
        {
            const std::string childKey = it.key();
            const nlohmann::json &childValue = it.value();

            // 检查是否已经有子节点存在
            auto existingChildNode = getChild(childKey);
            if (!existingChildNode)
            {
                // 创建新的子节点并递归设置值
                auto newChildNode = std::make_shared<RSettingsNode>(childKey, childValue);
                addChild(newChildNode);
                newChildNode->setValue(childValue);
            }
            else
            {
                // 更新已有子节点的值
                existingChildNode->setValue(childValue);
            }
        }
    }
    // 如果值是数组类型，递归处理每个数组元素
    else if (value.is_array())
    {
        for (size_t i = 0; i < value.size(); ++i)
        {
            const nlohmann::json &arrayValue = value[i];

            // 将数组元素按索引作为 key, 或者直接处理数组
            auto existingChildNode = getChild(std::to_string(i));
            if (!existingChildNode)
            {
                // 创建新的子节点并递归设置数组值
                auto arrayChildNode = std::make_shared<RSettingsNode>(std::to_string(i), arrayValue);
                addChild(arrayChildNode);
                arrayChildNode->setValue(arrayValue);
            }
            else
            {
                // 更新已有数组子节点的值
                existingChildNode->setValue(arrayValue);
            }
        }
    }
    else
    {
        // 对于非对象和非数组的简单类型，直接设置值即可
        mValue = value;
    }
}

    
void RSettingsNode::updateParentValue()
{
    if (mParent) // 只有父节点存在时才更新
    {
        // 获取当前父节点的值
        nlohmann::json parentValue = mParent->getValue();

        // 父节点必须是一个对象
        if (!parentValue.is_object()) {
            parentValue = nlohmann::json::object();
        }

        // 更新父节点中对应当前节点的值
        parentValue[mName] = mValue;

        // 设置父节点的新值
        mParent->setValue(parentValue);

        // 递归更新父节点
        mParent->updateParentValue();
    }
}


    nlohmann::json RSettingsNode::getValue() const
    {
        return mValue;
    }

    std::string RSettingsNode::getName() const
    {
        return mName;
    }

} // namespace rededa



