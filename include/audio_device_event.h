#ifndef CENTURION_AUDIO_DEVICE_EVENT_HEADER
#define CENTURION_AUDIO_DEVICE_EVENT_HEADER

#include <SDL_events.h>

#include "base_event.h"
#include "centurion_api.h"

namespace centurion {
namespace event {

class AudioDeviceEvent : public BaseEvent<SDL_AudioDeviceEvent> {
 public:

};

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_AUDIO_DEVICE_EVENT_HEADER
