#ifndef CENTURION_KEY_HEADER
#define CENTURION_KEY_HEADER

#include <SDL_keycode.h>
#include <SDL_scancode.h>

#include <type_traits>

#include "centurion_api.h"

namespace centurion {

/**
 * The Key class is a simple value class that represents a keyboard key and
 * can be created from either SDL_Scancode or SDL_Keycode values. This class
 * is implicitly convertible to both SDL_Scancode and SDL_Keycode.
 *
 * @see SDL_Scancode
 * @see SDL_Keycode
 * @since 4.0.0
 */
class Key final {
 public:
  /**
   * Creates a Key instance with the UNKNOWN scancode and keycode values.
   *
   * @since 4.0.0
   */
  CENTURION_API Key() noexcept;

  /**
   * Creates a Key instance based on the supplied scancode.
   *
   * @param scancode the scancode that the Key will be based on.
   * @since 4.0.0
   */
  CENTURION_API Key(SDL_Scancode scancode) noexcept;

  /**
   * Creates a Key instance based on the supplied keycode.
   *
   * @param scancode the keycode that the Key will be based on.
   * @since 4.0.0
   */
  CENTURION_API Key(SDL_Keycode keycode) noexcept;

  /**
   * Sets the value of the key.
   *
   * @param scancode the scancode of the key that the key instance will
   * represent.
   * @since 4.0.0
   */
  CENTURION_API void set(SDL_Scancode scancode) noexcept;

  /**
   * Sets the value of the key.
   *
   * @param keycode the keycode of the key that the key instance will
   * represent.
   * @since 4.0.0
   */
  CENTURION_API void set(SDL_Keycode keycode) noexcept;

  /**
   * Returns the scancode associated with the key.
   *
   * @return the scancode associated with the key.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SDL_Scancode scancode() const noexcept;

  /**
   * Returns the keycode associated with the key.
   *
   * @return the keycode associated with the key.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SDL_Keycode keycode() const noexcept;

  /**
   * Implicitly converts the Key instance to an SDL_Scancode value.
   *
   * @return an SDL_Scancode value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API operator SDL_Scancode() const noexcept;

  /**
   * Implicitly converts the Key instance to an SDL_Keycode value.
   *
   * @return an SDL_Keycode value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API operator SDL_Keycode() const noexcept;

 private:
  SDL_Scancode m_scancode;
  SDL_Keycode m_keycode;
};

static_assert(std::is_final<Key>::value, "Key isn't final!");

static_assert(std::is_copy_constructible<Key>::value, "Key isn't copyable!");
static_assert(std::is_copy_assignable<Key>::value, "Key isn't copyable!");

static_assert(std::is_move_constructible<Key>::value, "Key isn't movable!");
static_assert(std::is_move_assignable<Key>::value, "Key isn't movable!");

/**
 * Indicates whether or not two keys represent the same keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 * @return true if the two keys are the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(const Key& lhs, const Key& rhs) noexcept;

/**
 * Indicates whether or not two keys don't represent the same keyboard key.
 *
 * @param lhs the left-hand side key.
 * @param rhs the right-hand side key.
 * @return true if the two keys aren't the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(const Key& lhs, const Key& rhs) noexcept;

}  // namespace centurion

#endif  // CENTURION_KEY_HEADER