#ifndef CENTURION_DETAIL_HINTS_IMPL_HEADER
#define CENTURION_DETAIL_HINTS_IMPL_HEADER

#include <optional>     // optional
#include <string>       // string, stoi, stoul, stof
#include <type_traits>  // enable_if_t, is_same_v, is_convertible_v

#include "../core/integers.hpp"
#include "../core/str.hpp"
#include "czstring_compare.hpp"
#include "czstring_eq.hpp"
#include "from_string.hpp"
#include "static_bimap.hpp"

/// \cond FALSE

namespace cen::detail {

template <typename Hint, typename T>
using enable_if_hint_arg_t = std::enable_if_t<Hint::template valid_arg<T>(), int>;

template <typename Key, usize Size>
using string_map = static_bimap<Key, str, czstring_compare, Size>;

template <typename Derived, typename Arg>
struct crtp_hint
{
  using value_type = Arg;

  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, value_type>;
  }
};

// A hint class that only accepts booleans
template <typename Hint>
struct bool_hint : crtp_hint<bool_hint<Hint>, bool>
{
  [[nodiscard]] static auto current_value() noexcept -> std::optional<bool>
  {
    return SDL_GetHintBoolean(Hint::name(), SDL_FALSE) == SDL_TRUE;
  }

  [[nodiscard]] static auto from_string(const str str) noexcept -> bool
  {
    return czstring_eq(str, "1") ? true : false;
  }

  [[nodiscard]] static auto to_string(const bool value) -> std::string
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
struct string_hint : crtp_hint<string_hint<Hint>, str>
{
  [[nodiscard]] static auto current_value() noexcept -> std::optional<str>
  {
    if (const str value = SDL_GetHint(Hint::name())) {
      return value;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const str value) noexcept -> str
  {
    return value;
  }

  [[nodiscard]] static auto to_string(const str value) -> std::string
  {
    return value;
  }
};

// A hint class that only accepts integers
template <typename Hint>
struct int_hint : crtp_hint<int_hint<Hint>, int>
{
  [[nodiscard]] static auto current_value() -> std::optional<int>
  {
    if (const str value = SDL_GetHint(Hint::name())) {
      return std::stoi(value);
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const str value) -> int
  {
    return detail::from_string<int>(value).value();
  }

  [[nodiscard]] static auto to_string(const int value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts unsigned integers
template <typename Hint>
struct uint_hint : crtp_hint<uint_hint<Hint>, uint>
{
  [[nodiscard]] static auto current_value() -> std::optional<uint>
  {
    if (const str value = SDL_GetHint(Hint::name())) {
      return static_cast<uint>(std::stoul(value));
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const str value) -> uint
  {
    return detail::from_string<uint>(value).value();
  }

  [[nodiscard]] static auto to_string(const uint value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts floats
template <typename Hint>
struct float_hint : crtp_hint<float_hint<Hint>, float>
{
  [[nodiscard]] static auto current_value() -> std::optional<float>
  {
    if (const str value = SDL_GetHint(Hint::name())) {
      return std::stof(value);
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const str value) -> float
  {
    return detail::from_string<float>(value).value();
  }

  [[nodiscard]] static auto to_string(const float value) -> std::string
  {
    return std::to_string(value);
  }
};

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_HINTS_IMPL_HEADER
