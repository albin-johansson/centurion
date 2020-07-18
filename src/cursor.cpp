#ifndef CENTURION_CURSOR_SOURCE
#define CENTURION_CURSOR_SOURCE

#include "cursor.hpp"

#include "centurion_utils.hpp"
#include "error.hpp"

namespace centurion {

CENTURION_DEF
cursor::cursor(system_cursor id)
{
  m_cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(id));
  if (!m_cursor) {
    throw detail::core_error("Failed to create system cursor!");
  }
}

CENTURION_DEF
cursor::cursor(gsl::owner<SDL_Cursor*> sdlCursor)
{
  if (sdlCursor) {
    m_cursor = sdlCursor;
  } else {
    throw centurion_exception{"Can't create Cursor from null SDL_Cursor!"};
  }
}

CENTURION_DEF
cursor::cursor(const surface& surface, const point_i& hotspot)
{
  m_surface = SDL_DuplicateSurface(surface.get());
  if (!m_surface) {
    throw detail::core_error("Failed to create color cursor!");
  }

  m_cursor = SDL_CreateColorCursor(m_surface, hotspot.x(), hotspot.y());
  if (!m_cursor) {
    SDL_FreeSurface(m_surface);
    throw detail::core_error("Failed to create color cursor!");
  }
}

CENTURION_DEF
cursor::cursor(cursor&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
cursor::~cursor() noexcept
{
  destroy();
}

CENTURION_DEF
void cursor::destroy() noexcept
{
  if (m_cursor) {
    SDL_FreeCursor(m_cursor);
  }

  if (m_surface) {
    SDL_FreeSurface(m_surface);
  }
}

CENTURION_DEF
void cursor::move(cursor&& other) noexcept
{
  destroy();

  m_cursor = other.m_cursor;
  m_surface = other.m_surface;

  other.m_cursor = nullptr;
  other.m_surface = nullptr;
}

CENTURION_DEF
auto cursor::operator=(cursor&& other) noexcept -> cursor&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
auto cursor::unique(system_cursor id) -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(id);
}

CENTURION_DEF
auto cursor::unique(gsl::owner<SDL_Cursor*> sdlCursor)
    -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(sdlCursor);
}

CENTURION_DEF
auto cursor::unique(const surface& surface, const point_i& hotspot)
    -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(surface, hotspot);
}

CENTURION_DEF
auto cursor::shared(system_cursor id) -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(id);
}

CENTURION_DEF
auto cursor::shared(gsl::owner<SDL_Cursor*> sdlCursor)
    -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(sdlCursor);
}

CENTURION_DEF
auto cursor::shared(const surface& surface, const point_i& hotspot)
    -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(surface, hotspot);
}

CENTURION_DEF
void cursor::enable() noexcept
{
  SDL_SetCursor(m_cursor);
}

CENTURION_DEF
auto cursor::is_enabled() const noexcept -> bool
{
  return SDL_GetCursor() == m_cursor;
}

CENTURION_DEF
void cursor::force_redraw() noexcept
{
  SDL_SetCursor(nullptr);
}

CENTURION_DEF
void cursor::reset() noexcept
{
  SDL_SetCursor(SDL_GetDefaultCursor());
}

CENTURION_DEF
void cursor::set_visible(bool visible) noexcept
{
  SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

CENTURION_DEF
auto cursor::visible() noexcept -> bool
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

}  // namespace centurion

#endif  // CENTURION_CURSOR_SOURCE