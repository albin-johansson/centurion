/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_DETAIL_OWNER_HANDLE_API_HPP_
#define CENTURION_DETAIL_OWNER_HANDLE_API_HPP_

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <type_traits>  // enable_if_t, is_same_v, true_type, false_type

#include "../common.hpp"
#include "../memory.hpp"

namespace cen::detail {

using owner_tag = std::true_type;
using handle_tag = std::false_type;

template <typename T>
inline constexpr bool is_owner = std::is_same_v<T, owner_tag>;

template <typename T>
inline constexpr bool is_handle = std::is_same_v<T, handle_tag>;

template <typename T>
using enable_for_owner = std::enable_if_t<is_owner<T>, int>;

template <typename T>
using enable_for_handle = std::enable_if_t<is_handle<T>, int>;

template <typename B, typename Type>
class pointer final
{
 public:
  using smart_ptr = managed_ptr<Type>;
  using raw_ptr = Type*;
  using pointer_type = std::conditional_t<B::value, smart_ptr, raw_ptr>;

  pointer() noexcept = default;

  explicit pointer(Type* ptr) noexcept : mPtr{ptr} {}

  template <typename BB = B, enable_for_owner<BB> = 0>
  void reset(Type* ptr) noexcept
  {
    mPtr.reset(ptr);
  }

  auto operator->() noexcept -> Type* { return get(); }

  auto operator->() const noexcept -> const Type* { return get(); }

  auto operator*() noexcept -> Type&
  {
    assert(mPtr);
    return *mPtr;
  }

  auto operator*() const noexcept -> const Type&
  {
    assert(mPtr);
    return *mPtr;
  }

  explicit operator bool() const noexcept { return mPtr != nullptr; }

  /*implicit*/ operator Type*() const noexcept { return get(); }

  template <typename BB = B, enable_for_owner<BB> = 0>
  [[nodiscard]] auto release() noexcept -> Type*
  {
    return mPtr.release();
  }

  [[nodiscard]] auto get() const noexcept -> Type*
  {
    if constexpr (B::value) {
      return mPtr.get();
    }
    else {
      return mPtr;
    }
  }

 private:
  pointer_type mPtr{};
};

}  // namespace cen::detail

#endif  // CENTURION_DETAIL_OWNER_HANDLE_API_HPP_
