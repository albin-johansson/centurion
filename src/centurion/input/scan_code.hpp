#ifndef CENTURION_SCAN_CODE_HEADER
#define CENTURION_SCAN_CODE_HEADER

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
 * \class scan_code
 *
 * \brief Represents a scan code.
 *
 * \serializable
 *
 * \details Scan codes represent the physical location of a key on the
 * keyboard. Use the associated key code associated with the location to give
 * the key press meaning.
 *
 * Scan codes are meant to be layout-independent. Think of this as "the user
 * pressed the Q key as it would be on a US QWERTY keyboard" regardless of
 * whether this is actually a European keyboard or a Dvorak keyboard or
 * whatever. *The scancode is always the same key position.*
 *
 * \since 5.0.0
 *
 * \see `key_code`
 * \see `cen::scancodes`
 */
class scan_code final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a `scan_code` instance with the `SDL_SCANCODE_UNKNOWN` scan
   * code.
   *
   * \since 5.0.0
   */
  constexpr scan_code() noexcept = default;

  constexpr scan_code(const scan_code&) noexcept = default;

  constexpr scan_code(scan_code&&) noexcept = default;

  /**
   * \brief Creates a `scan_code` instance with the specified scan code.
   *
   * \param scancode the scan code that will be used.
   *
   * \since 5.0.0
   */
  constexpr /*implicit*/ scan_code(const SDL_Scancode scancode) noexcept : m_code{scancode}
  {}

  /**
   * \brief Creates a `scan_code` instance based on a key code.
   *
   * \details The created `scan_code` will use the scan code obtained
   * by converting the specified key code.
   *
   * \param key the key code that will be converted and used.
   *
   * \since 5.0.0
   */
  explicit scan_code(const SDL_Keycode key) noexcept : m_code{SDL_GetScancodeFromKey(key)}
  {}

  /**
   * \brief Creates a `scan_code` instance based on the specified name.
   *
   * \details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \see `SDL_GetScancodeFromName`
   *
   * \since 5.0.0
   */
  explicit scan_code(const not_null<str> name) noexcept : m_code{SDL_GetScancodeFromName(name)}
  {}

  /**
   * \brief Creates a `scan_code` instance based on the specified name.
   *
   * \details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * \param name the name of the key.
   *
   * \since 5.3.0
   */
  explicit scan_code(const std::string& name) noexcept : scan_code{name.c_str()}
  {}

  /// \} End of construction

  /// \name Assignment operators
  /// \{

  constexpr auto operator=(const scan_code&) noexcept -> scan_code& = default;

  constexpr auto operator=(scan_code&&) noexcept -> scan_code& = default;

  /**
   * \brief Sets the scan code used to the specified scan code.
   *
   * \param code the scan code that will be used.
   *
   * \return the `scan_code` instance.
   *
   * \since 5.0.0
   */
  constexpr auto operator=(const SDL_Scancode code) noexcept -> scan_code&
  {
    m_code = code;
    return *this;
  }

  /**
   * \brief Sets the scan code used to be the converted version of the
   * supplied key code.
   *
   * \param keycode the key code that will be converted and used.
   *
   * \return the `scan_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(const SDL_Keycode keycode) noexcept -> scan_code&
  {
    m_code = SDL_GetScancodeFromKey(keycode);
    return *this;
  }

  /**
   * \brief Sets the scan code used to be the one associated with the
   * specified name.
   *
   * \details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * \param name the name of the key, mustn't be null.
   *
   * \return the `scan_code` instance.
   *
   * \since 5.0.0
   */
  auto operator=(const not_null<str> name) noexcept -> scan_code&
  {
    assert(name);
    m_code = SDL_GetScancodeFromName(name);
    return *this;
  }

  /**
   * \brief Sets the scan code used to be the one associated with the
   * specified name.
   *
   * \details If the specified name isn't recognized, `SDL_SCANCODE_UNKNOWN` is
   * used as the scan code.
   *
   * \param name the name of the key.
   *
   * \return the `scan_code` instance.
   *
   * \since 5.3.0
   */
  auto operator=(const std::string& name) noexcept -> scan_code&
  {
    return operator=(name.c_str());  // NOLINT
  }

  /// \} End of assignment operators

  /// \name Queries
  /// \{

  /**
   * \brief Returns the total amount of scan codes.
   *
   * \return the amount of scan codes.
   *
   * \since 5.1.0
   */
  [[nodiscard]] constexpr static auto count() noexcept -> int
  {
    return SDL_NUM_SCANCODES;
  }

  /**
   * \brief Indicates whether or not the stored scan code is
   * `SDL_SCANCODE_UNKNOWN`.
   *
   * \return `true` if the internal scan code is `SDL_SCANCODE_UNKNOWN`;
   * `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto unknown() const noexcept -> bool
  {
    return m_code == SDL_SCANCODE_UNKNOWN;
  }

  /**
   * \brief Returns the name associated with the scan code.
   *
   * \return the name associated with the scan code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto name() const -> std::string
  {
    return SDL_GetScancodeName(m_code);
  }

  /**
   * \brief Returns the corresponding `SDL_KeyCode`.
   *
   * \return the key code associated with the internal scan code.
   *
   * \see `SDL_GetKeyFromScancode`
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto to_key_code() const noexcept -> SDL_KeyCode
  {
    return static_cast<SDL_KeyCode>(SDL_GetKeyFromScancode(m_code));
  }

  /**
   * \brief Returns the internal scan code.
   *
   * \return the internal scan code.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> SDL_Scancode
  {
    return m_code;
  }

  /// \} End of queries

  /// \name Conversions
  /// \{

  /**
   * \brief Converts to `SDL_Scancode`.
   *
   * \return the internal scan code.
   *
   * \since 5.0.0
   */
  constexpr explicit operator SDL_Scancode() const noexcept
  {
    return m_code;
  }

  /**
   * \brief Converts to `SDL_KeyCode`.
   *
   * \return the key code associated with the internal scan code.
   *
   * \see `SDL_GetKeyFromScancode`
   *
   * \since 5.0.0
   */
  explicit operator SDL_KeyCode() const noexcept
  {
    return to_key_code();
  }

  /// \} End of conversions

  /**
   * \brief Serializes the scan code.
   *
   * \details This function expects that the archive provides an overloaded
   * `operator()`, used for serializing data. This API is based on the Cereal
   * serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the scan code.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_code);
  }

 private:
  SDL_Scancode m_code{SDL_SCANCODE_UNKNOWN};
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a scan code.
 *
 * \param code the scan code that will be converted.
 *
 * \return a textual representation of the scan code.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const scan_code& code) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("scan_code{{key: {}}}", code.name());
#else
  return "scan_code{key: " + code.name() + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a scan code using a stream.
 *
 * \param stream the stream that will be used.
 * \param scanCode the scan code that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const scan_code& scanCode) -> std::ostream&
{
  return stream << to_string(scanCode);
}

/// \} End of streaming

/// \name Scan code comparison operators
/// \{

/**
 * \brief Indicates whether or not two scan codes are the same.
 *
 * \param lhs the left-hand side scan code.
 * \param rhs the right-hand side scan code.
 *
 * \return `true` if the scan codes are the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator==(const scan_code& lhs, const scan_code& rhs) noexcept
    -> bool
{
  return lhs.get() == rhs.get();
}

/**
 * \brief Indicates whether or not two scan codes aren't the same.
 *
 * \param lhs the left-hand side scan code.
 * \param rhs the right-hand side scan code.
 *
 * \return `true` if the scan codes aren't the same; `false` otherwise.
 *
 * \since 5.0.0
 */
[[nodiscard]] constexpr auto operator!=(const scan_code& lhs, const scan_code& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of scan code comparison operators

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_SCAN_CODE_HEADER