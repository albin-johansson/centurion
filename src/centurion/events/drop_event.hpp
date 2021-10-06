#ifndef CENTURION_DROP_EVENT_HEADER
#define CENTURION_DROP_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class drop_event
 *
 * \brief Represents the event of requesting a file to be opened.
 *
 * \see `SDL_DropEvent`
 *
 * \since 4.0.0
 */
class drop_event final : public common_event<SDL_DropEvent>
{
 public:
  /**
   * \brief Creates a drop event of type `drop_file`.
   *
   * \since 4.0.0
   */
  drop_event() noexcept : common_event{event_type::drop_file}
  {}

  /**
   * \brief Creates a drop event based on the supplied event.
   *
   * \param event the SDL drop event that will be copied.
   *
   * \since 4.0.0
   */
  explicit drop_event(const SDL_DropEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Destroys the drop event.
   *
   * \details The associated file will be freed depending on the value
   * returned from the `will_free_file()` function.
   *
   * \since 4.0.0
   */
  ~drop_event() noexcept
  {
    if (m_event.file && m_willFreeFile) {
      SDL_free(m_event.file);
    }
  }

  /**
   * \brief Sets whether or not the associated file will be freed by this event.
   *
   * \details If you set this property to `false`, you **must** remember to
   * call `SDL_free` on the file pointer by yourself. Otherwise, you'll end
   * up with a memory leak!
   *
   * \param freeFile `true` if the associated file should be freed upon the
   * destruction of the event; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_will_free_file(const bool freeFile) noexcept
  {
    m_willFreeFile = freeFile;
  }

  /**
   * \brief Sets the file associated with the drop event.
   *
   * \details The ownership of the supplied pointer will, by default, not be
   * claimed by this event.
   *
   * \note The supplied pointer will be freed using `SDL_free` upon the
   * destruction of the event *if* the `will_free_file` property is set to
   * **true**.
   *
   * \note If the `will_free_file` property is `true`, then **the previously
   * set file pointer will be freed** by calling this function. However, if the
   * `will_free_file` property is `false`, then the old file pointer is
   * simply overridden. Of course, this may, if you're not careful, introduce a
   * memory leak in your program!
   *
   * \warning Make sure you know what you are doing when using this function.
   *
   * \param file a pointer to a file, can safely be null.
   *
   * \since 4.0.0
   */
  void set_file(char* file) noexcept
  {
    if (m_event.file && m_willFreeFile) {
      SDL_free(m_event.file);
    }
    m_event.file = file;
  }

  /**
   * \brief Sets the ID of the window that is the target of the drop event.
   *
   * \param id the ID of the window that is the target of the drop event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Indicates whether or not the associated file will be freed by
   * this event upon destruction.
   *
   * \details By default, this property is set to **false**.
   *
   * \return `true` if the associated file will be freed upon destruction;
   * `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto will_free_file() const noexcept -> bool
  {
    return m_willFreeFile;
  }

  /**
   * \brief Returns a pointer to the associated file.
   *
   * \warning Do **not** claim ownership of the returned pointer *without*
   * setting the `will_free_file` property to **false**.
   *
   * \note The returned pointer is always `nullptr` for `drop_begin` and
   * `drop_complete` drop events.
   *
   * \return a pointer to the file associated with the event, might be null.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto file() const noexcept -> char*
  {
    return m_event.file;
  }

  /**
   * \brief Returns the ID of the window that is the target of the drop
   * event, if there even is one.
   *
   * \return the ID of the window that is the target of the drop event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

 private:
  bool m_willFreeFile{false};
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_DropEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.drop = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_DROP_EVENT_HEADER
