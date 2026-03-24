#ifndef _REDEDA_SETTINGS_COMMON_H
#define _REDEDA_SETTINGS_COMMON_H

#include "common/rededa_type.h"

#if defined(REDEDA_SETTINGS_STATIC_LIB)
#define REDEDA_SETTINGS_API
#else // !defined(REDEDA_SETTINGS_STATIC_LIB)

#if defined(_WIN32)
#ifdef REDEDA_SETTINGS_EXPORTS
#define REDEDA_SETTINGS_API __declspec(dllexport)
#else // !REDEDA_SETTINGS_EXPORTS
#define REDEDA_SETTINGS_API __declspec(dllimport)
#endif
#else // !defined(_WIN32)
#define REDEDA_SETTINGS_API __attribute__((visibility("default")))
#endif

#endif
#endif /* _REDEDA_SETTINGS_COMMON_H */