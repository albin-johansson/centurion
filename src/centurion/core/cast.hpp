#ifndef CENTURION_CAST_HEADER
#define CENTURION_CAST_HEADER

namespace cen {

/**
 * \brief Casts a value to a value of another type.
 *
 * \ingroup core
 *
 * \details This is the default implementation, which simply attempts to use
 * `static_cast`. The idea is that this function will be specialized for various Centurion
 * and SDL types. This is useful because it isn't always possible to implement conversion
 * operators as members.
 *
 * \tparam To the type of the value that will be converted.
 * \tparam From the type that the value will be casted to.
 *
 * \param from the value that will be converted.
 *
 * \return the result of casting the supplied value to the specified type.
 *
 * \since 5.0.0
 */
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

}  // namespace cen

#endif  // CENTURION_CAST_HEADER
