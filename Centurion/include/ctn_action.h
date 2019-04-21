#pragma once
#include <memory>

namespace centurion {
namespace events {

/**
\brief The IAction class serves as an interface for objects that represent
various actions.
\since 1.0.0
*/
class IAction {
 protected:
  IAction() = default;

 public:
  virtual ~IAction() = default;

  /**
  \brief Executes the action represented by this action object.
  \since 1.0.0
  */
  virtual void Execute() = 0;
};

typedef std::shared_ptr<IAction> IAction_sptr;
typedef std::unique_ptr<IAction> IAction_uptr;
typedef std::weak_ptr<IAction> IAction_wptr;

}  // namespace events
}  // namespace centurion