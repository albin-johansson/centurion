#ifndef CENTURION_SEEK_MODE_HEADER
#define CENTURION_SEEK_MODE_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string

#include "../core/exception.hpp"

namespace cen {

/// \addtogroup system
/// \{

/**
 * \enum seek_mode
 *
 * \brief Provides values that represent various file seek modes.
 *
 * \since 5.3.0
 */
enum class seek_mode
{
  from_beginning = RW_SEEK_SET,       ///< From the beginning.
  relative_to_current = RW_SEEK_CUR,  ///< Relative to the current read point.
  relative_to_end = RW_SEEK_END       ///< Relative to the end.
};

/**
 * \brief Returns a textual version of the supplied seek mode.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(seek_mode::from_beginning) == "from_beginning"`.
 *
 * \param mode the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const seek_mode mode) -> std::string
{
  switch (mode)
  {
    case seek_mode::from_beginning:
      return "from_beginning";

    case seek_mode::relative_to_current:
      return "relative_to_current";

    case seek_mode::relative_to_end:
      return "relative_to_end";

    default:
      throw cen_error{"Did not recognize file mode!"};
  }
}

/**
 * \brief Prints a textual representation of a seek mode enumerator.
 *
 * \param stream the output stream that will be used.
 * \param mode the enumerator that will be printed.
 *
 * \see `to_string(seek_mode)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const seek_mode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

/// \} End of group system

}  // namespace cen

#endif  // CENTURION_SEEK_MODE_HEADER