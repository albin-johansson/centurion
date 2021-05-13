#ifndef CENTURION_DETAIL_ANY_EQ_HEADER
#define CENTURION_DETAIL_ANY_EQ_HEADER

/// \cond FALSE
namespace cen::detail {

// clang-format off

/**
 * \brief Indicates whether or not any of the supplied values are equal to a specific value.
 *
 * \tparam T the type of the value to look for.
 *
 * \tparam Args the type of the arguments that will be checked.
 *
 * \param value the value to look for.
 * \param args the arguments that will be compared with the value.
 *
 * \return `true` if any of the supplied values are equal to `value`; `false` otherwise.
 *
 * \since 5.1.0
 */
template <typename T, typename... Args>
[[nodiscard]] constexpr auto any_eq(const T& value, Args&&... args)
    noexcept(noexcept( ((value == args) || ...) )) -> bool
{
  return ((value == args) || ...);
}

// clang-format on

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_ANY_EQ_HEADER
