#pragma once
#include <memory>
#include <vector>
#include "ctn_mouse_listener.h"
#include "mouse_state.h"

namespace centurion {
namespace input {

class MouseListenerComposite;
typedef std::shared_ptr<MouseListenerComposite> MouseListenerComposite_sptr;
typedef std::unique_ptr<MouseListenerComposite> MouseListenerComposite_uptr;
typedef std::weak_ptr<MouseListenerComposite> MouseListenerComposite_wptr;

/**
\brief The MouseListenerComposite class holds instances of IMouseListener.
\since 1.1.0
*/
class MouseListenerComposite final : public centurion::input::IMouseListener {
 private:
  std::vector<centurion::input::IMouseListener_sptr> listeners;

 public:
  MouseListenerComposite();

  ~MouseListenerComposite();

  /**
  \brief Invokes the MousePressed()-method on all of the children.
  \since 1.1.0
  */
  void MousePressed(const centurion::input::MouseState& mouse) override;

  /**
  \brief Invokes the MouseReleased()-method on all of the children.
  \since 1.1.0
  */
  void MouseReleased(const centurion::input::MouseState& mouse) override;

  /**
  \brief Removes all of the children from this MouseListenerComposite.
  \since 1.1.0
  */
  void RemoveChildren() noexcept;

  /**
  \brief Adds a IMouseListener instance to this MouseListenerComposite.
  \since 1.1.0
  */
  void AddChild(centurion::input::IMouseListener_sptr ml);

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

  /**
  \brief Returns a weak pointer that points to a MouseListenerComposite.
  \since 1.1.0
  */
  static MouseListenerComposite_wptr CreateWeak();
};

}  // namespace input
}  // namespace centurion