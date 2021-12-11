#ifndef CENTURION_CORE_COMMON_HPP_
#define CENTURION_CORE_COMMON_HPP_

#include <SDL.h>

#include <cstddef>      // size_t
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // underlying_type_t, enable_if_t, is_same_v, is_integral_v, ...

#define CENTURION_DISABLE_COPY(Class) \
  Class(const Class&) = delete;       \
  Class& operator=(const Class&) = delete;

#define CENTURION_DISABLE_MOVE(Class) \
  Class(Class&&) = delete;            \
  Class& operator=(Class&&) = delete;

namespace cen {

/// \addtogroup core
/// \{

/**
 * \brief Indicates whether or not a "debug" build mode is active.
 *
 * \note This is intended to be use with `if constexpr`-statements instead of raw `#ifdef`
 * conditional compilation, since the use of `if constexpr` prevents any branch to be
 * ill-formed, which avoids code rot.
 *
 * \return `true` if a debug build mode is currently active; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto is_debug_build() noexcept -> bool
{
#ifndef NDEBUG
  return true;
#else
  return false;
#endif  // NDEBUG
}

/**
 * \brief Indicates whether or not a "release" build mode is active.
 *
 * \note This is intended to be use with `if constexpr`-statements instead of raw `#ifdef`
 * conditional compilation, since the use of `if constexpr` prevents any branch to be
 * ill-formed, which avoids code rot.
 *
 * \return `true` if a release build mode is currently active; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto is_release_build() noexcept -> bool
{
  return !is_debug_build();
}

/**
 * \brief Indicates whether or not the compiler is MSVC.
 *
 * \return `true` if MSVC is detected as the current compiler; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_msvc() noexcept -> bool
{
#ifdef _MSC_VER
  return true;
#else
  return false;
#endif  // _MSC_VER
}

/**
 * \brief Indicates whether or not the compiler is GCC.
 *
 * \return `true` if GCC is detected as the current compiler; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_gcc() noexcept -> bool
{
#ifdef __GNUC__
  return true;
#else
  return false;
#endif  // __GNUC__
}

/**
 * \brief Indicates whether or not the compiler is Clang.
 *
 * \return `true` if Clang is detected as the current compiler; `false` otherwise.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto on_clang() noexcept -> bool
{
#ifdef __clang__
  return true;
#else
  return false;
#endif  // __clang__
}

/// \brief Alias for a C-style string.
/// \since 6.2.0
using cstr = const char*;

/// \name Integer aliases
/// \{

using usize = std::size_t;

/// Alias for an unsigned integer.
using uint = unsigned int;

/// Alias for the type used for integer literal operators.
using ulonglong = unsigned long long;

using u8 = Uint8;
using u16 = Uint16;
using u32 = Uint32;
using u64 = Uint64;

using i8 = Sint8;
using i16 = Sint16;
using i32 = Sint32;
using i64 = Sint64;

/// \} End of integer aliases

// TODO use _t suffix instead of _v in the SFINAE aliases

// clang-format off

/// Enables a template if the type is either integral of floating-point, but not a boolean.
template <typename T>
using enable_if_number_t = std::enable_if_t<!std::is_same_v<T, bool> &&
                                            (std::is_integral_v<T> ||
                                             std::is_floating_point_v<T>), int>;

// clang-format on

/// Enables a template if the type is a pointer.
template <typename T>
using enable_if_pointer_v = std::enable_if_t<std::is_pointer_v<T>, int>;

/// Enables a template if T is convertible to any of the specified types.
template <typename T, typename... Args>
using enable_if_convertible_t = std::enable_if_t<(std::is_convertible_v<T, Args> || ...), int>;

template <typename T>
using enable_if_enum_t = std::enable_if_t<std::is_enum_v<T>, int>;

/// \brief Tag used to indicate that a pointer cannot be null.
/// \since 5.0.0
template <typename T, enable_if_pointer_v<T> = 0>
using not_null = T;

/**
 * \brief Tag used to denote ownership of raw pointers directly in code.
 *
 * \details If a function takes an `owner<T*>` as a parameter, then the function will
 * claim ownership of that pointer. Subsequently, if a function returns an `owner<T*>`,
 * then ownership is transferred to the caller.
 */
template <typename T, enable_if_pointer_v<T> = 0>
using owner = T;

/**
 * \brief Tag used to denote conditional ownership of raw pointers directly in code.
 *
 * \details This is primarily used in constructors of owner/handle classes, where the
 * owner version will claim ownership of the pointer, whilst the handle does not.
 *
 * \since 6.0.0
 */
template <typename T, enable_if_pointer_v<T> = 0>
using maybe_owner = T;

/**
 * \brief Converts an enum value to an integral value using the underlying type.
 *
 * \ingroup core
 *
 * \note If you're using C++23, see `std::to_underlying()`.
 *
 * \tparam Enum the enum type.
 *
 * \param value the enum value that will be converted.
 *
 * \return the value of the enum, in the underlying type.
 *
 * \since 6.0.0
 */
template <typename Enum, enable_if_enum_t<Enum> = 0>
[[nodiscard]] constexpr auto to_underlying(const Enum value) noexcept
    -> std::underlying_type_t<Enum>
{
  return static_cast<std::underlying_type_t<Enum>>(value);
}

/**
 * \brief Casts a value to a value of another type.
 *
 * \ingroup core
 *
 * \details This is the default implementation, which simply attempts to use
 * `static_cast`. The idea is that this function will be specialized for various Centurion
 * and SDL types. This is useful because it isn't always possible to implement conversion
 * operators as members.
 *
 * \tparam To the type of the value that will be converted.
 * \tparam From the type that the value will be casted to.
 *
 * \param from the value that will be converted.
 *
 * \return the result of casting the supplied value to the specified type.
 *
 * \since 5.0.0
 */
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

/**
 * \brief Obtains the size of a container as an `int`.
 *
 * \tparam T a "container" that provides a `size()` member function.
 *
 * \param container the container to query the size of.
 *
 * \return the size of the container as an `int` value.
 *
 * \since 5.3.0
 */
template <typename T>
[[nodiscard]] constexpr auto isize(const T& container) noexcept(noexcept(container.size()))
    -> int
{
  return static_cast<int>(container.size());
}

/**
 * \brief Simply returns the string if it isn't null, returning a placeholder otherwise.
 *
 * \param string the string that will be checked.
 *
 * \return the supplied string if it isn't null; "n/a" otherwise.
 *
 * \since 6.0.0
 */
[[nodiscard]] inline auto str_or_na(const cstr string) noexcept -> not_null<cstr>
{
  return string ? string : "n/a";
}

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

namespace literals {

/// \addtogroup core
/// \{

/**
 * \brief Creates an 8-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return an 8-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u8(const ulonglong value) noexcept -> u8
{
  return static_cast<u8>(value);
}

/**
 * \brief Creates a 16-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 16-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u16(const ulonglong value) noexcept -> u16
{
  return static_cast<u16>(value);
}

/**
 * \brief Creates a 32-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 32-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u32(const ulonglong value) noexcept -> u32
{
  return static_cast<u32>(value);
}

/**
 * \brief Creates a 64-bit unsigned integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 64-bit unsigned integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_u64(const ulonglong value) noexcept -> u64
{
  return static_cast<u64>(value);
}

/**
 * \brief Creates an 8-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return an 8-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i8(const ulonglong value) noexcept -> i8
{
  return static_cast<i8>(value);
}

/**
 * \brief Creates a 16-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 16-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i16(const ulonglong value) noexcept -> i16
{
  return static_cast<i16>(value);
}

/**
 * \brief Creates a 32-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 32-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i32(const ulonglong value) noexcept -> i32
{
  return static_cast<i32>(value);
}

/**
 * \brief Creates a 64-bit signed integer.
 *
 * \param value the value that will be converted.
 *
 * \return a 64-bit signed integer.
 *
 * \since 5.3.0
 */
[[nodiscard]] constexpr auto operator""_i64(const ulonglong value) noexcept -> i64
{
  return static_cast<i64>(value);
}

/// \} End of group core

}  // namespace literals
}  // namespace cen

#ifndef CENTURION_NO_SDL_NAMESPACE_ALIAS
namespace SDL = cen;
#endif  // CENTURION_NO_SDL_NAMESPACE_ALIAS

#endif  // CENTURION_CORE_COMMON_HPP_
