#pragma once
#include <SDL_events.h>

namespace centurion {
namespace events {

class MouseEvent {
 private:
  SDL_Event event;

 public:
  explicit MouseEvent(SDL_Event event);

  ~MouseEvent();

  int GetMousePressedX();

  int GetMousePressedY();

  int GetPressedButtonID();

  bool WasButtonReleased();

  bool WasButtonPressed();

  bool WasDoubleClick();

  bool IsMousePressedEvent();

  bool IsMouseMotionEvent();

  bool IsMouseWheelEvent();
};

}  // namespace events
}  // namespace centurion