#pragma once
#include <SDL_events.h>
#include <memory>
#include "keyboard_event.h"
#include "mouse_event.h"

namespace centurion {
namespace events {

/**
\brief The Event class represents an event which holds various information about
components like the mouse and keyboard.
*/
class Event {
 private:
  SDL_Event event;
  centurion::events::MouseEvent mouseEvent;
  centurion::events::KeyboardEvent keyEvent;

 public:
  /**
  \param event - The SDL_Event that will serve as the internal representation of
  the Event.
  */
  explicit Event(SDL_Event event);

  ~Event();

  /**
  \brief Indicates whether the type of this Event is primarily a key based
  event. Returns true if this is the case, false otherwise.
  */
  bool IsKeyEvent() const;

  /**
  \brief Indicates whether the type of this Event is primarily a mouse based
  event. Returns true if this is the case, false otherwise.
  */
  bool IsMouseEvent() const;

  /**
  \brief Returns a MouseEvent that holds information about the mouse.
  */
  inline centurion::events::MouseEvent GetMouseInfo() const {
    return mouseEvent;
  }

  /**
  \brief Returns a KeyboardEvent that holds information about the mouse.
  */
  inline centurion::events::KeyboardEvent GetKeyboardInfo() const {
    return keyEvent;
  }

  /**
  \brief Returns a copy of the internal representation of this Event.
  */
  inline SDL_Event GetSDLVersion() const { return event; }
};

typedef std::shared_ptr<centurion::events::Event> Event_sptr;
typedef std::unique_ptr<centurion::events::Event> Event_uptr;
typedef std::weak_ptr<centurion::events::Event> Event_wptr;

}  // namespace events
}  // namespace centurion