#ifndef CENTURION_CORE_MEMORY_HPP_
#define CENTURION_CORE_MEMORY_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

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

template <>
struct Deleter<SDL_Surface> final
{
  void operator()(SDL_Surface* surface) noexcept
  {
    SDL_FreeSurface(surface);
  }
};

template <>
struct Deleter<SDL_Texture> final
{
  void operator()(SDL_Texture* texture) noexcept
  {
    SDL_DestroyTexture(texture);
  }
};

template <>
struct Deleter<SDL_PixelFormat> final
{
  void operator()(SDL_PixelFormat* format) noexcept
  {
    SDL_FreeFormat(format);
  }
};

template <>
struct Deleter<SDL_Palette> final
{
  void operator()(SDL_Palette* palette) noexcept
  {
    SDL_FreePalette(palette);
  }
};

template <>
struct Deleter<SDL_Cursor> final
{
  void operator()(SDL_Cursor* cursor) noexcept
  {
    SDL_FreeCursor(cursor);
  }
};

template <>
struct Deleter<SDL_Joystick> final
{
  void operator()(SDL_Joystick* joystick) noexcept
  {
    SDL_JoystickClose(joystick);
  }
};

template <>
struct Deleter<SDL_GameController> final
{
  void operator()(SDL_GameController* controller) noexcept
  {
    SDL_GameControllerClose(controller);
  }
};

template <>
struct Deleter<SDL_Haptic> final
{
  void operator()(SDL_Haptic* haptic) noexcept
  {
    SDL_HapticClose(haptic);
  }
};

template <>
struct Deleter<SDL_Sensor> final
{
  void operator()(SDL_Sensor* sensor) noexcept
  {
    SDL_SensorClose(sensor);
  }
};

template <>
struct Deleter<SDL_mutex> final
{
  void operator()(SDL_mutex* mutex) noexcept
  {
    SDL_DestroyMutex(mutex);
  }
};

template <>
struct Deleter<SDL_sem> final
{
  void operator()(SDL_sem* semaphore) noexcept
  {
    SDL_DestroySemaphore(semaphore);
  }
};

template <>
struct Deleter<SDL_cond> final
{
  void operator()(SDL_cond* cond) noexcept
  {
    SDL_DestroyCond(cond);
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

#ifndef CENTURION_NO_SDL_TTF

template <>
struct Deleter<TTF_Font> final
{
  void operator()(TTF_Font* font) noexcept
  {
    TTF_CloseFont(font);
  }
};

#endif  // CENTURION_NO_SDL_TTF

template <typename T>
using Managed = std::unique_ptr<T, Deleter<T>>;

}  // namespace cen

#endif  // CENTURION_CORE_MEMORY_HPP_