#ifndef CENTURION_AREA_HEADER
#define CENTURION_AREA_HEADER

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // is_integral_v, is_floating_point_v, is_same_v

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/cast.hpp"

namespace cen {

/// \addtogroup math
/// \{

template <typename T>
struct basic_area;

/**
 * \typedef iarea
 *
 * \brief An alias for `int` areas.
 *
 * \since 4.1.0
 */
using iarea = basic_area<int>;

/**
 * \typedef farea
 *
 * \brief An alias for `float` areas.
 *
 * \since 4.1.0
 */
using farea = basic_area<float>;

/**
 * \typedef darea
 *
 * \brief An alias for `double` areas.
 *
 * \since 4.1.0
 */
using darea = basic_area<double>;

/**
 * \struct basic_area
 *
 * \brief Simply represents an area with a width and height.
 *
 * \serializable
 *
 * \tparam T the type of the components of the area. Must be either an integral or
 * floating-point type. Can't be `bool`.
 *
 * \since 4.0.0
 *
 * \see `iarea`
 * \see `farea`
 * \see `darea`
 */
template <typename T>
struct basic_area final
{
  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
  static_assert(!std::is_same_v<T, bool>);

  using value_type = T;

  T width{0};   ///< The width of the area.
  T height{0};  ///< The height of the area.

#if CENTURION_HAS_FEATURE_SPACESHIP

  [[nodiscard]] constexpr auto operator==(const basic_area&) const noexcept -> bool = default;

#endif  // CENTURION_HAS_FEATURE_SPACESHIP
};

/// \name Area-related functions
/// \{

/**
 * \brief Creates an area instance with automatically deduced precision.
 *
 * \tparam T the deduced type of the width and height values.
 *
 * \param width the width of the area.
 * \param height the height of the area.
 *
 * \return an area instance with the specified width and height.
 *
 * \since 6.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto area(const T width, const T height) noexcept -> basic_area<T>
{
  return {width, height};
}

/**
 * \brief Returns the size (width x height) of an area.
 *
 * \tparam T the representation type.
 *
 * \param area the area instance that will be calculated.
 *
 * \return the size of the area.
 *
 * \since 5.3.0
 */
template <typename T>
[[nodiscard]] constexpr auto area_of(const basic_area<T> area) noexcept -> T
{
  return area.width * area.height;
}

/// \} End of area-related functions

/**
 * \brief Serializes an area instance.
 *
 * \details This function expects that the archive provides an overloaded `operator()`,
 * used for serializing data. This API is based on the Cereal serialization library.
 *
 * \tparam Archive the type of the archive.
 * \tparam T the type of the area components.
 *
 * \param archive the archive used to serialize the area.
 * \param area the area that will be serialized.
 *
 * \since 5.3.0
 */
template <typename Archive, typename T>
void serialize(Archive& archive, basic_area<T>& area)
{
  archive(area.width, area.height);
}

/// \name Area cast specializations
/// \{

template <>
[[nodiscard]] constexpr auto cast(const iarea& from) noexcept -> darea
{
  return {static_cast<double>(from.width), static_cast<double>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const iarea& from) noexcept -> farea
{
  return {static_cast<float>(from.width), static_cast<float>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const farea& from) noexcept -> darea
{
  return {static_cast<double>(from.width), static_cast<double>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const farea& from) noexcept -> iarea
{
  return {static_cast<int>(from.width), static_cast<int>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const darea& from) noexcept -> farea
{
  return {static_cast<float>(from.width), static_cast<float>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const darea& from) noexcept -> iarea
{
  return {static_cast<int>(from.width), static_cast<int>(from.height)};
}

/// \} End of area cast specializations

/// \name Area comparison operators
/// \{

#if !CENTURION_HAS_FEATURE_SPACESHIP

/**
 * \brief Indicates whether or not two areas are considered to be equal.
 *
 * \param lhs the left-hand side area.
 * \param rhs the right-hand side area.
 *
 * \return `true` if the areas are equal; `false` otherwise.
 *
 * \since 4.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_area<T>& lhs,
                                        const basic_area<T>& rhs) noexcept -> bool
{
  return (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

/**
 * \brief Indicates whether or not two areas aren't considered to be equal.
 *
 * \param lhs the left-hand side area.
 * \param rhs the right-hand side area.
 *
 * \return `true` if the areas aren't equal; `false` otherwise.
 *
 * \since 4.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_area<T>& lhs,
                                        const basic_area<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

#endif  // CENTURION_HAS_FEATURE_SPACESHIP

/// \} End of area comparison operators

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of an area.
 *
 * \tparam T the type of the area components.
 *
 * \param area the area that will be converted.
 *
 * \return a string that represents the area.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_area<T>& area) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("area{{width: {}, height: {}}}", area.width, area.height);
#else
  return "area{width: " + std::to_string(area.width) +
         ", height: " + std::to_string(area.height) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of an area using a stream.
 *
 * \tparam T the type of the area components.
 *
 * \param stream the stream that will be used.
 * \param area the are that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_area<T>& area) -> std::ostream&
{
  return stream << to_string(area);
}

/// \} End of streaming

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_AREA_HEADER