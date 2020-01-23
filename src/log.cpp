#include "log.h"
#include <cstdarg>
#include <type_traits>

namespace centurion {

static_assert(std::is_final_v<Log>);
static_assert(!std::is_constructible_v<Log>);
static_assert(!std::is_copy_constructible_v<Log>);
static_assert(!std::is_move_constructible_v<Log>);
static_assert(!std::is_copy_assignable_v<Log>);
static_assert(!std::is_move_assignable_v<Log>);

void Log::msgf(Category category, Priority prio, const char* fmt, ...) noexcept {
  if (!fmt) { return; }
  std::va_list args;
  va_start(args, fmt);
  SDL_LogMessageV(static_cast<int>(category), static_cast<SDL_LogPriority>(prio), fmt, args);
}

void Log::msgf(Category category, const char* fmt, ...) noexcept {
  if (!fmt) { return; }
  std::va_list args;
  va_start(args, fmt);

  const auto category_id = static_cast<int>(category);
  const auto prio = SDL_LogGetPriority(category_id);

  SDL_LogMessageV(static_cast<int>(category), prio, fmt, args);
}

void Log::msgf(const char* fmt, ...) noexcept {
  if (!fmt) { return; }
  std::va_list args;
  va_start(args, fmt);

  SDL_LogMessageV(static_cast<int>(Category::App),
                  static_cast<SDL_LogPriority>(Priority::Info),
                  fmt,
                  args);
}

void Log::msg(Category category, Priority prio, const char* msg) noexcept {
  if (!msg) { return; }
  SDL_LogMessageV(static_cast<int>(category),
                  static_cast<SDL_LogPriority>(prio),
                  "%s",
                  const_cast<char*>(msg));
}

void Log::msg(Category category, const char* msg) noexcept {
  if (!msg) { return; }

  const auto category_id = static_cast<int>(category);
  const auto prio = SDL_LogGetPriority(category_id);

  SDL_LogMessageV(static_cast<int>(category),
                  static_cast<SDL_LogPriority>(prio),
                  "%s",
                  const_cast<char*>(msg));
}

void Log::msg(const char* msg) noexcept {
  if (!msg) { return; }
  SDL_Log("%s", msg);
}

void Log::set_priority(Category category, Priority prio) noexcept {
  SDL_LogSetPriority(static_cast<int>(category), static_cast<SDL_LogPriority>(prio));
}

void Log::set_priority(Priority prio) noexcept {
  const auto p = static_cast<SDL_LogPriority>(prio);
  SDL_LogSetAllPriority(p);
  SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, p); // Apparently not set by SDL
}

Priority Log::get_priority(Category category) noexcept {
  return static_cast<Priority>(SDL_LogGetPriority(static_cast<int>(category)));
}

}
