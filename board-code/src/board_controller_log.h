#ifndef SRC_BOARD_CONTROLLER_LOG
#define SRC_BOARD_CONTROLLER_LOG



#include "rlog/rlogger_wrapper.hpp"

namespace rededa {
  inline RLoggerWrapper& getRBoardLogger() {
    static RLoggerWrapper logger("board");
    return logger;
  }
}

#endif  // SRC_BOARD_CONTROLLER_LOG // NOLINT