#pragma once
#include <SDL_config.h>
#include <SDL_events.h>
#include <memory>
#include "ctn_key_trigger.h"

namespace centurion {
namespace events {

/**
\brief The KeyboardEvent class provides information about a keyboard event.
\since 1.0.0
*/
class KeyboardEvent {
 private:
  SDL_Event event;

 public:
  /**
  \param event - the SDL_Event that will serve as the internal representation of
  the KeyboardEvent.
  */
  explicit KeyboardEvent(SDL_Event event);

  ~KeyboardEvent();

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
  \brief Returns the keycode of the key that triggered this KeyboardEvent.
  \since 1.0.0
  */
  SDL_Keycode GetKeycode() const noexcept;

  /**
  \brief Returns the event type of this KeyboardEvent. The possible return
  values are either SDL_KEYDOWN or SDL_KEYUP.
  \since 1.0.0
  */
  uint32_t GetKeyEventType() const noexcept;
};

typedef std::shared_ptr<KeyboardEvent> KeyboardEvent_sptr;
typedef std::unique_ptr<KeyboardEvent> KeyboardEvent_uptr;
typedef std::weak_ptr<KeyboardEvent> KeyboardEvent_wptr;

}  // namespace events
}  // namespace centurion