#pragma once
#include "ctn_event.h"

namespace centurion {
namespace events {

class IKeyStroke;
using IKeyStroke_sptr = std::shared_ptr<IKeyStroke>;
using IKeyStroke_uptr = std::unique_ptr<IKeyStroke>;
using IKeyStroke_wptr = std::weak_ptr<IKeyStroke>;

/**
\brief The IKeyStroke class is an interface for objects that represent an event
based key stroke.
\since 2.0.0
*/
class IKeyStroke {
 protected:
  IKeyStroke() = default;

 public:
  virtual ~IKeyStroke() = default;

  /**
  \brief Updates the state of this KeyStroke by comparing it to the supplied
  event.
  \param event - the event that will be checked.
  \since 2.0.0
  */
  virtual void Update(const Event& event) = 0;

  /**
  \brief Programmatically triggers the action related to this KeyStroke.
  \since 2.0.0
  */
  virtual void Trigger() = 0;

  /**
  \brief Assigns whether or not this KeyStroke may be continously triggered by
  holding down the related key. This is only applicable if this KeyStroke is
  triggered when the related key is PRESSED. By default, all KeyStrokes have
  this set to FALSE.
  \param repeatable - true if the KeyStroke should be repeatable, false
  otherwise.
  \since 2.0.0
  */
  virtual void SetRepeatable(bool repeatable) = 0;

  /**
  \brief Returns true if this KeyStroke is repeatable, returns false otherwise.
  \since 2.0.0
  */
  virtual bool IsRepeatable() const = 0;
};

}  // namespace events
}  // namespace centurion