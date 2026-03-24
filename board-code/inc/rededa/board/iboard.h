#ifndef _00E92971_603D_4584_81CA_8DDDD799949D_
#define _00E92971_603D_4584_81CA_8DDDD799949D_


#include "common.h"

namespace rededa {
class REDEDA_BOARD_API IRBoard {
public:
  virtual ~IRBoard() = default;

  // @brief get handle
  // @return handle
  virtual rhandle_t handle() const = 0;

  // @brief api
  // @param[in] param1 参数1, 先输入参数，再输出参数
  // @param[out] param2 参数2
  // @return error code
  virtual rerror_t api(int param1, int* param2) = 0;
};

}  // namespace rededa


#endif  // _00E92971_603D_4584_81CA_8DDDD799949D_ // NOLINT