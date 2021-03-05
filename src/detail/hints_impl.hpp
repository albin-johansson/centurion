#ifndef CENTURION_DETAIL_HINTS_IMPL_HEADER
#define CENTURION_DETAIL_HINTS_IMPL_HEADER

#include <cstddef>      // size_t
#include <optional>     // optional
#include <string>       // string, stoi, stoul, stof
#include <type_traits>  // is_same_v, is_convertible_v

#include "../centurion_cfg.hpp"
#include "czstring.hpp"
#include "czstring_compare.hpp"
#include "static_bimap.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

template <typename Key, std::size_t size>
using string_map = static_bimap<Key, czstring, czstring_compare, size>;

template <typename Derived, typename Arg>
class crtp_hint
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Arg>;
  }

  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return Derived::name();
  }

  [[nodiscard]] static auto value() noexcept -> std::optional<Arg>
  {
    return Derived::current_value();
  }

  [[nodiscard]] static auto to_string(Arg value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts booleans
template <typename Hint>
class bool_hint : public crtp_hint<bool_hint<Hint>, bool>
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, bool>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<bool>
  {
    return static_cast<bool>(SDL_GetHintBoolean(Hint::name(), SDL_FALSE));
  }

  [[nodiscard]] static auto to_string(const bool value) -> std::string
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
class string_hint : public crtp_hint<string_hint<Hint>, czstring>
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_convertible_v<T, czstring>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<czstring>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return std::nullopt;
    } else {
      return value;
    }
  }

  [[nodiscard]] static auto to_string(const czstring value) -> std::string
  {
    return value;
  }
};

// A hint class that only accepts integers
template <typename Hint>
class int_hint : public crtp_hint<int_hint<Hint>, int>
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, int>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<int>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return std::nullopt;
    } else {
      return std::stoi(value);
    }
  }
};

// A hint class that only accepts unsigned integers
template <typename Hint>
class unsigned_int_hint : public crtp_hint<int_hint<Hint>, unsigned int>
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, unsigned int>;
  }

  [[nodiscard]] static auto current_value() noexcept
      -> std::optional<unsigned int>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return std::nullopt;
    } else {
      return static_cast<unsigned int>(std::stoul(value));
    }
  }
};

// A hint class that only accepts floats
template <typename Hint>
class float_hint : public crtp_hint<float_hint<Hint>, float>
{
 public:
  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, float>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<float>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return std::nullopt;
    } else {
      return std::stof(value);
    }
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_HINTS_IMPL_HEADER
