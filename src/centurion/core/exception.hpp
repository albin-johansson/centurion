#ifndef CENTURION_CORE_EXCEPTION_HPP_
#define CENTURION_CORE_EXCEPTION_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <exception>  // exception

#include "../common.hpp"

namespace cen {

class Error : public std::exception {
 public:
  Error() noexcept = default;

  explicit Error(const char* what) noexcept : mWhat{what ? what : "?"} {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat; }

 private:
  const char* mWhat{"?"};
};

class SDLError final : public Error {
 public:
  SDLError() noexcept : Error{SDL_GetError()} {}

  explicit SDLError(const char* what) noexcept : Error{what} {}
};

#ifndef CENTURION_NO_SDL_IMAGE

class IMGError final : public Error {
 public:
  IMGError() noexcept : Error{IMG_GetError()} {}

  explicit IMGError(const char* what) noexcept : Error{what} {}
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF

class TTFError final : public Error {
 public:
  TTFError() noexcept : Error{TTF_GetError()} {}

  explicit TTFError(const char* what) noexcept : Error{what} {}
};

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

class MixError final : public Error {
 public:
  MixError() noexcept : Error{Mix_GetError()} {}

  explicit MixError(const char* what) noexcept : Error{what} {}
};

#endif  // CENTURION_NO_SDL_MIXER

}  // namespace cen

#endif  // CENTURION_CORE_EXCEPTION_HPP_
