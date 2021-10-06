#ifndef CENTURION_KEY_CODE_HEADER
#define CENTURION_KEY_CODE_HEADER

#include <SDL.h>

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/not_null.hpp"
#include "../core/str.hpp"
#include "../core/version.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class key_code
 *
 * \brief Represents a key code (or virtual key).
 *
 * \serializable
 *
 * \details Key codes are mapped to the current layout of the keyboard and correlate to a
 * `scan_code`. Whilst scan codes identify the *location* of a key press, the
 * corresponding key codes give the key press *meaning* in the context of the current
 * keyboard layout.
 *
 * Keycodes are meant to be layout-dependent. Think of this as "the user pressed the key
 * that is labelled 'Q' on a specific keyboard."
 *
 * For example, if you pressed the key that's two keys to the right of CAPS LOCK on a US
 * QWERTY keyboard, it'll report a scancode of SDL_SCANCODE_S and a keycode of SDLK_S. The
 * same key on a Dvorak keyboard, will report a scancode of SDL_SCANCODE_S and a keycode
 * of SDLK_O.
 *
 * \note Key codes are sometimes referred to as "keysyms" in the SDL documentation.
 *
 * \since 5.0.0
 *
 * \see `scan_code`
 * \see `cen::keycodes`
 */
class key_code final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a `key_code` instance with the `SDLK_UNKNOWN` key code.
   *
   * \since 5.0.0
   */
  constexpr key_code() noexcept = default;

  constexpr key_code(const key_code&) noexcept = default;

  constexpr key_code(key_code&&) noexcept = default;

  /**
   * \brief Creates a `key_code` instance with the specified key code.
   *
   * \param key the key code that will be used.
   *
   * \since 5.0.0
   */
  constexpr /*implicit*/ key_code(const SDL_KeyCode key) noexcept : m_key{key}
  {}

  /**
   * \brief Creates a `key_code` instance based on a scan code.
   *
   * \details The created `key_code` will use the key code obtained
   * by converting the specified scan code.
   *
   * \param scancode the scan code that will be converted and used.
   *
   * \see `SDL_GetKeyFromScancode`
   *
   * \since 5.0.0
   */
  explicit key_code(const SDL_Scancode scancode) noexcept
      : m_key{static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode))}
  {}

  /**
   * \brief Creates a `key_code` instance based on the specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as
   * the key code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \see `SDL_GetKeyFromName`
   *
   * \since 5.0.0
   */
  explicit key_code(const not_null<str> name) noexcept
      : m_key{static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name))}
  {}

  /**
   * \brief Creates a `key_code` instance based on the specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as
   * the key code.
   *
   * \param name the name of the key.
   *
   * \since 5.3.0
   */
  explicit key_code(const std::string& name) noexcept : key_code{name.c_str()}
  {}

  /// \} End of construction

  /// \name Assignment operators
  /// \{

  constexpr auto operator=(const key_code&) noexcept -> key_code& = default;

  constexpr auto operator=(key_code&&) noexcept -> key_code& = default;

  /**
   * \brief Sets the key code used to the specified key code.
   *
   * \param key the key code that will be used.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  constexpr auto operator=(const SDL_KeyCode key) noexcept -> key_code&
  {
    m_key = key;
    return *this;
  }

  /**
   * \brief Sets the key code used to be the converted version of the
   * supplied scan code.
   *
   * \param scancode the scan code that will be converted and used.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(const SDL_Scancode scancode) noexcept -> key_code&
  {
    m_key = static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(scancode));
    return *this;
  }

  /**
   * \brief Sets the key code used to be the one associated with the
   * specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as
   * the key code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \return the `key_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(const not_null<str> name) noexcept -> key_code&
  {
    assert(name);
    m_key = static_cast<SDL_KeyCode>(SDL_GetKeyFromName(name));
    return *this;
  }

  /**
   * \brief Sets the key code used to be the one associated with the specified name.
   *
   * \details If the specified name isn't recognized, `SDLK_UNKNOWN` is used as the key
   * code.
   *
   * \param name the name of the key.
   *
   * \return the `key_code` instance.
   *
   * \since 5.3.0
   */
  auto operator=(const std::string& name) noexcept -> key_code&
  {
    return this->operator=(name.c_str());  // NOLINT
  }

  /// \} End of assignment operators

  /// \name Queries
  /// \{

  /**
   * \brief Indicates whether or not the stored key code is `SDLK_UNKNOWN`.
   *
   * \return `true` if the internal key code is `SDLK_UNKNOWN`; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return m_key == SDLK_UNKNOWN;
  }

  /**
   * \brief Returns the name associated with the key code.
   *
   * \return the name associated with the key code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetKeyName(m_key);
  }

  /**
   * \brief Returns the corresponding `SDL_Scancode`.
   *
   * \return the scan code associated with the internal key code.
   *
   * \see `SDL_GetScancodeFromKey`
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto to_scan_code() const noexcept -> SDL_Scancode
  {
    return SDL_GetScancodeFromKey(m_key);
  }

  /**
   * \brief Returns the internal key code.
   *
   * \return the internal key code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> SDL_KeyCode
  {
    return m_key;
  }

  /// \} End of queries

  /// \name Conversions
  /// \{

  /**
   * \brief Converts to `SDL_KeyCode`.
   *
   * \return the internal key code.
   *
   * \since 5.0.0
   */
  constexpr explicit operator SDL_KeyCode() const noexcept
  {
    return m_key;
  }

  /**
   * \brief Converts to `SDL_Keycode`.
   *
   * \return the internal key code.
   *
   * \note `SDL_Keycode` is just an alias for `i32`.
   *
   * \since 5.0.0
   */
  constexpr explicit operator SDL_Keycode() const noexcept
  {
    return m_key;
  }

  /**
   * \brief Converts to `SDL_Scancode`.
   *
   * \return the scan code associated with the internal key code.
   *
   * \see `to_scan_code()`
   *
   * \since 5.0.0
   */
  explicit operator SDL_Scancode() const noexcept
  {
    return to_scan_code();
  }

  /// \} End of conversions

  /**
   * \brief Serializes the key code.
   *
   * \details This function expects that the archive provides an overloaded `operator()`,
   * used for serializing data. This API is based on the Cereal serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the key code.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_key);
  }

 private:
  SDL_KeyCode m_key{SDLK_UNKNOWN};
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a key code.
 *
 * \param keyCode the key code that will be converted.
 *
 * \return a textual representation of the key code.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const key_code& keyCode) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("key_code{{key: {}}}", keyCode.name());
#else
  return "key_code{key: " + keyCode.name() + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a key code using a stream.
 *
 * \param stream the stream that will be used.
 * \param keyCode the key code that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const key_code& keyCode) -> std::ostream&
{
  return stream << to_string(keyCode);
}

/// \} End of streaming

/// \name Key code comparison operators
/// \{

/**
 * \brief Indicates whether or not two key codes are the same.
 *
 * \param lhs the left-hand side key code.
 * \param rhs the right-hand side key code.
 *
 * \return `true` if the key codes are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const key_code& lhs, const key_code& rhs) noexcept
    -> bool
{
  return lhs.get() == rhs.get();
}

/**
 * \brief Indicates whether or not two key codes aren't the same.
 *
 * \param lhs the left-hand side key code.
 * \param rhs the right-hand side key code.
 *
 * \return `true` if the key codes aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const key_code& lhs, const key_code& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of key code comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_KEY_CODE_HEADER