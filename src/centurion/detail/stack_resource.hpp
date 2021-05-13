#ifndef CENTURION_DETAIL_STACK_RESOURCE_HEADER
#define CENTURION_DETAIL_STACK_RESOURCE_HEADER

#include "../core/macros.hpp"

#ifdef CENTURION_HAS_STD_MEMORY_RESOURCE

#include <array>            // array
#include <cstddef>          // byte, size_t
#include <memory_resource>  // memory_resource, monotonic_buffer_resource

/// \cond FALSE
namespace cen::detail {

template <std::size_t bufferSize>
class stack_resource final
{
 public:
  [[nodiscard]] auto get() noexcept -> std::pmr::memory_resource*
  {
    return &m_pool;
  }

 private:
  std::array<std::byte, bufferSize> m_buffer{};
  std::pmr::monotonic_buffer_resource m_pool{m_buffer.data(), sizeof m_buffer};
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_HAS_STD_MEMORY_RESOURCE
#endif  // CENTURION_DETAIL_STACK_RESOURCE_HEADER
