#pragma once
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <memory>
#include "ctn_point.h"

namespace centurion {
namespace input {

class MouseState;
using MouseState_sptr = std::shared_ptr<MouseState>;
using MouseState_uptr = std::unique_ptr<MouseState>;
using MouseState_wptr = std::weak_ptr<MouseState>;

/**
\brief The MouseState class holds information about the mouse state.
\since 1.1.0
*/
class MouseState final {
 private:
  int x;
  int y;
  Uint32 prevMask;
  Uint32 currentMask;

  inline bool IsValidMask(const Uint32 mask) const noexcept {
    return mask | COMPLETE_MASK;
  }

 public:
  /**
  \brief A bit mask for all of the possible ::SDL_BUTTON_xyz values.
  \since 1.1.0
  */
  const static Uint32 COMPLETE_MASK = SDL_BUTTON_LMASK | SDL_BUTTON_MMASK |
                                      SDL_BUTTON_RMASK | SDL_BUTTON_X1MASK |
                                      SDL_BUTTON_X2MASK;

  MouseState();

  ~MouseState();

  void Update() noexcept;

  /**
  \brief Returns true if the button associated with the mask is pressed, returns
  false otherwise.
  \param buttonMask - the mask associated with the desired button. The possible
  values are: SDL_BUTTON_LMASK, SDL_BUTTON_MMASK, SDL_BUTTON_RMASK,
  SDL_BUTTON_X1MASK and SDL_BUTTON_X2MASK;
  \since 1.1.0
  */
  bool IsButtonPressed(Uint32 buttonMask) const noexcept;

  /**
  \brief Returns true if the button associated with the mask was released,
  returns false otherwise.
  \param buttonMask - the mask associated with the desired button. The possible
  values are: SDL_BUTTON_LMASK, SDL_BUTTON_MMASK, SDL_BUTTON_RMASK,
  SDL_BUTTON_X1MASK and SDL_BUTTON_X2MASK;
  \since 1.1.0
  */
  bool WasButtonReleased(Uint32 buttonMask) const noexcept;

  /**
  \brief Returns true if the left button is being pressed, returns false
  otherwise.
  \since 1.1.0
  */
  bool IsLeftButtonPressed() const noexcept;

  /**
  \brief Returns true if the right button is being pressed, returns false
  otherwise.
  \since 1.1.0
  */
  bool IsRightButtonPressed() const noexcept;

  /**
  \brief Returns true if the left button was released, returns false otherwise.
  \since 1.1.0
  */
  bool WasLeftButtonReleased() const noexcept;

  /**
  \brief Returns true if the right button was released, returns false otherwise.
  \since 1.1.0
  */
  bool WasRightButtonReleased() const noexcept;

  /**
  \brief Returns the x-coordinate of the mouse cursor.
  \since 1.1.0
  */
  inline int GetX() const noexcept { return x; }

  /**
  \brief Returns the y-coordinate of the mouse cursor.
  \since 1.1.0
  */
  inline int GetY() const noexcept { return y; }

  /**
  \brief Returns a Point instance that holds the x- and y-coordinate of the
  mouse.
  \since 1.1.0
  */
  centurion::geo::Point GetPoint() const noexcept;

  /**
  \brief Returns a shared pointer that points to a MouseState.
  \since 1.1.0
  */
  static MouseState_sptr CreateShared();

  /**
  \brief Returns a unique pointer that points to a MouseState.
  \since 1.1.0
  */
  static MouseState_uptr CreateUnique();
};

}  // namespace input
}  // namespace centurion