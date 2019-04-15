#pragma once
#include <memory>

namespace centurion {
namespace events {

/**
\brief The Action class serves as an interface for objects that represent
various actions.
\since 1.0.0
*/
class Action {
 protected:
  Action() = default;

 public:
  virtual ~Action() = default;

  /**
  \brief Executes the action represented by this action object.
  \since 1.0.0
  */
  virtual void Execute() = 0;
};

typedef std::shared_ptr<centurion::events::Action> Action_sptr;
typedef std::unique_ptr<centurion::events::Action> Action_uptr;
typedef std::weak_ptr<centurion::events::Action> Action_wptr;

}  // namespace events
}  // namespace centurion