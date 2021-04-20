#ifndef CENTURION_DETAIL_MAX_HEADER
#define CENTURION_DETAIL_MAX_HEADER

/// \cond FALSE
namespace cen::detail {

// clang-format off

template <typename T>
[[nodiscard]] constexpr auto max(const T& a, const T& b)
    noexcept(noexcept(a < b)) -> T
{
  return (a < b) ? b : a;
}

// clang-format on

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_MAX_HEADER
