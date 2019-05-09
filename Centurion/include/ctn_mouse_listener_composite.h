#pragma once
#include <memory>
#include <vector>
#include "ctn_mouse_listener.h"
#include "ctn_mouse_state.h"

namespace centurion {
namespace input {

class MouseListenerComposite;
using MouseListenerComposite_sptr = std::shared_ptr<MouseListenerComposite>;
using MouseListenerComposite_uptr = std::unique_ptr<MouseListenerComposite>;
using MouseListenerComposite_wptr = std::weak_ptr<MouseListenerComposite>;

/**
\brief The MouseListenerComposite class holds instances of IMouseListener.
\since 1.1.0
*/
class MouseListenerComposite final : public IMouseListener {
 private:
  std::vector<IMouseListener_sptr> children;

 public:
  MouseListenerComposite();

  ~MouseListenerComposite();

  /**
  \brief Invokes the MouseStateUpdated()-method on all of the children.
  \param state - a reference to the MouseState instance holding information
  about the mouse state.
  \since 1.1.0
  */
  void MouseStateUpdated(const MouseState& state) override;

  /**
  \brief Removes all of the children from this MouseListenerComposite.
  \since 1.1.0
  */
  void RemoveChildren() noexcept;

  /**
  \brief Adds a IMouseListener instance to this MouseListenerComposite.
  \param child - the IMouseListener instance that will be added.
  \since 1.1.0
  */
  void AddChild(IMouseListener_sptr child);

  /**
  \brief Removes a child from this MouseListenerComposite.
  \param child - a pointer to the child that will be removed.
  \note this method has no effect if the supplied pointer is nullptr.
  \since 2.0.0
  */
  void RemoveChild(IMouseListener_sptr child);

  /**
  \brief Returns a shared pinter that points to a MouseListenerComposite.
  \since 1.1.0
  */
  static MouseListenerComposite_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to a MouseListenerComposite.
  \since 1.1.0
  */
  static MouseListenerComposite_uptr CreateUnique();
};

}  // namespace input
}  // namespace centurion