#include "window_utils.hpp"

#include <SDL.h>

#include "window.hpp"
#include "window_handle.hpp"

namespace centurion {
namespace {

[[nodiscard]] auto get_renderer(SDL_Window* window) noexcept -> renderer_handle
{
  if (window) {
    return renderer_handle{SDL_GetRenderer(window)};
  } else {
    return renderer_handle{nullptr};
  }
}

}  // namespace

auto get_renderer(const window& window) noexcept -> renderer_handle
{
  return get_renderer(window.get());
}

auto get_renderer(const window_handle& window) noexcept -> renderer_handle
{
  if (window) {
    return get_renderer(window.get());
  } else {
    return renderer_handle{nullptr};
  }
}

}  // namespace centurion
