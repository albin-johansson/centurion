#ifndef CENTURION_DETAIL_OWNER_HANDLE_API_HEADER
#define CENTURION_DETAIL_OWNER_HANDLE_API_HEADER

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <type_traits>  // enable_if_t, is_same_v, true_type, false_type

#include "../centurion_cfg.hpp"
#include "../exception.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

template <typename T>
using is_owner = std::enable_if_t<std::is_same_v<T, std::true_type>, bool>;

template <typename T>
using is_handle = std::enable_if_t<std::is_same_v<T, std::false_type>, bool>;

template <typename T>
[[nodiscard]] constexpr auto is_owning() noexcept -> bool
{
  return std::is_same_v<T, std::true_type>;
}

template <typename B, typename Type, typename Deleter>
class pointer_manager final
{
  using managed_ptr = std::unique_ptr<Type, Deleter>;
  using raw_ptr = Type*;
  using pointer_type = std::conditional_t<B::value, managed_ptr, raw_ptr>;

 public:
  pointer_manager() noexcept = default;

  explicit pointer_manager(Type* ptr) noexcept : m_ptr{ptr}
  {}

  template <typename BB = B, is_owner<BB> = true>
  void reset(Type* ptr) noexcept
  {
    m_ptr.reset(ptr);
  }

  auto operator->() noexcept -> Type*
  {
    return get();
  }

  auto operator->() const noexcept -> const Type*
  {
    return get();
  }

  auto operator*() noexcept -> Type&
  {
    assert(m_ptr);
    return *m_ptr;
  }

  auto operator*() const noexcept -> const Type&
  {
    assert(m_ptr);
    return *m_ptr;
  }

  explicit operator bool() const noexcept
  {
    return m_ptr != nullptr;
  }

  /*implicit*/ operator Type*() const noexcept
  {
    return get();
  }

  template <typename BB = B, is_owner<BB> = true>
  [[nodiscard]] auto release() noexcept -> Type*
  {
    return m_ptr.release();
  }

  [[nodiscard]] auto get() const noexcept -> Type*
  {
    if constexpr (B::value)
    {
      return m_ptr.get();
    }
    else
    {
      return m_ptr;
    }
  }

 private:
  pointer_type m_ptr{};
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_OWNER_HANDLE_API_HEADER
