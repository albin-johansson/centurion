#include "platform.hpp"

namespace centurion::platform {

auto id() noexcept -> platform_id
{
  const auto platformName = name();
  if (platformName == "Windows") {
    return platform_id::windows;

  } else if (platformName == "Mac OS X") {
    return platform_id::mac_osx;

  } else if (platformName == "Linux") {
    return platform_id::linux;

  } else if (platformName == "iOS") {
    return platform_id::ios;

  } else if (platformName == "Android") {
    return platform_id::android;

  } else {
    return platform_id::unknown;
  }
}

auto name() noexcept -> std::optional<std::string>
{
  const std::string name{SDL_GetPlatform()};
  if (name == "Unknown") {
    return std::nullopt;
  } else {
    return name;
  }
}

}  // namespace centurion::platform
