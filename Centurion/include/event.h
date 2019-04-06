#pragma once
#include <SDL_events.h>
#include "keyboard_event.h"
#include "mouse_event.h"

namespace centurion {
namespace events {

class Event {
 private:
  SDL_Event event;
  centurion::events::MouseEvent mouseEvent;
  centurion::events::KeyboardEvent keyEvent;

 public:
  explicit Event(SDL_Event event);

  ~Event();

  bool IsKeyEvent() const;

  bool IsMouseEvent() const;

  inline centurion::events::MouseEvent GetMouseInfo() const {
    return mouseEvent;
  }

  inline centurion::events::KeyboardEvent GetKeyboardInfo() const {
    return keyEvent;
  }

  inline SDL_Event GetSDLVersion() const { return event; }
};

}  // namespace events
}  // namespace centurion