#ifndef CENTURION_VECTOR3_HEADER
#define CENTURION_VECTOR3_HEADER

#include <ostream>  // ostream
#include <string>   // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup math
/// \{

/**
 * \struct vector3
 *
 * \brief A simple representation of a 3-dimensional vector.
 *
 * \serializable
 *
 * \tparam T the representation type, e.g. `float` or `double`.
 *
 * \since 5.2.0
 */
template <typename T>
struct vector3 final
{
  using value_type = T;  ///< The type of the vector components.

  value_type x{};  ///< The x-coordinate of the vector.
  value_type y{};  ///< The y-coordinate of the vector.
  value_type z{};  ///< The z-coordinate of the vector.

#if CENTURION_HAS_FEATURE_SPACESHIP

  [[nodiscard]] constexpr auto operator<=>(const vector3&) const noexcept = default;

#endif  // CENTURION_HAS_FEATURE_SPACESHIP

  /**
   * \brief Casts the vector to a vector with another representation type.
   *
   * \tparam U the target vector type.
   *
   * \return the result vector.
   *
   * \since 5.2.0
   */
  template <typename U>
  [[nodiscard]] explicit operator vector3<U>() const noexcept
  {
    using target_value_type = typename vector3<U>::value_type;
    return vector3<U>{static_cast<target_value_type>(x),
                      static_cast<target_value_type>(y),
                      static_cast<target_value_type>(z)};
  }
};

/**
 * \brief Serializes a 3D-vector.
 *
 * \details This function expects that the archive provides an overloaded `operator()`,
 * used for serializing data. This API is based on the Cereal serialization library.
 *
 * \tparam Archive the type of the archive.
 * \tparam T the type of the vector components.
 *
 * \param archive the archive used to serialize the vector.
 * \param vector the vector that will be serialized.
 *
 * \since 5.3.0
 */
template <typename Archive, typename T>
void serialize(Archive& archive, vector3<T>& vector)
{
  archive(vector.x, vector.y, vector.z);
}

/// \name Vector3 comparison operators
/// \{

#if !CENTURION_HAS_FEATURE_SPACESHIP

/**
 * \brief Indicates whether or not two 3D vectors are equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the vectors are equal; `false` otherwise.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const vector3<T>& lhs, const vector3<T>& rhs) noexcept
    -> bool
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

/**
 * \brief Indicates whether or not two 3D vectors aren't equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the vectors aren't equal; `false` otherwise.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const vector3<T>& lhs, const vector3<T>& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

#endif  // CENTURION_HAS_FEATURE_SPACESHIP

/// \} End of vector3 comparison operators

/// \name String conversions
/// \{

/**
 * \brief Returns a string that represents a vector.
 *
 * \tparam T the representation type used by the vector.
 *
 * \param vector the vector that will be converted to a string.
 *
 * \return a string that represents the supplied vector.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] auto to_string(const vector3<T>& vector) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("vector3{{x: {}, y: {}, z: {}}}", vector.x, vector.y, vector.z);
#else
  return "vector3{x: " + std::to_string(vector.x) + ", y: " + std::to_string(vector.y) +
         ", z: " + std::to_string(vector.z) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a vector.
 *
 * \tparam T the representation type used by the vector.
 *
 * \param stream the stream that will be used.
 * \param vector the vector that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const vector3<T>& vector) -> std::ostream&
{
  return stream << to_string(vector);
}

/// \} End of streaming

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_VECTOR3_HEADER
