#include "platform.hpp"

#include <SDL.h>

namespace cen::platform {

auto id() noexcept -> platform_id
{
  const auto platformName = name();
  if (platformName == "Windows") {
    return platform_id::windows;

  } else if (platformName == "Mac OS X") {
    return platform_id::mac_osx;

  } else if (platformName == "Linux") {
    return platform_id::linuxx;

  } else if (platformName == "iOS") {
    return platform_id::ios;

  } else if (platformName == "Android") {
    return platform_id::android;

  } else {
    return platform_id::unknown;
  }
}

auto is_windows() noexcept -> bool
{
  return id() == platform_id::windows;
}

auto is_mac_osx() noexcept -> bool
{
  return id() == platform_id::mac_osx;
}

auto is_linux() noexcept -> bool
{
  return id() == platform_id::linuxx;
}

auto is_ios() noexcept -> bool
{
  return id() == platform_id::ios;
}

auto is_android() noexcept -> bool
{
  return id() == platform_id::android;
}

auto name() -> std::optional<std::string>
{
  const std::string name{SDL_GetPlatform()};
  if (name == "Unknown") {
    return std::nullopt;
  } else {
    return name;
  }
}

}  // namespace cen::platform
