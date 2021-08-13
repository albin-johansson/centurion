#ifndef CENTURION_RESULT_HEADER
#define CENTURION_RESULT_HEADER

#include <ostream>  // ostream
#include <string>   // string

namespace cen {

/// \addtogroup core
/// \{

/**
 * \class result
 *
 * \brief A simple indicator for the result of different operations.
 *
 * \details The idea behind this class is to make results of various operations
 * unambiguous. Quite an amount of functions in the library may fail, and earlier versions
 * of Centurion would usually return a `bool` in those cases, where `true` and `false`
 * would indicate success and failure, respectively. This class is a development of that
 * practice. For instance, this class is contextually convertible to `bool`, where a
 * successful result is still converted to `true`, and vice versa. However, this class
 * also enables explicit checks against `success` and `failure` constants, which makes
 * code very easy to read and unambiguous.
 * \code{cpp}
 *   cen::window window;
 *
 *   if (window.set_opacity(0.4f))
 *   {
 *     // Success!
 *   }
 *
 *   if (window.set_opacity(0.4f) == cen::success)
 *   {
 *     // Success!
 *   }
 *
 *   if (window.set_opacity(0.4f) == cen::failure)
 *   {
 *     // Failure!
 *   }
 * \endcode
 *
 * \see `success`
 * \see `failure`
 *
 * \since 6.0.0
 */
class result final
{
 public:
  /**
   * \brief Creates a result.
   *
   * \param success `true` if the result is successful; `false` otherwise.
   *
   * \since 6.0.0
   */
  constexpr result(const bool success) noexcept  // NOLINT implicit
      : m_success{success}
  {}

  /// \name Comparison operators
  /// \{

  /**
   * \brief Indicates whether or not two results have the same success value.
   *
   * \param other the other result.
   *
   * \return `true` if the results are equal; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] constexpr auto operator==(const result other) const noexcept -> bool
  {
    return m_success == other.m_success;
  }

  /**
   * \brief Indicates whether or not two results don't have the same success value.
   *
   * \param other the other result.
   *
   * \return `true` if the results aren't equal; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] constexpr auto operator!=(const result other) const noexcept -> bool
  {
    return !(*this == other);
  }

  /// \} End of comparison operators

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not the result is successful.
   *
   * \return `true` if the result is successful; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] constexpr explicit operator bool() const noexcept
  {
    return m_success;
  }

  /// \} End of conversions

 private:
  bool m_success{};
};

/// Represents a successful result.
/// \since 6.0.0
inline constexpr result success{true};

/// Represents a failure of some kind.
/// \since 6.0.0
inline constexpr result failure{false};

/// \name String conversions
/// \{

/**
 * \brief Returns a string that represents a result value.
 *
 * \note The returned string is in a slightly different format compared to other Centurion
 * components.
 *
 * \param result the value that will be converted.
 *
 * \return `"success"` for a successful result; `"failure"` otherwise.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto to_string(const result result) -> std::string
{
  return result ? "success" : "failure";
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a result value using a stream.
 *
 * \param stream the stream that will be used.
 * \param result the result value that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.0.0
 */
inline auto operator<<(std::ostream& stream, const result result) -> std::ostream&
{
  return stream << to_string(result);
}

/// \} End of streaming

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_RESULT_HEADER
