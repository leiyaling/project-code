#ifndef _SETTINGS_SETTINGS_DATA_H
#define _SETTINGS_SETTINGS_DATA_H


/**
 * @brief settings 的产品
 *
 */
enum SettingsProduct
{
    REDEDA_PREFERENCES = 1,
    REDEDA_SCH = 2,
    REDEDA_PCB = 3,
    REDEDA_PKG = 4,
};

struct red_c_str
{
    const char *data;
    unsigned int len;
};
/**
 ** 定义的 字符串 拷贝回调函数，由上层提供
 */
typedef void (*str_copy_call_back)(const char *, int);

/**
 ** 定义的 通知数据变动回调函数，由上层提供
 */
typedef void (*data_change_call_back)(const char* key, const char* value);

#endif /* _SETTINGS_SETTINGS_DATA_H */
