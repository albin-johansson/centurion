#ifndef CENTURION_DETAIL_TO_STRING_HEADER
#define CENTURION_DETAIL_TO_STRING_HEADER

#include <array>         // array
#include <charconv>      // to_chars
#include <optional>      // optional, nullopt
#include <string>        // string
#include <system_error>  // errc
#include <type_traits>   // is_floating_point_v

#include "../compiler.hpp"

/// \cond FALSE
namespace cen::detail {

/**
 * \brief Returns a string representation of an arithmetic value.
 *
 * \note This function is guaranteed to work for 32-bit integers and floats.
 * You might have to increase the buffer size for larger types.
 *
 * \remark On GCC, this function simply calls `std::to_string`, since the
 * `std::to_chars` implementation seems to be lacking at the time of writing.
 *
 * \tparam bufferSize the size of the stack buffer used, must be big enough
 * to store the characters of the string representation of the value.
 * \tparam T the type of the value that will be converted, must be arithmetic.
 *
 * \param value the value that will be converted.
 *
 * \return a string representation of the supplied value; `std::nullopt` if
 * something goes wrong.
 *
 * \since 5.0.0
 */
template <std::size_t bufferSize = 16, typename T>
[[nodiscard]] auto to_string(T value) -> std::optional<std::string>
{
  if constexpr (on_gcc() || (on_clang() && std::is_floating_point_v<T>))
  {
    return std::to_string(value);
  }
  else
  {
    std::array<char, bufferSize> buffer{};
    const auto [ptr, err] =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);

    if (err == std::errc{})
    {
      return std::string{buffer.data(), ptr};
    }
    else
    {
      return std::nullopt;
    }
  }
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_TO_STRING_HEADER
