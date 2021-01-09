#ifndef CENTURION_DETAIL_STACK_RESOURCE_HEADER
#define CENTURION_DETAIL_STACK_RESOURCE_HEADER

#include <array>            // array
#include <cstddef>          // byte
#include <memory_resource>  // memory_resource, monotonic_buffer_resource

#include "../centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

template <std::size_t bufferSize>
class stack_resource final
{
 public:
  stack_resource() : m_buffer{}, m_pool{m_buffer.data(), sizeof m_buffer}
  {}

  [[nodiscard]] auto get() noexcept -> std::pmr::memory_resource*
  {
    return &m_pool;
  }

 private:
  std::array<std::byte, bufferSize> m_buffer;
  std::pmr::monotonic_buffer_resource m_pool;
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_STACK_RESOURCE_HEADER
