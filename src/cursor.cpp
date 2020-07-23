#include "cursor.hpp"

#include "centurion_utils.hpp"
#include "error.hpp"

namespace centurion {

cursor::cursor(system_cursor id)
    : m_cursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(id))}
{
  if (!m_cursor) {
    throw detail::core_error("Failed to create system cursor!");
  }
}

cursor::cursor(nn_owner<SDL_Cursor*> sdlCursor) : m_cursor{sdlCursor}
{}

cursor::cursor(const surface& surface, const point_i& hotspot)
    : m_cursor{SDL_CreateColorCursor(surface.get(), hotspot.x(), hotspot.y())}
{
  if (!m_cursor) {
    throw detail::core_error("Failed to create color cursor!");
  }
}

auto cursor::unique(system_cursor id) -> uptr
{
  return std::make_unique<cursor>(id);
}

auto cursor::unique(nn_owner<SDL_Cursor*> sdlCursor) -> uptr
{
  return std::make_unique<cursor>(sdlCursor);
}

auto cursor::unique(const surface& surface, const point_i& hotspot) -> uptr
{
  return std::make_unique<cursor>(surface, hotspot);
}

auto cursor::shared(system_cursor id) -> sptr
{
  return std::make_shared<cursor>(id);
}

auto cursor::shared(nn_owner<SDL_Cursor*> sdlCursor) -> sptr
{
  return std::make_shared<cursor>(sdlCursor);
}

auto cursor::shared(const surface& surface, const point_i& hotspot) -> sptr
{
  return std::make_shared<cursor>(surface, hotspot);
}

void cursor::enable() noexcept
{
  SDL_SetCursor(m_cursor.get());
}

auto cursor::is_enabled() const noexcept -> bool
{
  return SDL_GetCursor() == m_cursor.get();
}

void cursor::force_redraw() noexcept
{
  SDL_SetCursor(nullptr);
}

void cursor::reset() noexcept
{
  SDL_SetCursor(SDL_GetDefaultCursor());
}

void cursor::set_visible(bool visible) noexcept
{
  SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

auto cursor::visible() noexcept -> bool
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

}  // namespace centurion
