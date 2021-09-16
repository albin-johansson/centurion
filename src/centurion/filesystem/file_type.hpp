#ifndef CENTURION_FILE_TYPE_HEADER
#define CENTURION_FILE_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup filesystem
/// \{

/**
 * \enum file_type
 *
 * \brief Provides values that represent different file types.
 *
 * \since 5.3.0
 */
enum class file_type : uint
{
  unknown = SDL_RWOPS_UNKNOWN,     ///< An unknown file type.
  win32 = SDL_RWOPS_WINFILE,       ///< A Win32 file.
  stdio = SDL_RWOPS_STDFILE,       ///< A STDIO file.
  jni = SDL_RWOPS_JNIFILE,         ///< An Android asset file.
  memory = SDL_RWOPS_MEMORY,       ///< A memory stream file.
  memory_ro = SDL_RWOPS_MEMORY_RO  ///< A read-only memory stream file.
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied file type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(file_type::stdio) == "stdio"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const file_type type) -> std::string_view
{
  switch (type) {
    case file_type::unknown:
      return "unknown";

    case file_type::win32:
      return "win32";

    case file_type::stdio:
      return "stdio";

    case file_type::jni:
      return "jni";

    case file_type::memory:
      return "memory";

    case file_type::memory_ro:
      return "memory_ro";

    default:
      throw cen_error{"Did not recognize file type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a file type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(file_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const file_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_FILE_TYPE_HEADER
