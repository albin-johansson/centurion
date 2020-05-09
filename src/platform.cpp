#ifndef CENTURION_PLATFORM_SOURCE
#define CENTURION_PLATFORM_SOURCE

#include "platform.h"

#include <string>

namespace centurion {

CENTURION_DEF
PlatformID Platform::id() noexcept
{
  const auto platform = name();
  if (platform == "Windows") {
    return PlatformID::Windows;
  } else if (platform == "Mac OS X") {
    return PlatformID::MacOSX;
  } else if (platform == "Linux") {
    return PlatformID::Linux;
  } else if (platform == "iOS") {
    return PlatformID::Ios;
  } else if (platform == "Android") {
    return PlatformID::Android;
  } else {
    return PlatformID::Unknown;
  }
}

CENTURION_DEF
Optional<std::string> Platform::name() noexcept
{
  const std::string name{SDL_GetPlatform()};
  if (name == "Unknown") {
    return nothing;
  } else {
    return name;
  }
}

}  // namespace centurion

#endif  // CENTURION_PLATFORM_SOURCE