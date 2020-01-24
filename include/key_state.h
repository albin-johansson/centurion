/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <cstdint>
#include <array>
#include <memory>
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
   * Creates and returns a unique pointer to a KeyState instance.
   *
   * @return a unique pointer to a KeyState instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<KeyState> unique();

  /**
   * Creates and returns a shared pointer to a KeyState instance.
   *
   * @return a shared pointer to a KeyState instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<KeyState> shared();

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
