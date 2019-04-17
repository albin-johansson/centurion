#pragma once
#include <memory>
#include <vector>
#include "key_listener.h"
#include "key_listener_composite.h"
#include "key_state.h"
#include "mouse_listener.h"
#include "mouse_listener_composite.h"
#include "mouse_state.h"

namespace centurion {
namespace input {

/**
\brief The InputDispatcher class manages state based input.
\since 1.1.0
*/
class InputDispatcher final {
 private:
  centurion::input::KeyListenerComposite_uptr keyListenerComposite;
  centurion::input::KeyState_uptr keyState;
  centurion::input::MouseListenerComposite_uptr mouseListenerComposite;
  centurion::input::MouseState_uptr mouseState;
  bool shouldQuit;

  void NotifyKeyListeners();

  void NotifyMouseListeners();

 public:
  InputDispatcher();

  ~InputDispatcher();

  /**
  \brief Updates the state of the various input sources.
  \since 1.1.0
  */
  void Update();

  /**
  \brief Adds a MouseListener instance to this input dispatcher.
  \param ml - a pointer to the MouseListener that will be added.
  \since 1.1.0
  */
  void AddMouseListener(centurion::input::MouseListener_sptr ml);

  /**
  \brief Adds a KeyListener instance to this input dispatcher.
  \param kl - a pointer to the KeyListener instance that will be added.
  \since 1.1.0
  */
  void AddKeyListener(centurion::input::KeyListener_sptr kl);

  /**
  \brief Returns true if the user has requested a termination of the
  application. This is usually done by pressing the "x"-button on a window.
  \since 1.1.0
  */
  bool ReceivedQuit() const { return shouldQuit; }

  /**
  \brief Returns a shared_ptr that points to a InputDispatcher.
  \since 1.1.0
  */
  static std::shared_ptr<InputDispatcher> CreateShared();

  /**
  \brief Returns a unique_ptr that points to a InputDispatcher.
  \since 1.1.0
  */
  static std::unique_ptr<InputDispatcher> CreateUnique();

  /**
  \brief Returns a weak_ptr that points to a InputDispatcher.
  \since 1.1.0
  */
  static std::weak_ptr<InputDispatcher> CreateWeak();
};

}  // namespace input
}  // namespace centurion