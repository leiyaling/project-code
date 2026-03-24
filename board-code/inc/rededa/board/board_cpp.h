#ifndef _CD4BF125_3204_4E8A_9760_CB9D75B6AF08_
#define _CD4BF125_3204_4E8A_9760_CB9D75B6AF08_

#include <memory>

#include "common.h"
#include "iboard.h"

namespace rededa {

  // @brief Acuqire a board object
  // @return std::shared_ptr<IRBoard>
  REDEDA_BOARD_API std::shared_ptr<RBoard> board_acquire();

  // @brief Release a board object
  // @param[in] obj std::shared_ptr<Iboard>
  REDEDA_BOARD_API void board_release(std::shared_ptr<RBoard> obj);

}  // namespace rededa


#endif  // _CD4BF125_3204_4E8A_9760_CB9D75B6AF08_ // NOLINT

