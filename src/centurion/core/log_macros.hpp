#ifndef CENTURION_LOG_MACROS_HEADER
#define CENTURION_LOG_MACROS_HEADER

#include <SDL.h>

#include "../compiler/features.hpp"
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

#if CENTURION_HAS_FEATURE_CPP20

// clang-format off
#define CENTURION_LOG_INFO(fmt, ...) cen::log::info(fmt __VA_OPT__(,) __VA_ARGS__)
#define CENTURION_LOG_WARN(fmt, ...) cen::log::warn(fmt __VA_OPT__(,) __VA_ARGS__)
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log::verbose(fmt __VA_OPT__(,) __VA_ARGS__)
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log::debug(fmt __VA_OPT__(,) __VA_ARGS__)
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log::critical(fmt __VA_OPT__(,) __VA_ARGS__)
#define CENTURION_LOG_ERROR(fmt, ...) cen::log::error(fmt __VA_OPT__(,) __VA_ARGS__)
// clang-format on

#else

// clang-format off
#define CENTURION_LOG_INFO(fmt, ...) cen::log::info(fmt, __VA_ARGS__)
#define CENTURION_LOG_WARN(fmt, ...) cen::log::warn(fmt, __VA_ARGS__)
#define CENTURION_LOG_VERBOSE(fmt, ...) cen::log::verbose(fmt, __VA_ARGS__)
#define CENTURION_LOG_DEBUG(fmt, ...) cen::log::debug(fmt, __VA_ARGS__)
#define CENTURION_LOG_CRITICAL(fmt, ...) cen::log::critical(fmt, __VA_ARGS__)
#define CENTURION_LOG_ERROR(fmt, ...) cen::log::error(fmt, __VA_ARGS__)
// clang-format on

#endif  // CENTURION_HAS_FEATURE_CPP20

#endif  // NDEBUG
#endif  // CENTURION_NO_DEBUG_LOG_MACROS

#endif  // CENTURION_LOG_MACROS_HEADER
