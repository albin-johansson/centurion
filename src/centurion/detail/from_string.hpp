#ifndef CENTURION_DETAIL_FROM_STRING_HEADER
#define CENTURION_DETAIL_FROM_STRING_HEADER

#include <charconv>      // from_chars
#include <optional>      // optional
#include <string>        // string, stof
#include <string_view>   // string_view
#include <system_error>  // errc
#include <type_traits>   // is_floating_point_v

#include "../compiler/compiler.hpp"

/// \cond FALSE
namespace cen::detail {

template <typename T>
[[nodiscard]] auto from_string(const std::string_view str,
                               const int base = 10) noexcept(on_msvc()) -> std::optional<T>
{
  T value{};

  const auto begin = str.data();
  const auto end = str.data() + str.size();

  const char* mismatch = end;
  std::errc error{};

  if constexpr (std::is_floating_point_v<T>) {
    if constexpr (on_gcc() || on_clang()) {
      try {
        value = std::stof(std::string{str});
      }
      catch (...) {
        return std::nullopt;
      }
    }
    else {
      const auto [ptr, err] = std::from_chars(begin, end, value);
      mismatch = ptr;
      error = err;
    }
  }
  else {
    const auto [ptr, err] = std::from_chars(begin, end, value, base);
    mismatch = ptr;
    error = err;
  }

  if (mismatch == end && error == std::errc{}) {
    return value;
  }
  else {
    return std::nullopt;
  }
}

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_FROM_STRING_HEADER
