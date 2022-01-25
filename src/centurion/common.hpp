#ifndef CENTURION_COMMON_HPP_
#define CENTURION_COMMON_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <chrono>       // duration
#include <cstddef>      // size_t
#include <exception>    // exception
#include <memory>       // unique_ptr
#include <ostream>      // ostream
#include <ratio>        // ratio, milli, micro, nano
#include <string>       // string
#include <type_traits>  // underlying_type_t, enable_if_t, is_same_v, is_integral_v, ...

#include "detail/sdl_deleter.hpp"
#include "features.hpp"
#include "memory.hpp"
#include "version.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

/**
 * \defgroup common Common
 *
 * \brief Common utilities and APIs.
 */

/// \addtogroup common
/// \{

#define CENTURION_DISABLE_COPY(Class) \
  Class(const Class&) = delete;       \
  Class& operator=(const Class&) = delete;

#define CENTURION_DISABLE_MOVE(Class) \
  Class(Class&&) = delete;            \
  Class& operator=(Class&&) = delete;

/// \} End of group common

namespace cen {

/// \addtogroup common
/// \{

/// \name Integral aliases
/// \{

using uint = unsigned int;
using ulonglong = unsigned long long;

using uint8 = Uint8;
using uint16 = Uint16;
using uint32 = Uint32;
using uint64 = Uint64;

using int8 = Sint8;
using int16 = Sint16;
using int32 = Sint32;
using int64 = Sint64;

using unicode_t = uint16;

template <typename T>
using seconds = std::chrono::duration<T>;

template <typename T>
using millis = std::chrono::duration<T, std::milli>;

template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

using u16ms = millis<uint16>;
using u32ms = millis<uint32>;
using u64ms = millis<uint64>;

/// \} End of integral aliases

/// \name Build and compiler information
/// \{

/**
 * \var is_debug_build
 * \brief Indicates whether the compiler is in debug build mode.
 */

/**
 * \var is_release_build
 * \brief Indicates whether the compiler is in release build mode.
 */

/**
 * \var on_msvc
 * \brief Indicates whether the compiler is MSVC.
 */

/**
 * \var on_gcc
 * \brief Indicates whether the compiler is GNU (GCC).
 */

/**
 * \var on_clang
 * \brief Indicates whether the compiler is Clang.
 */

#ifdef NDEBUG
inline constexpr bool is_debug_build = false;
inline constexpr bool is_release_build = true;
#else
inline constexpr bool is_debug_build = true;
inline constexpr bool is_release_build = false;
#endif  // NDEBUG

#ifdef _MSC_VER
inline constexpr bool on_msvc = true;
#else
inline constexpr bool on_msvc = false;
#endif  // _MSC_VER

#ifdef __GNUC__
inline constexpr bool on_gcc = true;
#else
inline constexpr bool on_gcc = false;
#endif  // __GNUC__

#ifdef __clang__
inline constexpr bool on_clang = true;
#else
inline constexpr bool on_clang = false;
#endif  // __clang__

/// \} End of build and compiler information

/// \name SFINAE helpers
/// \{

template <typename T>
using enable_for_pointer_t = std::enable_if_t<std::is_pointer_v<T>, int>;

/// Enables a template if T is convertible to any of the specified types.
template <typename T, typename... Args>
using enable_for_convertible_t =
    std::enable_if_t<(std::is_convertible_v<T, Args> || ...), int>;

template <typename T>
using enable_for_enum_t = std::enable_if_t<std::is_enum_v<T>, int>;

/// \} End of SFINAE helpers

/// \name Array helper aliases
/// \{

template <typename T, std::size_t Size>
using bounded_array_ref = T (&)[Size];

/// \} End of array helper aliases

/// \name Pointer tag aliases
/// \{

template <typename T, enable_for_pointer_t<T> = 0>
using not_null = T;

template <typename T, enable_for_pointer_t<T> = 0>
using owner = T;

template <typename T, enable_for_pointer_t<T> = 0>
using maybe_owner = T;

/// \} End of pointer tag aliases

template <typename T>
inline constexpr bool is_number =
    !std::is_same_v<T, bool> && (std::is_integral_v<T> || std::is_floating_point_v<T>);

#if CENTURION_HAS_FEATURE_CONCEPTS

template <typename T, typename... Args>
concept is_stateless_callable = std::default_initializable<T> && std::invocable<T, Args...>;

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

/**
 * \brief The base class of all exceptions explicitly thrown by the library.
 *
 * \see `sdl_error`
 * \see `img_error`
 * \see `mix_error`
 * \see `ttf_error`
 */
class exception : public std::exception {
 public:
  exception() noexcept = default;

  explicit exception(const char* what) noexcept : mWhat{what ? what : "?"} {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat; }

 private:
  const char* mWhat{"?"};
};

/**
 * \brief Represents an error related to the core SDL library.
 */
class sdl_error final : public exception {
 public:
  sdl_error() noexcept : exception{SDL_GetError()} {}

  explicit sdl_error(const char* what) noexcept : exception{what} {}
};

#ifndef CENTURION_NO_SDL_IMAGE

/**
 * \brief Represents an error related to the core SDL_image library.
 */
class img_error final : public exception {
 public:
  img_error() noexcept : exception{IMG_GetError()} {}

  explicit img_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF

/**
 * \brief Represents an error related to the core SDL_ttf library.
 */
class ttf_error final : public exception {
 public:
  ttf_error() noexcept : exception{TTF_GetError()} {}

  explicit ttf_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

/**
 * \brief Represents an error related to the core SDL_mixer library.
 */
class mix_error final : public exception {
 public:
  mix_error() noexcept : exception{Mix_GetError()} {}

  explicit mix_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_MIXER

/**
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
 */
class result final {
 public:
  /**
   * \brief Creates a result.
   *
   * \param success `true` if the result is successful; `false` otherwise.
   */
  constexpr result(const bool success) noexcept  // NOLINT implicit
      : mSuccess{success}
  {}

  /**
   * \brief Indicates whether the result is a success.
   *
   * \return `true` if the result is a success; `false` otherwise.
   */
  [[nodiscard]] constexpr explicit operator bool() const noexcept { return mSuccess; }

 private:
  bool mSuccess{};
};

/// \name Result constants
/// \{

inline constexpr result success{true};   ///< Represents a successful result.
inline constexpr result failure{false};  ///< Represents a failure.

/// \} End of result constants

/// \name Result functions
/// \{

[[nodiscard]] inline auto to_string(const result result) -> std::string
{
  return result ? "success" : "failure";
}

inline auto operator<<(std::ostream& stream, const result result) -> std::ostream&
{
  return stream << to_string(result);
}

[[nodiscard]] constexpr auto operator==(const result a, const result b) noexcept -> bool
{
  return a.operator bool() == b.operator bool();
}

[[nodiscard]] constexpr auto operator!=(const result a, const result b) noexcept -> bool
{
  return !(a == b);
}

/// \} End of result functions

/**
 * \brief Represents an SDL style string.
 *
 * \details Certain SDL APIs return `char*` strings that need to be freed using `SDL_free()`,
 * this class serves as a small wrapper around such strings. Use the `copy()` member function
 * to convert the string into a corresponding `std::string`.
 *
 * \note Instances of `sdl_string` can hold null strings. Use the overloaded `operator
 * bool()` in order to determine whether the associated string is null.
 */
class sdl_string final {
 public:
  /**
   * \brief Creates a string.
   *
   * \param str the string that will be claimed, can be null.
   */
  explicit sdl_string(owner<char*> str) noexcept : mStr{str} {}

  /**
   * \brief Returns the internal string, which might be null.
   *
   * \return the internal string; `nullptr` if there is none.
   */
  [[nodiscard]] auto get() const noexcept -> const char* { return mStr.get(); }

  /**
   * \brief Returns a copy of the internal string.
   *
   * \details This function returns the empty string if the internal string is a null
   * pointer.
   *
   * \return a copy of the internal string.
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (mStr) {
      return std::string{get()};
    }
    else {
      return std::string{};
    }
  }

  /**
   * \brief Indicates whether or not the internal string is non-null.
   *
   * \return `true` if the internal string is non-null; `false` otherwise.
   */
  explicit operator bool() const noexcept { return mStr != nullptr; }

 private:
  std::unique_ptr<char, detail::sdl_deleter> mStr;
};

/// \name Common utility functions
/// \{

/**
 * \brief Casts a value to a value of another type.
 *
 * \details This is the default implementation, which simply attempts to use `static_cast`. The
 * idea is that this function will be specialized for various Centurion and SDL types. This is
 * useful because it isn't always possible to implement conversion operators as members.
 *
 * \tparam To the target type of the value that will be converted.
 * \tparam From the original type of the value.
 *
 * \param from the value that will be casted.
 *
 * \return the casted value.
 */
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

/**
 * \brief Converts an enum value to its underlying integral value.
 *
 * \details This function is basically just `std::to_underlying()` from C++23.
 *
 * \tparam Enum the enum type.
 *
 * \param value the enumerator that will be converted.
 *
 * \return the integral value of the enumerator.
 */
template <typename Enum, enable_for_enum_t<Enum> = 0>
[[nodiscard]] constexpr auto to_underlying(const Enum value) noexcept
    -> std::underlying_type_t<Enum>
{
  return static_cast<std::underlying_type_t<Enum>>(value);
}

/**
 * \brief Obtains the size of a container as an `int`.
 *
 * \tparam T a "container" that provides a `size()` member function.
 *
 * \param container the container that will be queried.
 *
 * \return the container size as an `int`.
 */
template <typename T>
[[nodiscard]] constexpr auto isize(const T& container) noexcept(noexcept(container.size()))
    -> int
{
  return static_cast<int>(container.size());
}

/**
 * \brief Simply returns the string if it is non-null, returning a placeholder otherwise.
 *
 * \param str the string that will be returned if it is not null.
 *
 * \return the supplied string or a placeholder.
 */
[[nodiscard]] inline auto str_or_na(const char* str) noexcept -> const char*
{
  return str ? str : "null";
}

/// \} End of common utility functions

/// \} End of group common

/// \ingroup common
namespace literals {

/// \ingroup common
inline namespace time_literals {

#if SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u64ms
{
  return u64ms{static_cast<uint64>(ms)};
}

#else

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u32ms
{
  return u32ms{static_cast<uint32>(ms)};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

}  // namespace time_literals

}  // namespace literals

}  // namespace cen

#if CENTURION_SDL_VERSION_IS(2, 0, 10)

/* Workaround for the enum being completely anonymous in SDL 2.0.10. Included here because
   multiple files depend on this definition. */
using SDL_KeyCode = decltype(SDLK_UNKNOWN);

#endif  // CENTURION_SDL_VERSION_IS(2, 0, 10)

#endif  // CENTURION_COMMON_HPP_
