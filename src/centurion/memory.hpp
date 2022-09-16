/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MEMORY_HPP_
#define CENTURION_MEMORY_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <cstddef>  // size_t
#include <memory>   // unique_ptr

namespace cen {

/// Specialized for SDL types to provide uniform memory management.
template <typename T>
struct deleter;  // Intentionally no base definition

template <>
struct deleter<SDL_Window> final
{
  void operator()(SDL_Window* window) noexcept { SDL_DestroyWindow(window); }
};

template <>
struct deleter<SDL_Renderer> final
{
  void operator()(SDL_Renderer* renderer) noexcept { SDL_DestroyRenderer(renderer); }
};

template <>
struct deleter<SDL_RWops> final
{
  void operator()(SDL_RWops* ops) noexcept { SDL_RWclose(ops); }
};

template <>
struct deleter<SDL_Surface> final
{
  void operator()(SDL_Surface* surface) noexcept { SDL_FreeSurface(surface); }
};

template <>
struct deleter<SDL_Texture> final
{
  void operator()(SDL_Texture* texture) noexcept { SDL_DestroyTexture(texture); }
};

template <>
struct deleter<SDL_PixelFormat> final
{
  void operator()(SDL_PixelFormat* format) noexcept { SDL_FreeFormat(format); }
};

template <>
struct deleter<SDL_Palette> final
{
  void operator()(SDL_Palette* palette) noexcept { SDL_FreePalette(palette); }
};

template <>
struct deleter<SDL_Cursor> final
{
  void operator()(SDL_Cursor* cursor) noexcept { SDL_FreeCursor(cursor); }
};

template <>
struct deleter<SDL_Joystick> final
{
  void operator()(SDL_Joystick* joystick) noexcept { SDL_JoystickClose(joystick); }
};

template <>
struct deleter<SDL_GameController> final
{
  void operator()(SDL_GameController* controller) noexcept
  {
    SDL_GameControllerClose(controller);
  }
};

template <>
struct deleter<SDL_Haptic> final
{
  void operator()(SDL_Haptic* haptic) noexcept { SDL_HapticClose(haptic); }
};

template <>
struct deleter<SDL_Sensor> final
{
  void operator()(SDL_Sensor* sensor) noexcept { SDL_SensorClose(sensor); }
};

template <>
struct deleter<SDL_mutex> final
{
  void operator()(SDL_mutex* mutex) noexcept { SDL_DestroyMutex(mutex); }
};

template <>
struct deleter<SDL_sem> final
{
  void operator()(SDL_sem* semaphore) noexcept { SDL_DestroySemaphore(semaphore); }
};

template <>
struct deleter<SDL_cond> final
{
  void operator()(SDL_cond* cond) noexcept { SDL_DestroyCond(cond); }
};

#ifndef CENTURION_NO_SDL_IMAGE

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

template <>
struct deleter<IMG_Animation> final
{
  void operator()(IMG_Animation* anim) noexcept { IMG_FreeAnimation(anim); }
};

#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

template <>
struct deleter<Mix_Music> final
{
  void operator()(Mix_Music* music) noexcept { Mix_FreeMusic(music); }
};

template <>
struct deleter<Mix_Chunk> final
{
  void operator()(Mix_Chunk* chunk) noexcept { Mix_FreeChunk(chunk); }
};

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

template <>
struct deleter<TTF_Font> final
{
  void operator()(TTF_Font* font) noexcept { TTF_CloseFont(font); }
};

#endif  // CENTURION_NO_SDL_TTF

template <typename T>
using managed_ptr = std::unique_ptr<T, deleter<T>>;

class simd_block final
{
 public:
  using size_type = std::size_t;

  explicit simd_block(const size_type size) noexcept : mData{SDL_SIMDAlloc(size)} {}

#if SDL_VERSION_ATLEAST(2, 0, 14)

  void reallocate(const size_type size) noexcept
  {
    /* We temporarily release the ownership of the pointer in order to avoid a double
       delete, since the reallocation will free the previously allocated memory. */
    auto* ptr = mData.release();
    mData.reset(SDL_SIMDRealloc(ptr, size));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto data() noexcept -> void* { return mData.get(); }

  [[nodiscard]] auto data() const noexcept -> const void* { return mData.get(); }

  /// Indicates whether the internal pointer is non-null.
  explicit operator bool() const noexcept { return mData != nullptr; }

 private:
  struct simd_deleter final
  {
    void operator()(void* ptr) noexcept { SDL_SIMDFree(ptr); }
  };
  std::unique_ptr<void, simd_deleter> mData;
};

}  // namespace cen

#endif  // CENTURION_MEMORY_HPP_
