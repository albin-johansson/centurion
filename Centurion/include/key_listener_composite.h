#pragma once
#include <memory>
#include <vector>
#include "key_listener.h"
#include "key_state.h"

namespace centurion {
namespace input {

/**
\brief The KeyListenerComposite class holds instances of KeyListener.
\since 1.1.0
*/
class KeyListenerComposite final : public centurion::input::KeyListener {
 private:
  std::vector<centurion::input::KeyListener_sptr> listeners;

 public:
  KeyListenerComposite();

  ~KeyListenerComposite();

  void KeyPressed(const centurion::input::KeyState& state) override;

  void KeyReleased(const centurion::input::KeyState& state) override;

  /**
  \brief Adds a KeyListener instance to this LeyListenerComposite.
  \since 1.1.0
  */
  void AddChild(centurion::input::KeyListener_sptr kl);

  /**
  \brief Removes all of this KeyListenerComposite's children.
  \since 1.1.0
  */
  void RemoveChildren();
};

typedef std::shared_ptr<centurion::input::KeyListenerComposite>
    KeyListenerComposite_sptr;
typedef std::unique_ptr<centurion::input::KeyListenerComposite>
    KeyListenerComposite_uptr;
typedef std::weak_ptr<centurion::input::KeyListenerComposite>
    KeyListenerComposite_wptr;

}  // namespace input
}  // namespace centurion