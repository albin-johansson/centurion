#ifndef CENTURION_EVENT_BASE_HPP_
#define CENTURION_EVENT_BASE_HPP_

#include <SDL.h>

#include <utility>  // move

#include "../common.hpp"
#include "event_type.hpp"

namespace cen {

/// The templated base class of all Centurion events.
///
/// This class defines the common API of all events and provides the storage of the SDL event.
///
/// \tparam T the SDL event type.
template <typename T>
class EventBase {
 public:
  explicit EventBase(const EventType type) noexcept
  {
    SetTimestamp(SDL_GetTicks());
    SetType(type);
  }

  explicit EventBase(const T& event) : m_event{event} {}

  explicit EventBase(T&& event) : m_event{std::move(event)} {}

  /// Sets the timestamp of the creation of the event. TODO U32_Millis?
  void SetTimestamp(const Uint32 timestamp) noexcept { m_event.timestamp = timestamp; }

  void SetType(const EventType type) noexcept { m_event.type = ToUnderlying(type); }

  [[nodiscard]] auto GetTimestamp() const noexcept -> Uint32 { return m_event.timestamp; }

  [[nodiscard]] auto GetType() const noexcept -> EventType { return EventType{m_event.type}; }

  [[nodiscard]] auto get() const noexcept -> const T& { return m_event; }

 protected:
  T m_event{};
};

/// \name SDL event conversions
/// \{

template <typename T>
[[nodiscard]] auto AsSDLEvent(const EventBase<T>& event) -> SDL_Event;

/// \} End of SDL event conversions

}  // namespace cen

#endif  // CENTURION_EVENT_BASE_HPP_
