#ifndef _DDB01F67_EF11_4EFC_8BC4_EFACAF60A3C6_
#define _DDB01F67_EF11_4EFC_8BC4_EFACAF60A3C6_

#include "common/rededa_error.h"

enum RBoardErrCode
{
  BOARD_ERROR_CODE1 = 10000,  // 正常返回
  BOARD_ERROR_CODE2,          // 非法RBoard handle
  BOARD_ERROR_CODE3,          // 空字符串
  BOARD_ERROR_CODE4,          // 空指针
  BOARD_ERROR_CODE5,          // 空文件
  BOARD_ERROR_CODE6,          // 非法路径
};


#endif  // _DDB01F67_EF11_4EFC_8BC4_EFACAF60A3C6_ // NOLINT