#ifndef _097F10E9_3139_4588_B095_6A1DE6457B1A_
#define _097F10E9_3139_4588_B095_6A1DE6457B1A_




#include "common/rededa_type.h"

#if defined(REDEDA_BOARD_STATIC_LIB)
#define REDEDA_BOARD_API
#else // !defined(REDEDA_BOARD_STATIC_LIB)

#if defined(_WIN32)
#ifdef REDEDA_BOARD_EXPORTS
#define REDEDA_BOARD_API __declspec(dllexport)
#else // !REDEDA_BOARD_EXPORTS
#define REDEDA_BOARD_API __declspec(dllimport)
#endif
#else // !defined(_WIN32)
#define REDEDA_BOARD_API __attribute__((visibility("default")))
#endif

#endif

#endif  // _097F10E9_3139_4588_B095_6A1DE6457B1A_ // NOLINT