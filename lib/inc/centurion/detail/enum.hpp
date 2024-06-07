// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <type_traits>

namespace cen::inline v8_0_0::detail {

template <typename T>
concept enum_type = std::is_enum_v<T>;

template <enum_type T>
[[nodiscard]] constexpr auto to_underlying(const T enumerator) noexcept
    -> std::underlying_type_t<T>
{
  return static_cast<std::underlying_type_t<T>>(enumerator);
}

}  // namespace cen::inline v8_0_0::detail
