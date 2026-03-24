#ifndef _SETTINGS_SETTINGS_H
#define _SETTINGS_SETTINGS_H
#include "rededa/settings/common.h"
#include "rededa/settings/i_settings.h"
#include "settings_node.h"
#include "rededa/settings/i_settings_observer.h"
#include "rededa/settings/i_settings_dao.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <string>
#include <list>
#include <memory>
#include <map>

namespace rededa
{
  class RSettingsSystem;
  class RSettings : public IRSettings
  {
  public:
    RSettings(SettingsProduct aSettingProduct, std::string aName);

    /**
     * @brief 获取settings产品枚举
     *
     * @return SettingsProduct
     */
    SettingsProduct getProduct() const override;

    /**
     * @brief 获取settings产品句柄
     *
     * @return rhandle_t
     */
    rhandle_t getHandle() const override;

    /**
     * @brief 更新settings项
     *
     * 使用给定的key和JSON数据来更新settings中的项。key是一个以点分隔的字符串，用于指定要更新的settings项的路径。
     * JSON数据提供了要更新的值。
     *
     * @param aKey 要更新的settings项的key
     * @param aJson 包含新值的JSON数据
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int updateValue(const std::string &aKey, const nlohmann::json &aJson) override;

    /**
     * @brief 插入settings项
     *
     * 将一个新的settings项插入到settings中。key是一个以点分隔的字符串，用于指定新项的位置。
     * JSON数据提供了要插入的项的值。
     *
     * @param aKey 要插入的settings项的key
     * @param aJson 包含新项值的JSON数据
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int insertValue(const std::string &aKey, const nlohmann::json &aJson) override;

    /**
     * @brief 删除settings项
     *
     * 根据给定的key删除settings中的项。key是一个以点分隔的字符串，用于指定要删除的settings项的路径。
     *
     * @param aKey 要删除的settings项的key
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int deleteKey(const std::string &aKey) override;

    /**
     * @brief 获取settings项的值
     *
     * 根据给定的key获取settings中的项的值。key是一个以点分隔的字符串，用于指定要获取的settings项的路径。
     *
     * @param aKey 要获取值的settings项的key
     * @return std::string 返回settings项的值，如果key不存在，则返回空字符串
     */
    const std::string getValue(const std::string &aKey) override;

    /**
     * @brief 获取所有设置项的值
     *
     * 将当前所有设置项的值序列化为一个字符串，并返回。
     *
     * @return std::string 返回包含所有设置项值的序列化字符串
     */
    std::string getAllData() override;

    /**
     * @brief 设置所有设置项的值
     *
     * 反序列化给定的字符串并将值应用到设置系统中。
     *
     * @param aData 包含所有设置项值的序列化字符串
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int setAllData(const std::string &aData) override;

    /**
     * @brief 设置回调函数
     * @param aData 通知VM数据变化的回调函数
     */
    void setChangeCallBack(const data_change_call_back aCallBack) override;

    /**
     * @brief 设置设置项的数据访问对象（DAO）
     *
     * @param aSettingsDAO 一个指向IRSettingsDAO接口的智能指针，用于设置数据的持久化
     */
    void setISettingsDAO(std::shared_ptr<IRSettingsDAO> aSettingsDAO) override;

    /**
     * @brief 注册节点
     *
     * @param aBranch 需要注册的节点
     */
    void registerNode(std::shared_ptr<RSettingsNode> aBranch);

    /**
     * @brief 从文件中加载设置配置
     *
     * 从指定的文件中读取设置配置，并将其应用到设置系统中。
     *
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int load() override;

    /**
     * @brief 将设置项配置保存到文件
     *
     * 将当前的设置配置保存到指定的文件中。
     *
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int save() override;

    /**
     * @brief  初始化settings
     * @param aSettingProduct  产品类型
     * @return int 返回操作结果，0表示成功，-1表示失败
     */
    int initSettings(SettingsProduct aSettingProduct);

    /**
     * @brief 注册观察者
     *
     * 将一个观察者对象添加到settings系统中，用于监听settings的变化。
     * 当settings项发生变化时，注册的观察者将会收到通知。
     *
     * @param aObserver 要注册的观察者对象的智能指针
     */
    void attach(std::shared_ptr<IRSettingsObserver> aObserver);

    /**
     * @brief 移除观察者
     *
     * 从settings系统中移除一个观察者对象，停止接收settings变化的通知。
     *
     * @param aObserver 要移除的观察者对象的智能指针
     */
    void detach(std::shared_ptr<IRSettingsObserver> aObserver);

    /**
     * @brief 通知观察者
     *
     * 当特定的settings项发生变化时，通知注册的观察者。
     * 该方法由settings系统内部调用，以通知观察者某个特定的settings项已经更新。
     *
     * @param aKey 发生变化的settings项的key
     * @param aValue 发生变化的settings项的新值
     */
    void notify(const std::string &aKey, const nlohmann::json &aValue);

    /**
     * @brief 通知观察者
     *
     * 当settings系统的所有数据发生变化时，通知注册的观察者。
     * 该方法由settings系统内部调用，以通知观察者整个settings数据已经更新。
     *
     * @param aData 包含所有settings项新值的JSON对象
     */
    void notifyAll(const nlohmann::json &aData);
    
  private:
    rhandle_t mHandle{};
    SettingsProduct mSettingProduct;
    std::shared_ptr<RSettingsNode> mRoot;
    data_change_call_back mDataChangeCallback = nullptr; // 通知VM数据变动的回调函数

    std::list<std::shared_ptr<IRSettingsObserver>> mObservers;
    std::shared_ptr<IRSettingsDAO> mSettingsDAO;
  };

}

#endif /* _SETTINGS_SETTINGS_H */
