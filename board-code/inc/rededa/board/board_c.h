#ifndef _CC0B9904_81D4_444A_9A8E_4AC9BDAA8D0A_
#define _CC0B9904_81D4_444A_9A8E_4AC9BDAA8D0A_

#include "common.h"
#include "common/common.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace rededa
{
class RIDesignLoader;
}

struct CRenderStruct{
    void *mScene;
    void *mContext;
    void *mTransform;
    void *msurface;
    void *mRender;
};
struct CStateID{
    int drawLineID;
    int drawComplexCopperID; ///< 画复杂铜皮状态机ID
    int drawComplexCopperStateID; ///< 画复杂铜皮模块ID
};
struct CSettingsID{
    int level0;
    int level1;
    int level2;
    int level3;
};
struct CBoardModuleID
{
    int layerID;
    int colorID;
    int itemHolderID;
    int vialistID;
    int selectionID;
    CRenderStruct renderID;
    CStateID stateID;
    CSettingsID settingsID;
};
struct CBoardData
{
    CBoardModuleID moduleID;
    double width;
    double height;
    unsigned accuracy;
    double originX;
    double originy;
    const char *boardName;
    const char *unitName;
    const char *path;
};

// @brief 释放业务逻辑对象
// @param[in] handle: 业务逻辑对象句柄
REDEDA_BOARD_API void board_release(rhandle_t handle);

/**
 * @brief 获取 board 属性
 *
 * @param rhandle_t 业务逻辑对象句柄
 * @return CBoardData baord 属性结构体
 */
REDEDA_BOARD_API CBoardData board_get_data(rhandle_t handle);

/**
 * @brief 加载 board
 *
 * @param id rhandle_t 业务逻辑对象句柄
 * @return RBoardErrCode 错误码
 */
REDEDA_BOARD_API RBoardErrCode board_load(rhandle_t handle);

/**
 * @brief 保存 board
 *
 * @param rhandle_t 业务逻辑对象句柄
 * @return RBoardErrCode 错误码
 */
REDEDA_BOARD_API RBoardErrCode board_save(rhandle_t handle);

/**
 * @brief 返回 board 当前文件路径
 * @param rhandle_t 业务逻辑对象句柄
 * @return const char* 返回 path 表示存在当前文件路径，返回 空串 ""
 * 表示当前文件路径为空
 */
REDEDA_BOARD_API const char* board_get_current_file_path(rhandle_t handle);

/**
 * @brief 检查当前board的工程文件是类型
 *
 * @param rhandle_t 业务逻辑对象句柄
 * @return BoardMode 返回板子模式
 */
REDEDA_BOARD_API BoardMode board_check_project_type(rhandle_t handle);

/**
 * @brief 创建 board
 *
 * @param path 创建board路径
 * @param name 创建board名称
 * @param BoardMode  创建board模式
 * 
 * @return rhandle_t 业务逻辑对象句柄
 */
REDEDA_BOARD_API rhandle_t board_new(const char* path, const char* name, BoardMode type);

/**
 * @brief 注册回调函数
 *
 * @param int(*)(int) 需要注册的回调函数
 * 
 * @return RBoardErrCode 错误码
 */
REDEDA_BOARD_API RBoardErrCode board_regist_callback(int (*callback)(int));

/**
 * @brief 注册退出时通知回调函数
 *
 * @param void(*)(bool) 需要注册的回调函数
 * 
 * @return RBoardErrCode 错误码
 */
REDEDA_BOARD_API RBoardErrCode board_regist_close_callback(void (*closeCallback)(bool));


/**
 * @brief 将design loader注册到项目管理器
 *
 * @param BoardMode 创建board模式
 * 
 * @return bool 返回 true 表示注册成功, 返回false表示注册失败
 */
REDEDA_BOARD_API bool board_regist_designloader(BoardMode type);

#ifdef __cplusplus
}
#endif
#endif  // _CC0B9904_81D4_444A_9A8E_4AC9BDAA8D0A_ // NOLINT