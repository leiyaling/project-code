#ifndef _SETTINGS_SETTINGS_C_H
#define _SETTINGS_SETTINGS_C_H

#include "common.h"
#include "settings_data.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 创建唯一 settings
     *
     * @param setting_product 设置产品
     * @return int 返回值为 settings id
     */
    REDEDA_SETTINGS_API int red_settings_create_id(SettingsProduct setting_product);

    /**
     * @brief 设置单个配置项的值
     *
     * @param id settings id
     * @param key 要设置的配置项的键
     * @param value 要设置的配置项的值
     * @return int 返回值为 0 表示成功，-1 表示失败
     */
    REDEDA_SETTINGS_API int red_settings_set_item(int id, const char *key, const char *value);

    /**
     * @brief 获取单个配置项的值
     *
     * @param id settings id
     * @param key 要获取的配置项的键
     * @param call_back 回调函数，用于复制配置项的值
     * @return int 返回值为 0 表示成功，-1 表示失败
     */
    REDEDA_SETTINGS_API int red_settings_get_item(int id, const char *key, str_copy_call_back call_back);

    /**
     * @brief 保存配置
     *
     * @param path 配置文件的路径
     * @param id   settings id
     * @return int 返回值为 0 表示成功，-1 表示文件路径为空，-2
     * 表示文件未被正确打开，-3 表示内容序列化失败
     */
    REDEDA_SETTINGS_API int red_settings_save(int id, const char *path);
    /**
     * @brief 加载配置
     *
     * @param path 配置文件的路径
     * @param id settings id
     * @return int 返回值为 0 表示成功，-1 表示文件路径为空，-2
     * 表示文件未被正确打开，-3 表示内容反序列化失败
     */
    REDEDA_SETTINGS_API int red_settings_load(int id, const char *path);

    /**
     * @brief  设置settings数据
     *
     * @param id   settings id
     * @param data 要设置保存的数据
     * @return int 返回值为 0 表示成功， -1 表示失败
     */
    REDEDA_SETTINGS_API int red_settings_set_all_data(int id, const char *data);

    /**
     * @brief 通过回调函数方式获取 settings 的内容
     *
     * @param id settings id
     * @param call_back 通过回调将字符串拷贝
     *                  回调函数参数为 const char* 和 int 确定一个字符串
     *                  该函数内部确保当调用 callback 函数时的传入的 const char*
     *                  数据是有效的
     * @return int 返回值为 0 表示成功，-1 表示失败
     */
    REDEDA_SETTINGS_API int red_settings_get_all_data(int id, str_copy_call_back call_back);
    // void (*call_back)(const char *start, int length));

    /**
     * @brief 设置数据变动的回调函数
     *
     * @param id settings id
     * @param callback 回调函数
     * @return int 返回值为 0 表示成功，-1 表示失败
     */
    REDEDA_SETTINGS_API int red_settings_set_data_change(int id, data_change_call_back call_back);
#ifdef __cplusplus
}
#endif
#endif /* _SETTINGS_SETTINGS_C_H */