#pragma once
#include <SDL_events.h>
#include <memory>

namespace centurion {
namespace events {

/**
\brief The MouseEvent class provides information about a mouse event.
*/
class MouseEvent {
 private:
  SDL_Event event;

 public:
  /**
  \param event - the SDL_Event that will serve as the internal representation of
  the MouseEvent.
  */
  explicit MouseEvent(SDL_Event event);

  ~MouseEvent();

  /**
  \brief Returns the x-coordinate of the mouse press.
  */
  int GetMousePressedX() const;

  /**
  \brief Returns the y-coordinate of the mouse press.
  */
  int GetMousePressedY() const;

  /**
  \brief Returns the ID of the pressed mouse button.
  */
  int GetPressedButtonID() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a released mouse
  button.
  */
  bool WasButtonReleased() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a pressed mouse
  button.
  */
  bool WasButtonPressed() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a double click of a
  mouse button.
  */
  bool WasDoubleClick() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse button event.
  */
  bool IsMouseButtonEvent() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse motion event.
  */
  bool IsMouseMotionEvent() const;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse wheel event.
  */
  bool IsMouseWheelEvent() const;
};

typedef std::shared_ptr<centurion::events::MouseEvent> MouseEvent_sptr;
typedef std::unique_ptr<centurion::events::MouseEvent> MouseEvent_uptr;
typedef std::weak_ptr<centurion::events::MouseEvent> MouseEvent_wptr;

}  // namespace events
}  // namespace centurion