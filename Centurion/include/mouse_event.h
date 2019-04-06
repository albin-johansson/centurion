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

  int GetMousePressedX() const;

  int GetMousePressedY() const;

  int GetPressedButtonID() const;

  bool WasButtonReleased() const;

  bool WasButtonPressed() const;

  bool WasDoubleClick() const;

  bool IsMouseButtonEvent() const;

  bool IsMouseMotionEvent() const;

  bool IsMouseWheelEvent() const;
};

}  // namespace events
}  // namespace centurion