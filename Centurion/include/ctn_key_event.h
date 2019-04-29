#pragma once
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_stdinc.h>
#include <memory>

namespace centurion {
namespace events {

/**
\brief The KeyEvent class provides information about a keyboard event.
\since 1.0.0
*/
class KeyEvent final {
 private:
  SDL_Event event;

 public:
  /**
  \param event - the SDL_Event that will serve as the internal representation of
  the KeyEvent.
  */
  explicit KeyEvent(SDL_Event event);

  ~KeyEvent();

  /**
  \brief Indicates whether the keyboard event was triggered by a repeated key. A
  key is usually repeated when it's continously held down.
  \since 1.0.0
  */
  bool IsRepeated() const noexcept;

  /**
  \brief Indicates whether the keyboard event was triggered by a pressed key.
  \since 1.0.0
  */
  bool WasPressed() const noexcept;

  /**
  \brief Indicates whether the keyboard event was triggered by a released key.
  \since 1.0.0
  */
  bool WasReleased() const noexcept;

  /**
  \brief Returns the keycode of the key that triggered this KeyEvent.
  \since 1.0.0
  */
  SDL_Keycode GetKeycode() const noexcept;

  /**
  \brief Returns the event type of this KeyEvent. The possible return
  values are either SDL_KEYDOWN or SDL_KEYUP.
  \since 1.0.0
  */
  Uint32 GetKeyEventType() const noexcept;
};

using KeyEvent_sptr = std::shared_ptr<KeyEvent>;
using KeyEvent_uptr = std::unique_ptr<KeyEvent>;
using KeyEvent_wptr = std::weak_ptr<KeyEvent>;

}  // namespace events
}  // namespace centurion