#pragma once
#include <memory>
#include <vector>
#include "event.h"
#include "key_stroke.h"

namespace centurion {
namespace events {

/**
\brief The KeyStrokeComposite is a convenience class designed to hold multiple
KeyStroke instances.
\since 1.0.0
*/
class KeyStrokeComposite final {  // FIXME should extend KeyStroke interface
 private:
  std::vector<std::shared_ptr<centurion::events::KeyStroke>> keyStrokes;

 public:
  KeyStrokeComposite();

  ~KeyStrokeComposite();

  /**
  \brief Creates and returns a heap allocated KeyStrokeComposite instance.
  */
  static std::shared_ptr<centurion::events::KeyStrokeComposite> Create();

  /**
  \brief Updates all held KeyStrokes with the supplied Event.
  \param event - the Event that will be dispatched to all KeyStroke instances.
  */
  void Update(const Event& event);

  /**
  \brief Adds a KeyStroke instance to the composite.
  \param keyStroke - the KeyStroke instance that will be added.
  */
  void AddKeyStroke(std::shared_ptr<centurion::events::KeyStroke> keyStroke);

  /**
  \brief Clears the composite of all KeyStroke instances.
  */
  void Clear();
};

}  // namespace events
}  // namespace centurion