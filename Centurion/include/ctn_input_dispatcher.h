#pragma once
#include <memory>
#include <vector>
#include "ctn_key_listener.h"
#include "ctn_key_listener_composite.h"
#include "ctn_key_state.h"
#include "ctn_mouse_listener.h"
#include "ctn_mouse_listener_composite.h"
#include "ctn_mouse_state.h"

namespace centurion {
namespace input {

class InputDispatcher;
using InputDispatcher_sptr = std::shared_ptr<InputDispatcher>;
using InputDispatcher_uptr = std::unique_ptr<InputDispatcher>;
using InputDispatcher_wptr = std::weak_ptr<InputDispatcher>;

/**
\brief The InputDispatcher class manages state based input.
\since 1.1.0
*/
class InputDispatcher final {
 private:
  KeyListenerComposite_uptr keyListenerComposite = nullptr;
  MouseListenerComposite_uptr mouseListenerComposite = nullptr;
  KeyState_uptr keyState = nullptr;
  MouseState_uptr mouseState = nullptr;
  bool shouldQuit = false;
  bool shouldRevalidateImages = false;

  void NotifyKeyListeners();

  void NotifyMouseListeners();

  inline bool IsEventActive(Uint32 type) const noexcept {
    return SDL_PeepEvents(NULL, 0, SDL_PEEKEVENT, type, type) > 0;
  }

 public:
  InputDispatcher();

  ~InputDispatcher();

  /**
  \brief Updates the state of the various input sources.
  \since 1.1.0
  */
  void Update();

  /**
  \brief Adds a IMouseListener instance to this input dispatcher.
  \param ml - a pointer to the IMouseListener that will be added.
  \since 1.1.0
  */
  void AddMouseListener(IMouseListener_sptr ml);

  /**
  \brief Adds a IKeyListener instance to this input dispatcher.
  \param kl - a pointer to the IKeyListener instance that will be added.
  \since 1.1.0
  */
  void AddKeyListener(IKeyListener_sptr kl);

  /**
  \brief Deactivates the image revalidation flag. Use this when you've dealt
  with revalidating your images.
  \since 2.0.0
  */
  void ResetRevalidationFlag() noexcept;

  /**
  \brief Returns true if the user has requested a termination of the
  application. This is usually done by pressing the "x"-button on a sdlWindow.
  \since 1.1.0
  */
  inline bool ReceivedQuit() const noexcept { return shouldQuit; }

  /**
  \brief Returns true if images need to be revalidated.
  \since 2.0.0
  */
  inline bool ShouldRevalidateImages() const noexcept {
    return shouldRevalidateImages;
  }

  /**
  \brief Returns a shared pointer that points to an InputDispatcher instance.
  \since 1.1.0
  */
  static InputDispatcher_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to an InputDispatcher instance.
  \since 1.1.0
  */
  static InputDispatcher_uptr CreateUnique();

  /**
  \brief Returns a weak pointer that points to an InputDispatcher instance.
  \since 1.1.0
  */
  static InputDispatcher_wptr CreateWeak();
};

}  // namespace input
}  // namespace centurion