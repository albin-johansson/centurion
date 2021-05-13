#ifndef CENTURION_DETAIL_MAX_HEADER
#define CENTURION_DETAIL_MAX_HEADER

/// \cond FALSE
namespace cen::detail {

template <typename T>
[[nodiscard]] constexpr auto max(const T& a, const T& b) noexcept(noexcept(a < b)) -> T
{
  return (a < b) ? b : a;
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_MAX_HEADER
