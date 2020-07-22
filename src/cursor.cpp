#include "cursor.hpp"

#include <utility>

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

cursor::cursor(gsl::owner<SDL_Cursor*> sdlCursor) : m_cursor{sdlCursor}
{
  if (!sdlCursor) {
    throw centurion_exception{"Can't create Cursor from null SDL_Cursor!"};
  }
}

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

cursor::cursor(cursor&& other) noexcept
{
  move(std::move(other));
}

cursor::~cursor() noexcept
{
  destroy();
}

void cursor::destroy() noexcept
{
  if (m_cursor) {
    SDL_FreeCursor(m_cursor);
  }

  if (m_surface) {
    SDL_FreeSurface(m_surface);
  }
}

void cursor::move(cursor&& other) noexcept
{
  destroy();

  m_cursor = other.m_cursor;
  m_surface = other.m_surface;

  other.m_cursor = nullptr;
  other.m_surface = nullptr;
}

auto cursor::operator=(cursor&& other) noexcept -> cursor&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

auto cursor::unique(system_cursor id) -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(id);
}

auto cursor::unique(gsl::owner<SDL_Cursor*> sdlCursor)
    -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(sdlCursor);
}

auto cursor::unique(const surface& surface, const point_i& hotspot)
    -> std::unique_ptr<cursor>
{
  return std::make_unique<cursor>(surface, hotspot);
}

auto cursor::shared(system_cursor id) -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(id);
}

auto cursor::shared(gsl::owner<SDL_Cursor*> sdlCursor)
    -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(sdlCursor);
}

auto cursor::shared(const surface& surface, const point_i& hotspot)
    -> std::shared_ptr<cursor>
{
  return std::make_shared<cursor>(surface, hotspot);
}

void cursor::enable() noexcept
{
  SDL_SetCursor(m_cursor);
}

auto cursor::is_enabled() const noexcept -> bool
{
  return SDL_GetCursor() == m_cursor;
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
