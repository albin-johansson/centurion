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
  \brief Invoked when the mouse state has been updated.
  \param mouse - a reference to the Mouse instance holding information about the
  mouse state.
  \since 1.1.0
  */
  virtual void MouseStateUpdated(const MouseState& mouse) = 0;
};

using IMouseListener_sptr = std::shared_ptr<IMouseListener>;
using IMouseListener_uptr = std::unique_ptr<IMouseListener>;
using IMouseListener_wptr = std::weak_ptr<IMouseListener>;

}  // namespace input
}  // namespace centurion