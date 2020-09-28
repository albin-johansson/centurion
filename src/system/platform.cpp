#include "platform.hpp"

#include <SDL.h>

#include "detail/utils.hpp"

namespace cen::platform {

auto id() noexcept -> platform_id
{
  using detail::equal;

  czstring platform = SDL_GetPlatform();
  if (equal(platform, "Windows")) {
    return platform_id::windows;

  } else if (equal(platform, "Mac OS X")) {
    return platform_id::mac_osx;

  } else if (equal(platform, "Linux")) {
    return platform_id::linuxx;

  } else if (equal(platform, "iOS")) {
    return platform_id::ios;

  } else if (equal(platform, "Android")) {
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
