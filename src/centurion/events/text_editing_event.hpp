#ifndef CENTURION_TEXT_EDITING_EVENT_HEADER
#define CENTURION_TEXT_EDITING_EVENT_HEADER

#include <SDL.h>

#include <string_view>  // string_view

#include "../core/integers.hpp"
#include "../core/str.hpp"
#include "../detail/clamp.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class text_editing_event
 *
 * \brief Represents an event triggered by keyboard text editing.
 *
 * \note This class doesn't provide a setter for the text, since it's
 * impossible to assign a value to a variable of type `char[32]` in C++.
 *
 * \see `SDL_TextEditingEvent`
 *
 * \since 4.0.0
 */
class text_editing_event final : public common_event<SDL_TextEditingEvent>
{
 public:
  /**
   * \brief Creates a text editing event.
   *
   * \since 4.0.0
   */
  text_editing_event() noexcept : common_event{event_type::text_editing}
  {
    check_length();
  }

  /**
   * \brief Creates an event that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit text_editing_event(const SDL_TextEditingEvent& event) noexcept : common_event{event}
  {
    check_length();
  }

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the location to begin editing from.
   *
   * \param start the location to begin editing from.
   *
   * \since 4.0.0
   */
  void set_start(const i32 start) noexcept
  {
    m_event.start = start;
  }

  /**
   * \brief Sets the number of characters to edit from the start point.
   *
   * \details The supplied value will be clamped to the range [0, 32].
   *
   * \param length the number of characters to edit from the start point.
   *
   * \since 4.0.0
   */
  void set_length(const i32 length) noexcept
  {
    m_event.length = detail::clamp(length, 0, 32);
  }

  /**
   * \brief Returns the window ID associated with the event.
   *
   * \return the window ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the text that will be used, as a null-terminated string in
   * UTF-8 encoding.
   *
   * \return the text that will be used.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto text() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<str>(m_event.text)};
  }

  /**
   * \brief Returns the location to begin editing from.
   *
   * \return the location to begin editing from.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto start() const noexcept -> i32
  {
    return m_event.start;
  }

  /**
   * \brief Returns the number of characters to edit from the start point.
   *
   * \details The returned value will always be in the range [0, 32].
   *
   * \return the number of characters to edit from the start point.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto length() const noexcept -> i32
  {
    return m_event.length;
  }

 private:
  void check_length() noexcept
  {
    m_event.length = detail::clamp(m_event.length, 0, 32);
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_TextEditingEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.edit = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_TEXT_EDITING_EVENT_HEADER
