#pragma once
#include <SDL_events.h>

namespace centurion {
namespace events {

class Event {
 private:
  SDL_Event event;

 public:
  explicit Event(SDL_Event event);

  ~Event();

  inline SDL_KeyboardEvent GetKeyInfo() const { return event.key; }

  inline SDL_MouseMotionEvent GetMouseMotionInfo() const {
    return event.motion;
  }

  inline SDL_MouseButtonEvent GetMouseButtonInfo() const {
    return event.button;
  }

  inline bool IsKeyEvent() const {
    return (event.type == SDL_KEYUP) || (event.type == SDL_KEYDOWN);
  }

  inline bool IsMouseEvent() const {
    return (event.type == SDL_MOUSEMOTION) ||
           (event.type == SDL_MOUSEBUTTONUP) ||
           (event.type == SDL_MOUSEWHEEL) || (event.type == SDL_MOUSEMOTION);
  }

  inline SDL_Event GetSDLVersion() const { return event; }
};

}  // namespace events
}  // namespace centurion