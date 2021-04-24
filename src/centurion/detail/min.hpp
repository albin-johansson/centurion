#ifndef CENTURION_DETAIL_MIN_HEADER
#define CENTURION_DETAIL_MIN_HEADER

/// \cond FALSE
namespace cen::detail {

template <typename T>
[[nodiscard]] constexpr auto min(const T& a, const T& b) noexcept(noexcept(a < b)) -> T
{
  return (a < b) ? a : b;
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_MIN_HEADER
