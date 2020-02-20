#ifndef CENTURION_CURSOR_SOURCE
#define CENTURION_CURSOR_SOURCE

#include "cursor.h"

#include "centurion_exception.h"

namespace centurion {

Cursor::Cursor() { cursor = SDL_GetDefaultCursor(); }

Cursor::Cursor(CursorID id)
{
  cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(id));
}

Cursor::Cursor(SDL_Cursor* cursor)
{
  if (cursor) {
    this->cursor = cursor;
  } else {
    throw CenturionException{"Can't create cursor from null SDL_Cursor!"};
  }
}

Cursor::Cursor(SDL_Surface* surface, math::IPoint hotspot)
{
  cursor = SDL_CreateColorCursor(surface, hotspot.get_x(), hotspot.get_y());
}

Cursor::~Cursor() noexcept
{
  if (cursor) {
    SDL_FreeCursor(cursor);
  }
}

void Cursor::set_visible(bool visible) noexcept
{
  SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

bool Cursor::is_visible() noexcept
{
  return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

}  // namespace centurion

#endif  // CENTURION_CURSOR_SOURCE