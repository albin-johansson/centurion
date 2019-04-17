#pragma once
#include <memory>
#include <vector>
#include "centurion_input.h"

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
};

}  // namespace input
}  // namespace centurion