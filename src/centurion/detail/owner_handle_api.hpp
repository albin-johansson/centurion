#ifndef CENTURION_DETAIL_OWNER_HANDLE_API_HPP_
#define CENTURION_DETAIL_OWNER_HANDLE_API_HPP_

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <type_traits>  // enable_if_t, is_same_v, true_type, false_type

#include "../common.hpp"
#include "../memory.hpp"

/// \cond FALSE

namespace cen::detail {

using OwnerTag = std::true_type;
using HandleTag = std::false_type;

template <typename T>
inline constexpr bool is_owner = std::is_same_v<T, OwnerTag>;

template <typename T>
inline constexpr bool is_handle = std::is_same_v<T, HandleTag>;

template <typename T>
using EnableOwner = std::enable_if_t<is_owner<T>, int>;

template <typename T>
using EnableHandle = std::enable_if_t<is_handle<T>, int>;

template <typename B, typename Type>
class Pointer final {
 public:
  using ManagedPtr = Managed<Type>;
  using RawPtr = Type*;
  using PointerType = std::conditional_t<B::value, ManagedPtr, RawPtr>;

  Pointer() noexcept = default;

  explicit Pointer(Type* ptr) noexcept : mPtr{ptr} {}

  template <typename BB = B, EnableOwner<BB> = 0>
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

  template <typename BB = B, EnableOwner<BB> = 0>
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
  PointerType mPtr{};
};

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_OWNER_HANDLE_API_HPP_
