#pragma once
#include <SDL_mouse.h>
#include <memory>
#include "point.h"

namespace centurion {
namespace input {

/**
\brief The MouseState class holds information about the mouse state.
\since 1.1.0
*/
class MouseState {
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

  centurion::geo::Point GetPoint() const noexcept;
};

typedef std::shared_ptr<centurion::input::MouseState> MouseState_sptr;
typedef std::unique_ptr<centurion::input::MouseState> MouseState_uptr;
typedef std::weak_ptr<centurion::input::MouseState> MouseState_wptr;

}  // namespace input
}  // namespace centurion