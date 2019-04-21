#pragma once
#include <memory>
#include "ctn_mouse_state.h"

namespace centurion {
namespace input {

/**
\brief The IMouseListener class is an interface for objects that responds to
mouse changes.
\since 1.1.0
*/
class IMouseListener {
 protected:
  IMouseListener() = default;

 public:
  virtual ~IMouseListener() = default;

  /**
  \brief Invoked when a mouse button has been pressed.
  \param mouse - a reference to the Mouse instance holding information about the
  mouse state.
  \since 1.1.0
  */
  virtual void MousePressed(const MouseState& mouse) = 0;

  /**
  \brief Invoked when a mouse button has been released.
  \param mouse - a reference to the Mouse instance holding information about the
  mouse state.
  \since 1.1.0
  */
  virtual void MouseReleased(const MouseState& mouse) = 0;
};

typedef std::shared_ptr<IMouseListener> IMouseListener_sptr;
typedef std::unique_ptr<IMouseListener> IMouseListener_uptr;
typedef std::weak_ptr<IMouseListener> IMouseListener_wptr;

}  // namespace input
}  // namespace centurion