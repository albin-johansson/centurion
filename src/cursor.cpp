#ifndef CENTURION_CURSOR_SOURCE
#define CENTURION_CURSOR_SOURCE

#include "cursor.h"

#include "centurion_exception.h"
#include "centurion_utils.h"

namespace centurion {
namespace video {

CENTURION_DEF
Cursor::Cursor(SystemCursor id)
{
  cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(id));
  if (!cursor) {
    throw CenturionException{"Failed to create system cursor!"};
  }
}

CENTURION_DEF
Cursor::Cursor(gsl::owner<SDL_Cursor*> cursor_)
{
  if (cursor_) {
    cursor = cursor_;
  } else {
    throw CenturionException{"Can't create cursor from null SDL_Cursor!"};
  }
}

CENTURION_DEF
Cursor::Cursor(const Surface& surface_, math::IPoint hotspot)
{
  surface = SDL_DuplicateSurface(surface_.get_internal());
  if (!surface) {
    throw CenturionException{"Failed to create color cursor!"};
  }

  cursor = SDL_CreateColorCursor(surface, hotspot.x(), hotspot.y());
  if (!cursor) {
    throw CenturionException{"Failed to create color cursor!"};
  }
}

CENTURION_DEF
Cursor::Cursor(Cursor&& other) noexcept
{
  destroy();

  cursor = other.cursor;
  surface = other.surface;

  other.cursor = nullptr;
  other.surface = nullptr;
}

CENTURION_DEF
Cursor& Cursor::operator=(Cursor&& other) noexcept
{
  destroy();

  cursor = other.cursor;
  surface = other.surface;

  other.cursor = nullptr;
  other.surface = nullptr;

  return *this;
}

CENTURION_DEF
Cursor::~Cursor() noexcept
{
  destroy();
}

CENTURION_DEF
void Cursor::destroy() noexcept
{
  if (cursor) {
    SDL_FreeCursor(cursor);
  }

  if (surface) {
    SDL_FreeSurface(surface);
  }
}

CENTURION_DEF
std::unique_ptr<Cursor> Cursor::unique(SystemCursor id)
{
  return centurion::make_unique<Cursor>(id);
}

CENTURION_DEF
std::unique_ptr<Cursor> Cursor::unique(gsl::owner<SDL_Cursor*> cursor)
{
  return centurion::make_unique<Cursor>(cursor);
}

CENTURION_DEF
std::unique_ptr<Cursor> Cursor::unique(const Surface& surface,
                                       math::IPoint hotspot)
{
  return centurion::make_unique<Cursor>(surface, hotspot);
}

CENTURION_DEF
std::shared_ptr<Cursor> Cursor::shared(SystemCursor id)
{
  return std::make_shared<Cursor>(id);
}

CENTURION_DEF
std::shared_ptr<Cursor> Cursor::shared(gsl::owner<SDL_Cursor*> cursor)
{
  return std::make_shared<Cursor>(cursor);
}

CENTURION_DEF
std::shared_ptr<Cursor> Cursor::shared(const Surface& surface,
                                       math::IPoint hotspot)
{
  return std::make_shared<Cursor>(surface, hotspot);
}

CENTURION_DEF
void Cursor::enable() noexcept
{
  SDL_SetCursor(cursor);
}

CENTURION_DEF
bool Cursor::is_enabled() const noexcept
{
  return SDL_GetCursor() == cursor;
}

CENTURION_DEF
void Cursor::force_redraw() noexcept
{
  SDL_SetCursor(nullptr);
}

CENTURION_DEF
void Cursor::reset() noexcept
{
  SDL_SetCursor(SDL_GetDefaultCursor());
}

CENTURION_DEF
void Cursor::set_visible(bool visible) noexcept
{
  SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

CENTURION_DEF
bool Cursor::visible() noexcept
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

CENTURION_DEF
bool operator==(SystemCursor lhs, SDL_SystemCursor rhs) noexcept
{
  return static_cast<SDL_SystemCursor>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(SDL_SystemCursor lhs, SystemCursor rhs) noexcept
{
  return lhs == static_cast<SDL_SystemCursor>(rhs);
}

CENTURION_DEF
bool operator!=(SystemCursor lhs, SDL_SystemCursor rhs) noexcept
{
  return !(lhs == rhs);
}

CENTURION_DEF
bool operator!=(SDL_SystemCursor lhs, SystemCursor rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_CURSOR_SOURCE