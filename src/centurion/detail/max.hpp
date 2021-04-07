#ifndef CENTURION_DETAIL_MAX_HEADER
#define CENTURION_DETAIL_MAX_HEADER

/// \cond FALSE
namespace cen::detail {

// clang-format off

template <typename T>
[[nodiscard]] constexpr auto max(const T& left, const T& right)
    noexcept(noexcept(left < right)) -> T
{
  return (left < right) ? right : left;
}

// clang-format on

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_MAX_HEADER
