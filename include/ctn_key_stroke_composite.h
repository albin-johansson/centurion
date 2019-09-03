#pragma once
#include <memory>
#include <vector>
#include "ctn_event.h"
#include "ctn_key_stroke.h"

namespace centurion {
namespace events {

class KeyStrokeComposite;
using KeyStrokeComposite_sptr = std::shared_ptr<KeyStrokeComposite>;
using KeyStrokeComposite_uptr = std::unique_ptr<KeyStrokeComposite>;
using KeyStrokeComposite_wptr = std::weak_ptr<KeyStrokeComposite>;

/**
\brief The KeyStrokeComposite is a convenience class designed to hold multiple
KeyStroke instances.
\since 1.0.0
*/
class KeyStrokeComposite final {
 private:
  std::vector<IKeyStroke_sptr> keyStrokes;

 public:
  KeyStrokeComposite();

  ~KeyStrokeComposite();

  /**
  \brief Updates all held KeyStrokes with the supplied Event.
  \param event - the Event that will be dispatched to all KeyStroke instances.
  \since 1.0.0
  */
  void Update(const Event& event);

  /**
  \brief Adds a KeyStroke instance to the composite.
  \param keyStroke - the KeyStroke instance that will be added.
  \throws invalid_argument if the supplied pointer is nullptr.
  \since 1.0.0
  */
  void AddKeyStroke(IKeyStroke_sptr keyStroke);

  /**
  \brief Clears the composite of all KeyStroke instances.
  \since 1.0.0
  */
  void Clear() noexcept;

  /**
  \brief Returns a shared pointer that points to a KeyStrokeComposite instance.
  \since 1.1.0
  */
  static KeyStrokeComposite_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to a KeyStrokeComposite instance.
  \since 1.1.0
  */
  static KeyStrokeComposite_uptr CreateUnique();
};

}  // namespace events
}  // namespace centurion