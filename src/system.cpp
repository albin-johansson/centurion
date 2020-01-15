#include "system.h"
#include <string>
#include <SDL.h>

namespace centurion {

static constexpr const char* a = "";

Platform System::get_platform() noexcept {
  const std::string name{SDL_GetPlatform()};
  if (name == "Windows") {
    return Platform::Windows;
  } else if (name == "Mac OS X") {
    return Platform::MacOSX;
  } else if (name == "Linux") {
    return Platform::Linux;
  } else if (name == "iOS") {
    return Platform::Ios;
  } else if (name == "Android") {
    return Platform::Android;
  } else {
    return Platform::Unknown;
  }
}

std::optional<std::string> System::get_platform_name() noexcept {
  const std::string name{SDL_GetPlatform()};
  if (name == "Unknown") {
    return std::nullopt;
  } else {
    return name;
  }
}

int CPU::get_cache_line_size() noexcept {
  return SDL_GetCPUCacheLineSize();
}

int CPU::get_cores() noexcept {
  return SDL_GetCPUCount();
}

int RAM::get_size_mb() noexcept {
  return SDL_GetSystemRAM();
}

int RAM::get_size_gb() noexcept {
  return get_size_mb() / 1'000;
}

}
