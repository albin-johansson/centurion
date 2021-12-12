#ifndef CENTURION_CORE_MEMORY_HPP_
#define CENTURION_CORE_MEMORY_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#include <memory>  // unique_ptr

namespace cen {

template <typename T>
struct Deleter;

template <>
struct Deleter<SDL_Window> final
{
  void operator()(SDL_Window* window) noexcept
  {
    SDL_DestroyWindow(window);
  }
};

template <>
struct Deleter<SDL_Renderer> final
{
  void operator()(SDL_Renderer* renderer) noexcept
  {
    SDL_DestroyRenderer(renderer);
  }
};

template <>
struct Deleter<SDL_RWops> final
{
  void operator()(SDL_RWops* ops) noexcept
  {
    SDL_RWclose(ops);
  }
};

#ifndef CENTURION_NO_SDL_MIXER

template <>
struct Deleter<Mix_Music> final
{
  void operator()(Mix_Music* music) noexcept
  {
    Mix_FreeMusic(music);
  }
};

template <>
struct Deleter<Mix_Chunk> final
{
  void operator()(Mix_Chunk* chunk) noexcept
  {
    Mix_FreeChunk(chunk);
  }
};

#endif  // CENTURION_NO_SDL_MIXER

template <typename T>
using Managed = std::unique_ptr<T, Deleter<T>>;

}  // namespace cen

#endif  // CENTURION_CORE_MEMORY_HPP_
