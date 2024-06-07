// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <type_traits>
#include <utility>

#include "centurion/core/error.hpp"

namespace cen::inline v8_0_0::detail {

template <typename T>
concept scope_exit_callable =
    std::is_invocable_v<T> && std::is_destructible_v<T> &&
    std::is_nothrow_move_constructible_v<T>;

template <scope_exit_callable T>
class scope_exit final
{
 public:
  [[nodiscard]]
  explicit scope_exit(T callable) noexcept
    : m_callable {std::move(callable)},
      m_active {true}
  {}

  scope_exit(scope_exit&& other) noexcept
    : m_callable {std::move(other.m_callable)},
      m_active {std::exchange(other.m_active, false)}
  {}

  scope_exit(const scope_exit&) = delete;

  auto operator=(scope_exit&&) -> scope_exit& = delete;

  auto operator=(const scope_exit&) -> scope_exit& = delete;

  ~scope_exit() noexcept
  {
    try {
      if (m_active) {
        m_callable();
        m_active = false;
      }
    }
    catch (...) {
      emit_error_message("scope_exit destructor threw exception");
    }
  }

 private:
  T m_callable;
  bool m_active;
};

using scope_exit_fn = scope_exit<void (*)() noexcept>;

template class scope_exit<void (*)() noexcept>;

}  // namespace cen::inline v8_0_0::detail
