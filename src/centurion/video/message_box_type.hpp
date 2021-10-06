#ifndef CENTURION_MESSAGE_BOX_TYPE_HEADER
#define CENTURION_MESSAGE_BOX_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum message_box_type
 *
 * \brief Serves as a hint of the purpose of a message box.
 *
 * \details Message boxes can indicate errors, warnings and general information.
 *
 * \since 5.0.0
 */
enum class message_box_type : u32
{
  error = SDL_MESSAGEBOX_ERROR,
  warning = SDL_MESSAGEBOX_WARNING,
  information = SDL_MESSAGEBOX_INFORMATION
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied message box type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(message_box_type::error) == "error"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const message_box_type type) -> std::string_view
{
  switch (type) {
    case message_box_type::error:
      return "error";

    case message_box_type::warning:
      return "warning";

    case message_box_type::information:
      return "information";

    default:
      throw cen_error{"Did not recognize message box type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a message box type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(message_box_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const message_box_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_MESSAGE_BOX_TYPE_HEADER
