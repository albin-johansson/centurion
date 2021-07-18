#ifndef CENTURION_LOG_MACROS_HEADER
#define CENTURION_LOG_MACROS_HEADER

// clang-format off
#include "../compiler/features.hpp"
// clang-format on

#include <SDL.h>

#include "log.hpp"

#ifndef CENTURION_NO_DEBUG_LOG_MACROS
#ifdef NDEBUG

#define CENTURION_LOG_INFO(fmt, ...)
#define CENTURION_LOG_WARN(fmt, ...)
#define CENTURION_LOG_VERBOSE(fmt, ...)
#define CENTURION_LOG_DEBUG(fmt, ...)
#define CENTURION_LOG_CRITICAL(fmt, ...)
#define CENTURION_LOG_ERROR(fmt, ...)

#else

// clang-format off
#define CENTURION_LOG_INFO(fmt, ...) cen::log::info(CENTURION_VARIADIC(fmt, __VA_ARGS__))
#define CENTURION_LOG_WARN(fmt, ...) cen::log::warn(CENTURION_VARIADIC(fmt, __VA_ARGS__))
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log::verbose(CENTURION_VARIADIC(fmt, __VA_ARGS__))
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log::debug(CENTURION_VARIADIC(fmt, __VA_ARGS__))
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log::critical(CENTURION_VARIADIC(fmt, __VA_ARGS__))
#define CENTURION_LOG_ERROR(fmt, ...) cen::log::error(CENTURION_VARIADIC(fmt, __VA_ARGS__))
// clang-format on

#endif  // NDEBUG
#endif  // CENTURION_NO_DEBUG_LOG_MACROS

#endif  // CENTURION_LOG_MACROS_HEADER
