#pragma once
#include <memory>
#include "key_state.h"

namespace centurion {
namespace input {

/**
\brief The KeyListener class is an interface for objects that listen to key
actions.
\since 1.1.0
*/
class KeyListener {
 protected:
  KeyListener() = default;

 public:
  virtual ~KeyListener() = default;

  /**
  \brief Invoked when a key has been pressed.
  \param state - a reference to the KeyState instance holding information about
  the key state.
  \since 1.1.0
  */
  virtual void KeyPressed(const centurion::input::KeyState& state) = 0;

  /**
  \brief Invoked when a key has been released.
  \param state - a reference to the KeyState instance holding information
  about the key state.
  \since 1.1.0
  */
  virtual void KeyReleased(const centurion::input::KeyState& state) = 0;
};

typedef std::shared_ptr<KeyListener> KeyListener_sptr;
typedef std::unique_ptr<KeyListener> KeyListener_uptr;
typedef std::weak_ptr<KeyListener> KeyListener_wptr;

}  // namespace input
}  // namespace centurion