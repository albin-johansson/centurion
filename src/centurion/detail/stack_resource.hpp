#ifndef CENTURION_DETAIL_STACK_RESOURCE_HEADER
#define CENTURION_DETAIL_STACK_RESOURCE_HEADER

#include "../compiler/features.hpp"
#include "../core/integers.hpp"

#if CENTURION_HAS_FEATURE_MEMORY_RESOURCE

#include <array>            // array
#include <cstddef>          // byte
#include <memory_resource>  // memory_resource, monotonic_buffer_resource

/// \cond FALSE
namespace cen::detail {

template <usize BufferSize>
class stack_resource final
{
 public:
  [[nodiscard]] auto get() noexcept -> std::pmr::memory_resource*
  {
    return &m_pool;
  }

 private:
  std::array<std::byte, BufferSize> m_buffer{};
  std::pmr::monotonic_buffer_resource m_pool{m_buffer.data(), sizeof m_buffer};
};

}  // namespace cen::detail
   /// \endcond

#endif  // CENTURION_HAS_FEATURE_MEMORY_RESOURCE
#endif  // CENTURION_DETAIL_STACK_RESOURCE_HEADER
