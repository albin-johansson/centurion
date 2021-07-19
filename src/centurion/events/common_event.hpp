#ifndef CENTURION_COMMON_EVENT_HEADER
#define CENTURION_COMMON_EVENT_HEADER

#include <SDL.h>

#include <utility>  // move

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "event_type.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class common_event
 *
 * \brief The templated base class of all Centurion events.
 *
 * \details This class defines the common API of all events and provides the
 * storage of the SDL2 event.
 *
 * \tparam T an SDL event type.
 *
 * \since 4.0.0
 */
template <typename T>
class common_event
{
 public:
  /**
   * \brief Creates a `common_event` and zero-initializes the internal event
   * except for the timestamp and the supplied type.
   *
   * \param type the type of the event.
   *
   * \since 5.1.0
   */
  explicit common_event(const event_type type) noexcept
  {
    set_time(SDL_GetTicks());
    set_type(type);
  }

  /**
   * \brief Creates a common_event and copies the supplied event.
   *
   * \param event the event that will be copied.
   *
   * \since 4.0.0
   */
  explicit common_event(const T& event) : m_event{event}
  {}

  /**
   * \brief Creates a common_event and moves the contents of the supplied event.
   *
   * \param event the event that will be moved.
   *
   * \since 4.0.0
   */
  explicit common_event(T&& event) : m_event{std::move(event)}
  {}

  /**
   * \brief Sets the timestamp that is associated with the creation of the
   * event.
   *
   * \param timestamp the timestamp that should be associated with the creation
   * of the event.
   *
   * \since 4.0.0
   */
  void set_time(const u32 timestamp) noexcept
  {
    m_event.timestamp = timestamp;
  }

  /**
   * \brief Sets the event type value associated with the event.
   *
   * \param type the event type value associated with the event.
   *
   * \since 4.0.0
   */
  void set_type(const event_type type) noexcept
  {
    m_event.type = to_underlying(type);
  }

  /**
   * \brief Returns the timestamp associated with the creation of the event.
   *
   * \return the timestamp associated with the creation of the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto time() const noexcept -> u32
  {
    return m_event.timestamp;
  }

  /**
   * \brief Returns the event type value associated with the event.
   *
   * \return the event type value associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto type() const noexcept -> event_type
  {
    return static_cast<event_type>(m_event.type);
  }

  /**
   * \brief Returns the internal event.
   *
   * \return the internal event.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> const T&
  {
    return m_event;
  }

 protected:
  T m_event{};
};

/// \name SDL event conversions
/// \{

template <typename T>
[[nodiscard]] auto as_sdl_event(const common_event<T>& event) -> SDL_Event;

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_COMMON_EVENT_HEADER
