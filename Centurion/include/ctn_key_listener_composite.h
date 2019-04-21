#pragma once
#include <memory>
#include <vector>
#include "ctn_key_listener.h"
#include "ctn_key_state.h"

namespace centurion {
namespace input {

class KeyListenerComposite;
typedef std::shared_ptr<KeyListenerComposite> KeyListenerComposite_sptr;
typedef std::unique_ptr<KeyListenerComposite> KeyListenerComposite_uptr;
typedef std::weak_ptr<KeyListenerComposite> KeyListenerComposite_wptr;

/**
\brief The KeyListenerComposite class holds instances of IKeyListener.
\since 1.1.0
*/
class KeyListenerComposite final : public IKeyListener {
 private:
  std::vector<IKeyListener_sptr> children;

 public:
  KeyListenerComposite();

  ~KeyListenerComposite();

  /**
  \brief Notifies all of the children of an updated key state.
  \param state - a reference to the KeyState that provides the information about
  the key state.
  \since 1.1.0
  */
  void StateUpdated(const KeyState& state) override;

  /**
  \brief Adds a IKeyListener instance to this KeyListenerComposite.
  \param child - a pointer to the IKeyListener instance that will be added.
  \since 1.1.0
  */
  void AddChild(IKeyListener_sptr child);

  /**
  \brief Removes all of this KeyListenerComposite's children.
  \since 1.1.0
  */
  void RemoveChildren() noexcept;

  /**
  \brief Returns a shared pointer that points to a KeyListenerComposite.
  \since 1.1.0
  */
  static KeyListenerComposite_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to a KeyListenerComposite.
  \since 1.1.0
  */
  static KeyListenerComposite_uptr CreateUnique();

  /**
  \brief Returns a weak pointer that points to a KeyListenerComposite.
  \since 1.1.0
  */
  static KeyListenerComposite_wptr CreateWeak();
};

}  // namespace input
}  // namespace centurion