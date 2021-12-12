#ifndef CENTURION_DETAIL_HINTS_IMPL_HEADER
#define CENTURION_DETAIL_HINTS_IMPL_HEADER

#include <cstddef>      // size_t
#include <cstdlib>      // atof
#include <optional>     // optional
#include <string>       // string, stoi, stoul, stof
#include <type_traits>  // enable_if_t, is_same_v, is_convertible_v

#include "../core/common.hpp"
#include "czstring_compare.hpp"
#include "static_bimap.hpp"
#include "stdlib.hpp"

/// \cond FALSE

namespace cen::detail {

template <typename Hint, typename T>
using enable_if_hint_arg_t = std::enable_if_t<Hint::template valid_arg<T>(), int>;

template <typename Key, std::size_t Size>
using string_map = static_bimap<Key, const char*, czstring_compare, Size>;

template <typename Derived, typename Arg>
struct crtp_hint {
  using value_type = Arg;

  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, value_type>;
  }
};

// A hint class that only accepts booleans
template <typename Hint>
struct bool_hint : crtp_hint<bool_hint<Hint>, bool> {
  [[nodiscard]] static auto current_value() noexcept -> std::optional<bool>
  {
    return SDL_GetHintBoolean(Hint::name(), SDL_FALSE) == SDL_TRUE;
  }

  [[nodiscard]] static auto from_string(const char* str) noexcept -> bool
  {
    return cmp(str, "1") ? true : false;
  }

  [[nodiscard]] static auto to_string(const bool value) -> std::string
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
struct string_hint : crtp_hint<string_hint<Hint>, const char*> {
  [[nodiscard]] static auto current_value() noexcept -> std::optional<const char*>
  {
    if (const char* value = SDL_GetHint(Hint::name())) {
      return value;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const char* value) noexcept -> const char*
  {
    return value;
  }

  [[nodiscard]] static auto to_string(const char* value) -> std::string { return value; }
};

// A hint class that only accepts integers
template <typename Hint>
struct int_hint : crtp_hint<int_hint<Hint>, int> {
  [[nodiscard]] static auto current_value() -> std::optional<int>
  {
    if (const char* value = SDL_GetHint(Hint::name())) {
      return std::stoi(value);
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const char* value) -> int
  {
    return detail::stoi(value).value();
  }

  [[nodiscard]] static auto to_string(const int value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts unsigned integers
template <typename Hint>
struct uint_hint : crtp_hint<uint_hint<Hint>, uint> {
  [[nodiscard]] static auto current_value() -> std::optional<uint>
  {
    if (const char* value = SDL_GetHint(Hint::name())) {
      return static_cast<uint>(std::stoul(value));
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const char* value) -> uint
  {
    return detail::stoi<uint>(value).value();
  }

  [[nodiscard]] static auto to_string(const uint value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts floats
template <typename Hint>
struct float_hint : crtp_hint<float_hint<Hint>, float> {
  [[nodiscard]] static auto current_value() -> std::optional<float>
  {
    if (const char* value = SDL_GetHint(Hint::name())) {
      return std::stof(value);
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const char* value) -> float
  {
    return std::atof(value);
  }

  [[nodiscard]] static auto to_string(const float value) -> std::string
  {
    return std::to_string(value);
  }
};

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_HINTS_IMPL_HEADER
