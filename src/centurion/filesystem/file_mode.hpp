#ifndef CENTURION_FILE_MODE_HEADER
#define CENTURION_FILE_MODE_HEADER

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup filesystem
/// \{

/**
 * \enum file_mode
 *
 * \brief Provides values that represent different file modes.
 *
 * \details This enum provides values that directly correspond to each of the possible SDL
 * file mode strings, such as "r" or "rb".
 *
 * \since 5.3.0
 */
enum class file_mode
{
  read_existing,         ///< "r"
  read_existing_binary,  ///< "rb"

  write,         ///< "w"
  write_binary,  ///< "wb"

  append_or_create,         ///< "a"
  append_or_create_binary,  ///< "ab"

  read_write_existing,         ///< "r+"
  read_write_existing_binary,  ///< "rb+"

  read_write_replace,         ///< "w+"
  read_write_replace_binary,  ///< "wb+"

  read_append,        ///< "a+"
  read_append_binary  ///< "ab+"
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied file mode.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(file_mode::read_append) == "read_append"`.
 *
 * \param mode the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const file_mode mode) -> std::string_view
{
  switch (mode) {
    case file_mode::read_existing:
      return "read_existing";

    case file_mode::read_existing_binary:
      return "read_existing_binary";

    case file_mode::write:
      return "write";

    case file_mode::write_binary:
      return "write_binary";

    case file_mode::append_or_create:
      return "append_or_create";

    case file_mode::append_or_create_binary:
      return "append_or_create_binary";

    case file_mode::read_write_existing:
      return "read_write_existing";

    case file_mode::read_write_existing_binary:
      return "read_write_existing_binary";

    case file_mode::read_write_replace:
      return "read_write_replace";

    case file_mode::read_write_replace_binary:
      return "read_write_replace_binary";

    case file_mode::read_append:
      return "read_append";

    case file_mode::read_append_binary:
      return "read_append_binary";

    default:
      throw cen_error{"Did not recognize file mode!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a file mode enumerator.
 *
 * \param stream the output stream that will be used.
 * \param mode the enumerator that will be printed.
 *
 * \see `to_string(file_mode)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const file_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of streaming

/// \} End of group filesystem

}  // namespace cen

#endif  // CENTURION_FILE_MODE_HEADER
