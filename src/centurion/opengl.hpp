#ifndef CENTURION_OPENGL_HPP_
#define CENTURION_OPENGL_HPP_

#ifndef CENTURION_NO_OPENGL

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string
#include <string_view>  // string_view

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "features.hpp"
#include "math.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace cen {

/// Represents different OpenGL attributes.
enum class GLAttribute {
  RedSize = SDL_GL_RED_SIZE,
  GreenSize = SDL_GL_GREEN_SIZE,
  BlueSize = SDL_GL_BLUE_SIZE,
  AlphaSize = SDL_GL_ALPHA_SIZE,
  BufferSize = SDL_GL_BUFFER_SIZE,
  DepthSize = SDL_GL_DEPTH_SIZE,
  StencilSize = SDL_GL_STENCIL_SIZE,

  AccumRedSize = SDL_GL_ACCUM_RED_SIZE,
  AccumGreenSize = SDL_GL_ACCUM_GREEN_SIZE,
  AccumBlueSize = SDL_GL_ACCUM_BLUE_SIZE,
  AccumAlphaSize = SDL_GL_ACCUM_ALPHA_SIZE,

  Stereo = SDL_GL_STEREO,
  DoubleBuffer = SDL_GL_DOUBLEBUFFER,
  AcceleratedVisual = SDL_GL_ACCELERATED_VISUAL,
  RetainedBacking = SDL_GL_RETAINED_BACKING,
  ShareWithCurrentContext = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
  FramebufferSRGBCapable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,

  MultisampleBuffers = SDL_GL_MULTISAMPLEBUFFERS,
  MultisampleSamples = SDL_GL_MULTISAMPLESAMPLES,

  EGL = SDL_GL_CONTEXT_EGL,
  ContextFlags = SDL_GL_CONTEXT_FLAGS,
  ContextMajorVersion = SDL_GL_CONTEXT_MAJOR_VERSION,
  ContextMinorVersion = SDL_GL_CONTEXT_MINOR_VERSION,
  ContextProfileMask = SDL_GL_CONTEXT_PROFILE_MASK,
  ContextReleaseBehavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  ContextResetNotification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  ContextNoError = SDL_GL_CONTEXT_NO_ERROR
};

enum class GLSwapInterval {
  Immediate = 0,
  Synchronized = 1,
  LateImmediate = -1
};

/// Manages the initialization and de-initialization of an OpenGL library.
class GLLibrary final {
 public:
  CENTURION_DISABLE_COPY(GLLibrary)
  CENTURION_DISABLE_MOVE(GLLibrary)

  CENTURION_NODISCARD_CTOR explicit GLLibrary(const char* path = nullptr)
  {
    if (SDL_GL_LoadLibrary(path) == -1) {
      throw sdl_error{};
    }
  }

  ~GLLibrary() noexcept { SDL_GL_UnloadLibrary(); }

  [[nodiscard]] auto AddressOf(const char* function) const noexcept  // NOLINT
      -> void*
  {
    assert(function);
    return SDL_GL_GetProcAddress(function);
  }
};

template <typename T>
class BasicGLContext;

using GLContext = BasicGLContext<detail::owner_tag>;
using GLContextHandle = BasicGLContext<detail::handle_tag>;

/// Represents an OpenGL context.
template <typename T>
class BasicGLContext final {
 public:
  explicit BasicGLContext(maybe_owner<SDL_GLContext> context) noexcept(detail::is_handle<T>)
      : mContext{context}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mContext) {
        throw exception{"Can't create OpenGL context from null pointer!"};
      }
    }
  }

  template <typename U>
  explicit BasicGLContext(BasicWindow<U>& window) noexcept(detail::is_handle<T>)
      : mContext{SDL_GL_CreateContext(window.get())}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mContext) {
        throw sdl_error{};
      }
    }
  }

  template <typename U>
  auto MakeCurrent(BasicWindow<U>& window) -> result
  {
    assert(window.IsOpenGL());
    return SDL_GL_MakeCurrent(window.get(), mContext.get()) == 0;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_GLContext { return mContext.get(); }

 private:
  struct Deleter final {
    void operator()(SDL_GLContext context) noexcept { SDL_GL_DeleteContext(context); }
  };

  std::unique_ptr<void, Deleter> mContext;
};

[[nodiscard]] constexpr auto ToString(const GLAttribute attr) -> std::string_view
{
  switch (attr) {
    case GLAttribute::RedSize:
      return "RedSize";

    case GLAttribute::GreenSize:
      return "GreenSize";

    case GLAttribute::BlueSize:
      return "BlueSize";

    case GLAttribute::AlphaSize:
      return "AlphaSize";

    case GLAttribute::BufferSize:
      return "BufferSize";

    case GLAttribute::DepthSize:
      return "DepthSize";

    case GLAttribute::StencilSize:
      return "StencilSize";

    case GLAttribute::AccumRedSize:
      return "AccumRedSize";

    case GLAttribute::AccumGreenSize:
      return "AccumGreenSize";

    case GLAttribute::AccumBlueSize:
      return "AccumBlueSize";

    case GLAttribute::AccumAlphaSize:
      return "AccumAlphaSize";

    case GLAttribute::Stereo:
      return "Stereo";

    case GLAttribute::EGL:
      return "EGL";

    case GLAttribute::ContextFlags:
      return "ContextFlags";

    case GLAttribute::DoubleBuffer:
      return "DoubleBuffer";

    case GLAttribute::AcceleratedVisual:
      return "AcceleratedVisual";

    case GLAttribute::RetainedBacking:
      return "RetainedBacking";

    case GLAttribute::ShareWithCurrentContext:
      return "ShareWithCurrentContext";

    case GLAttribute::FramebufferSRGBCapable:
      return "FramebufferSRGBCapable";

    case GLAttribute::MultisampleBuffers:
      return "MultisampleBuffers";

    case GLAttribute::MultisampleSamples:
      return "MultisampleSamples";

    case GLAttribute::ContextMajorVersion:
      return "ContextMajorVersion";

    case GLAttribute::ContextMinorVersion:
      return "ContextMinorVersion";

    case GLAttribute::ContextProfileMask:
      return "ContextProfileMask";

    case GLAttribute::ContextReleaseBehavior:
      return "ContextReleaseBehavior";

    case GLAttribute::ContextResetNotification:
      return "ContextResetNotification";

    case GLAttribute::ContextNoError:
      return "ContextNoError";

    default:
      throw exception{"Did not recognize OpenGL attribute!"};
  }
}

[[nodiscard]] constexpr auto ToString(const GLSwapInterval interval) -> std::string_view
{
  switch (interval) {
    case GLSwapInterval::Immediate:
      return "Immediate";

    case GLSwapInterval::Synchronized:
      return "Synchronized";

    case GLSwapInterval::LateImmediate:
      return "LateImmediate";

    default:
      throw exception{"Did not recognize swap interval!"};
  }
}

inline auto operator<<(std::ostream& stream, const GLAttribute attr) -> std::ostream&
{
  return stream << ToString(attr);
}

inline auto operator<<(std::ostream& stream, const GLSwapInterval interval) -> std::ostream&
{
  return stream << ToString(interval);
}

namespace gl {

/// \name OpenGL functions
/// \{

template <typename T>
void Swap(BasicWindow<T>& window) noexcept
{
  assert(window.IsOpenGL());
  SDL_GL_SwapWindow(window.get());
}

template <typename T>
[[nodiscard]] auto GetDrawableSize(const BasicWindow<T>& window) noexcept -> iarea
{
  assert(window.IsOpenGL());

  int width{};
  int height{};
  SDL_GL_GetDrawableSize(window.get(), &width, &height);

  return {width, height};
}

inline void ResetAttributes() noexcept
{
  SDL_GL_ResetAttributes();
}

inline auto Set(const GLAttribute attr, const int value) noexcept -> result
{
  return SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) == 0;
}

inline auto Get(const GLAttribute attr) noexcept -> std::optional<int>
{
  int value{};
  if (SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value) == 0) {
    return value;
  }
  else {
    return std::nullopt;
  }
}

inline auto SetSwapInterval(const GLSwapInterval interval) noexcept -> result
{
  return SDL_GL_SetSwapInterval(to_underlying(interval)) == 0;
}

[[nodiscard]] inline auto GetSwapInterval() noexcept -> GLSwapInterval
{
  return GLSwapInterval{SDL_GL_GetSwapInterval()};
}

[[nodiscard]] inline auto GetWindow() noexcept -> WindowHandle
{
  return WindowHandle{SDL_GL_GetCurrentWindow()};
}

[[nodiscard]] inline auto GetContext() noexcept -> GLContextHandle
{
  return GLContextHandle{SDL_GL_GetCurrentContext()};
}

[[nodiscard]] inline auto IsExtensionSupported(const char* extension) noexcept -> bool
{
  assert(extension);
  return SDL_GL_ExtensionSupported(extension) == SDL_TRUE;
}

[[nodiscard]] inline auto IsExtensionSupported(const std::string& extension) noexcept -> bool
{
  return IsExtensionSupported(extension.c_str());
}

template <typename T>
auto Bind(basic_texture<T>& texture) noexcept -> std::optional<farea>
{
  float width{};
  float height{};
  if (SDL_GL_BindTexture(texture.get(), &width, &height) == 0) {
    return farea{width, height};
  }
  else {
    return std::nullopt;
  }
}

template <typename T>
auto Unbind(basic_texture<T>& texture) noexcept -> result
{
  return SDL_GL_UnbindTexture(texture.get()) == 0;
}

/// \} End of OpenGL functions

}  // namespace gl
}  // namespace cen

#endif  // CENTURION_NO_OPENGL
#endif  // CENTURION_OPENGL_HPP_
