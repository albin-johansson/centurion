/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_VIDEO_OPENGL_HPP_
#define CENTURION_VIDEO_OPENGL_HPP_

#include <memory>  // unique_ptr

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <centurion/common/errors.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/result.hpp>

namespace cen {

class OpenGLContext final {
 public:
  struct ContextDeleter final {
    void operator()(SDL_GLContext context) noexcept { SDL_GL_DeleteContext(context); }
  };

  CEN_CANNOT_COPY(OpenGLContext);

  [[nodiscard]] explicit OpenGLContext(SDL_Window* window)
      : mWindow {window},
        mContext {SDL_GL_CreateContext(mWindow)}
  {
    if (!mContext) {
      throw SDLError {};
    }
  }

  [[nodiscard]] static auto current() noexcept -> SDL_GLContext
  {
    return SDL_GL_GetCurrentContext();
  }

  auto make_current() noexcept -> Result
  {
    return SDL_GL_MakeCurrent(mWindow, get()) == 0;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_GLContext { return mContext.get(); }

  [[nodiscard]] auto get_window() const noexcept -> SDL_Window* { return mWindow; }

 private:
  SDL_Window* mWindow {};
  std::unique_ptr<void, ContextDeleter> mContext;
};

class OpenGLLibrary final {
 public:
  CEN_CANNOT_COPY(OpenGLLibrary);
  CEN_CANNOT_MOVE(OpenGLLibrary);

  [[nodiscard]] explicit OpenGLLibrary(const char* library_path = nullptr)
  {
    if (SDL_GL_LoadLibrary(library_path) != 0) {
      throw SDLError {};
    }
  }

  ~OpenGLLibrary() noexcept { SDL_GL_UnloadLibrary(); }
};

}  // namespace cen

#endif  // CENTURION_VIDEO_OPENGL_HPP_
