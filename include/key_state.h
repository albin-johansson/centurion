#pragma once
#include <cstdint>
#include <array>
#include <SDL.h>
#include "centurion_api.h"

namespace centurion {

/**
 * The KeyState class provides information about the keyboard state. Using the keyboard state is
 * an alternative to using events for keyboard input.
 *
 * @since 3.0.0
 */
class CENTURION_API KeyState final {
 private:
  const uint8_t* states = nullptr;
  std::array<uint8_t, static_cast<int>(SDL_NUM_SCANCODES)> previousStates;
  int nKeys = 0;

 public:
  /**
   * @throws CenturionException if the key state cannot be obtained.
   * @since 3.0.0
   */
  CENTURION_API KeyState();

  /**
   * @since 3.0.0
   */
  CENTURION_API ~KeyState() noexcept;

  /**
   * Updates the state of the key state object. Note! SDL_PollEvent isn't invoked by this method.
   *
   * @since 3.0.0
   */
  CENTURION_API void update() noexcept;

  /**
   * Indicates whether or not the specified key is being pressed.
   *
   * @param code the scancode of the key that will be checked.
   * @return true if the key is being pressed; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_pressed(SDL_Scancode code) const noexcept;

  /**
   * Indicates whether or not the specified key has been pressed during more than one
   * update of the key state.
   *
   * @param code the scancode of the key that will be checked.
   * @return true if the key has been held down; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_held(SDL_Scancode code) const noexcept;

  /**
   * Indicates whether or not a key just became pressed in the last update of the key state.
   *
   * @param code the scancode of the key that will be checked.
   * @return true if the key has just been pressed; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool was_just_pressed(SDL_Scancode code) const noexcept;

  /**
   * Indicates whether or not the specified key was released in the last update of the key state.
   *
   * @param code the scancode of the key that will be checked.
   * @return true if the key was released; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool was_just_released(SDL_Scancode code) const noexcept;

  /**
   * Returns the total amount of keys.
   *
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_amount_of_keys() const noexcept;
};

}
