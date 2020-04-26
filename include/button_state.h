#ifndef CENTURION_BUTTON_STATE_HEADER
#define CENTURION_BUTTON_STATE_HEADER

namespace centurion {

/**
 * The ButtonState enum class provides the possible states for a button.
 * Corresponds to the SDL_RELEASED and SDL_PRESSED macros.
 *
 * @since 3.1.0
 */
enum class ButtonState { Released = SDL_RELEASED, Pressed = SDL_PRESSED };

}  // namespace centurion

#endif  // CENTURION_BUTTON_STATE_HEADER