// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>
#include <utility>

namespace cen::internal {

template <typename T>
  requires std::is_nothrow_invocable_v<T>
class Defer final
{
 public:
  [[nodiscard]]
  explicit Defer(T callable) noexcept :
    mCallable {std::move(callable)}
  {}

  ~Defer() noexcept
  {
    if (mEnabled) {
      mCallable();
      mEnabled = false;
    }
  }

  Defer(Defer&& other) noexcept :
    mCallable {std::move(other.mCallable)},
    mEnabled {std::exchange(other.mEnabled, false)}
  {}

  Defer(const Defer&) = delete;

  auto operator=(Defer&& other) noexcept -> Defer&
  {
    std::swap(mCallable, other.mCallable);
    std::swap(mEnabled, other.mEnabled);
    return *this;
  }

  auto operator=(const Defer&) -> Defer& = delete;

 private:
  T mCallable;
  bool mEnabled {true};
};

using DeferVoidFn = Defer<void (*)() noexcept>;

}  // namespace cen::internal
