#pragma once
#include <SDL_scancode.h>
#include <memory>
#include <vector>

namespace centurion {
namespace input {

/**
\brief The KeyState class provides information about the keyboard state.
\since 1.1.0
*/
class KeyState final {
 private:
  int nKeys;
  const Uint8* stateArr;
  std::vector<Uint8> prevStates;

  void CopyStates() noexcept;

 public:
  KeyState();

  ~KeyState();

  /**
  \brief Refreshes the information about the key state. This method does NOT
  call SDL_PumpEvents().
  \since 1.1.0
  */
  void Update() noexcept;

  /**
  \brief Returns true if the key associated with the supplied SDL_Scancode is
  being pressed.
  \param code - the SDL_Scancode that corresponds to the desired key to check.
  \since 1.1.0
  */
  bool IsPressed(const SDL_Scancode code) const;

  /**
  \brief Returns true if the key associated with the supplied SDL_Scancode is
  currently held down.
  \param code - the SDL_Scancode that corresponds to the
  desired key to check.
  \since 1.1.0
  */
  bool IsHeldDown(const SDL_Scancode code) const;

  /**
  \brief Returns true if the key associated with the supplied SDL_Scancode was
  released.
  \param code - the SDL_Scancode that corresponds to the desired key to check.
  \since 1.1.0
  */
  bool WasReleased(const SDL_Scancode code) const;

  /**
  \brief Returns true if the key associated with the supplied SDL_Scancode is
  being pressed and triggered for the first time, since it was pressed. Returns
  false otherwise.
  \param code - the SDL_Scancode that corresponds to the desired key to check.
  \since 1.1.0
  */
  bool IsFirstTrigger(const SDL_Scancode code) const;

  /**
  \brief Returns the number of possible keys.
  \since 1.1.0
  */
  inline int GetNumberOfKeys() const noexcept { return nKeys; }
};

typedef std::shared_ptr<centurion::input::KeyState> KeyState_sptr;
typedef std::unique_ptr<centurion::input::KeyState> KeyState_uptr;
typedef std::weak_ptr<centurion::input::KeyState> KeyState_wptr;

}  // namespace input
}  // namespace centurion