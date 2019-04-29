#pragma once
#include <memory>
#include "ctn_key_state.h"

namespace centurion {
namespace input {

/**
\brief The IKeyListener class is an interface for objects that react to key
input.
\since 1.1.0
*/
class IKeyListener {
 protected:
  IKeyListener() = default;

 public:
  virtual ~IKeyListener() = default;

  /**
  \brief Invoked when the key state has been updated.
  \param state - a reference to the KeyState instance holding information about
  the key state.
  \since 1.1.0
  */
  virtual void StateUpdated(const KeyState& state) = 0;
};

using IKeyListener_sptr = std::shared_ptr<IKeyListener>;
using IKeyListener_uptr = std::unique_ptr<IKeyListener>;
using IKeyListener_wptr = std::weak_ptr<IKeyListener>;

}  // namespace input
}  // namespace centurion