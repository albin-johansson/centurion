#ifndef CENTURION_TEXT_INPUT_EVENT_HEADER
#define CENTURION_TEXT_INPUT_EVENT_HEADER

#include <SDL.h>

#include <string_view>  // string_view

#include "../centurion_cfg.hpp"
#include "../czstring.hpp"
#include "../integers.hpp"
#include "common_event.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class text_input_event
 *
 * \brief Provides information about keyboard text input events.
 *
 * \see `SDL_TextInputEvent`
 *
 * \since 4.0.0
 *
 * \headerfile text_input_event.hpp
 */
class text_input_event final : public common_event<SDL_TextInputEvent>
{
 public:
  /**
   * \brief Creates a text input event.
   *
   * \since 4.0.0
   */
  text_input_event() noexcept : common_event{event_type::text_input}
  {}

  /**
   * \brief Creates a `TextInputEvent` that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit text_input_event(const SDL_TextInputEvent& event) noexcept
      : common_event{event}
  {}

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
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * \return the text that will be used.
   * \since 4.0.0
   */
  [[nodiscard]] auto text_utf8() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<czstring>(m_event.text)};
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_TextInputEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.text = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_TEXT_INPUT_EVENT_HEADER
