
#include "board_controller.h"

#include "board.h"
#include "rededa/board/board_cpp.h"



namespace rededa{

REDEDA_BOARD_API std::shared_ptr<RBoard> board_acquire(){
  auto& ctrl = RBoardController::instance();
  return ctrl.create();
}

REDEDA_BOARD_API void board_release(std::shared_ptr<RBoard> obj){
  RBoardController::instance().destroy(obj->handle());
}

RBoardController& RBoardController::instance() {
  static RBoardController instance;
  return instance;
}

std::shared_ptr<RBoard> RBoardController::create() {
  std::lock_guard lock(mMutex);
  auto handle = mNextHandle++;
  auto rev =  std::make_shared<RBoard>(handle);
  mInstances[handle] = rev;
  return rev;
}

void RBoardController::destroy(rhandle_t handle) {
  std::lock_guard lock(mMutex);
  auto it = mInstances.find(handle);
  if (it != mInstances.end()) {
    mInstances.erase(it);
  }
}

std::shared_ptr<RBoard> RBoardController::get(rhandle_t handle) {
  std::lock_guard lock(mMutex);
  auto it = mInstances.find(handle);
  if (it != mInstances.end()) {
    return it->second;
  }
  return nullptr;
}

std::shared_ptr<RBoard> rededa::RBoardController::get(const std::string &path)
{
    std::lock_guard lock(mMutex);
    for(const auto& [handle, ptr] : mInstances)
    {
        if(ptr)
        {
            auto boardPath = ptr -> getBoardFileName();
            if(boardPath.compare(path) == 0)
            {
                return ptr;
            }
        }
    }
    return nullptr;
}
}  // namespace rededa