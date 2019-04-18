#pragma once
#include <memory>
#include "mouse_state.h"

namespace centurion {
namespace input {

/**
\brief The MouseListener class is an interface for objects that responds to
mouse changes.
\since 1.1.0
*/
class MouseListener {
 protected:
  MouseListener() = default;

 public:
  virtual ~MouseListener() = default;

  /**
  \brief Invoked when a mouse button has been pressed.
  \param mouse - a reference to the Mouse instance holding information about the
  mouse state.
  \since 1.1.0
  */
  virtual void MousePressed(const centurion::input::MouseState& mouse) = 0;

  /**
  \brief Invoked when a mouse button has been released.
  \param mouse - a reference to the Mouse instance holding information about the
  mouse state.
  \since 1.1.0
  */
  virtual void MouseReleased(const centurion::input::MouseState& mouse) = 0;
};

typedef std::shared_ptr<MouseListener> MouseListener_sptr;
typedef std::unique_ptr<MouseListener> MouseListener_uptr;
typedef std::weak_ptr<MouseListener> MouseListener_wptr;

}  // namespace input
}  // namespace centurion