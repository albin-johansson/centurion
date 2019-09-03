#pragma once
#include <SDL_events.h>
#include <memory>

namespace centurion {
namespace events {

/**
\brief The MouseEvent class provides information about a mouse event.
\since 1.0.0
*/
class MouseEvent final {
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
  \since 1.0.0
  */
  int GetMousePressedX() const noexcept;

  /**
  \brief Returns the y-coordinate of the mouse press.
  \since 1.0.0
  */
  int GetMousePressedY() const noexcept;

  /**
  \brief Returns the ID of the pressed mouse button.
  \since 1.0.0
  */
  int GetPressedButtonID() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a released mouse
  button.
  \since 1.0.0
  */
  bool WasButtonReleased() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a pressed mouse
  button.
  \since 1.0.0
  */
  bool WasButtonPressed() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a double click of a
  mouse button.
  \since 1.0.0
  */
  bool WasDoubleClick() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse button event.
  \since 1.0.0
  */
  bool IsMouseButtonEvent() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse motion event.
  \since 1.0.0
  */
  bool IsMouseMotionEvent() const noexcept;

  /**
  \brief Indicates whether the MouseEvent was triggered by a mouse wheel event.
  \since 1.0.0
  */
  bool IsMouseWheelEvent() const noexcept;
};

using MouseEvent_sptr = std::shared_ptr<MouseEvent>;
using MouseEvent_uptr = std::unique_ptr<MouseEvent>;
using MouseEvent_wptr = std::weak_ptr<MouseEvent>;

}  // namespace events
}  // namespace centurion