#ifndef _C8A0BA13_9708_4877_8170_70ECFAF2FC82_
#define _C8A0BA13_9708_4877_8170_70ECFAF2FC82_



#include <memory>
#include <mutex>
#include <unordered_map>

#include "rededa/board/common.h"
#include "board.h"

namespace rededa {
class RBoardController final{
  public:
    // @brief get instance. singleton.
    // @return instance
    static RBoardController& instance();

    // @brief create logic instance
    // @return logic instance
    std::shared_ptr<RBoard> create();

    // @brief destroy logic instance
    // @param[in] handle
    void destroy(rhandle_t handle);

    std::shared_ptr<RBoard> get(rhandle_t handle);

    std::shared_ptr<RBoard> get(const std::string& path);

  protected:
    RBoardController() = default;
    RBoardController(RBoardController const&) = delete;
    RBoardController operator=(RBoardController const&) = delete;
  private:
    std::mutex mMutex;
    rhandle_t mNextHandle{1};  ///< next handle
    std::unordered_map<rhandle_t, std::shared_ptr<RBoard>> mInstances;
  };
}  // namespace rededa


#endif  // _C8A0BA13_9708_4877_8170_70ECFAF2FC82_ // NOLINT