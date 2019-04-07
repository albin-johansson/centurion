#pragma once
#include <SDL_config.h>
#include <SDL_events.h>
#include "key_trigger.h"

namespace centurion {
namespace events {

/**
\brief The KeyboardEvent class provides information about a keyboard event.
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
  */
  bool IsRepeated() const;

  /**
  \brief Indicates whether the keyboard event was triggered by a pressed key.
  */
  bool WasPressed() const;

  /**
  \brief Indicates whether the keyboard event was triggered by a released key.
  */
  bool WasReleased() const;

  /**
  \brief Returns the keycode of the key that triggered this KeyboardEvent.
  */
  SDL_Keycode GetKeycode() const;

  /**
  \brief Returns the event type of this KeyboardEvent. The possible return
  values are either SDL_KEYDOWN or SDL_KEYUP.
  */
  uint32_t GetKeyEventType() const;
};

}  // namespace events
}  // namespace centurion