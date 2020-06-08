/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL_hints.h>

#include <cstring>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {
namespace {

CENTURION_NODISCARD Optional<bool> to_bool(CZString name) noexcept
{
  CZString value = SDL_GetHint(name);
  if (!value) {
    return nothing;
  } else {
    return strcmp(value, "1") == 0;
  }
}

}  // namespace

namespace hint {

// TODO finish 4.1

enum RenderDriverHint {
  Direct3D,
  OpenGL,
  OpenGLES,
  OpenGLES2,
  Metal,
  Software
};

enum class HintPrio {
  Default = SDL_HINT_DEFAULT,
  Normal = SDL_HINT_NORMAL,
  Override = SDL_HINT_OVERRIDE
};

#define CENTURION_BOOL_HINT(Type, SDLHint)                                \
  class Type final {                                                      \
   public:                                                                \
    template <typename T>                                                 \
    CENTURION_NODISCARD static constexpr bool valid_arg() noexcept        \
    {                                                                     \
      return std::is_same<T, bool>::value;                                \
    }                                                                     \
                                                                          \
    CENTURION_NODISCARD static constexpr CZString name() noexcept         \
    {                                                                     \
      return SDLHint;                                                     \
    }                                                                     \
                                                                          \
    CENTURION_NODISCARD static Optional<bool> value() noexcept            \
    {                                                                     \
      return to_bool(name());                                             \
    }                                                                     \
                                                                          \
    CENTURION_NODISCARD static std::string to_string(bool value) noexcept \
    {                                                                     \
      return value ? "1" : "0";                                           \
    }                                                                     \
  };

CENTURION_BOOL_HINT(AccelerometerAsJoystick, SDL_HINT_ACCELEROMETER_AS_JOYSTICK)

CENTURION_BOOL_HINT(AppleTVControllerUIEvents,
                    SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS)

CENTURION_BOOL_HINT(AppleTVRemoteAllowRotation,
                    SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION)

CENTURION_BOOL_HINT(BMPSaveLegacyFormat, SDL_HINT_BMP_SAVE_LEGACY_FORMAT)

CENTURION_BOOL_HINT(NoSignalHandlers, SDL_HINT_NO_SIGNAL_HANDLERS)

class AndroidAPKExpansionMainFileVersion final {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, int>::value;
  }

  CENTURION_NODISCARD static constexpr CZString name() noexcept
  {
    return SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION;
  }

  CENTURION_NODISCARD static Optional<int> value() noexcept
  {
    return to_bool(name());
  }

  CENTURION_NODISCARD static std::string to_string(int value) noexcept
  {
    return std::to_string(value);
  }
};

class AndroidAPKExpansionPatchFileVersion final {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, int>::value;
  }

  CENTURION_NODISCARD static constexpr CZString name() noexcept
  {
    return SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION;
  }

  CENTURION_NODISCARD static Optional<int> value() noexcept
  {
    return to_bool(name());
  }

  CENTURION_NODISCARD static std::string to_string(int value) noexcept
  {
    return std::to_string(value);
  }
};

class RenderDriver final {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, RenderDriverHint>::value;
  }

  CENTURION_NODISCARD static constexpr CZString name() noexcept
  {
    return SDL_HINT_RENDER_DRIVER;
  }

  CENTURION_NODISCARD static Optional<RenderDriverHint> value() noexcept
  {
    CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    const std::string current{hint};
    if (current == "direct3d") {
      return Direct3D;
    } else if (current == "opengl") {
      return OpenGL;
    } else if (current == "opengles") {
      return OpenGLES;
    } else if (current == "opengles2") {
      return OpenGLES2;
    } else if (current == "metal") {
      return Metal;
    } else {
      return Software;
    }
  }

  CENTURION_NODISCARD static std::string to_string(
      RenderDriverHint value) noexcept
  {
    switch (value) {
      case Direct3D:
        return "direct3d";
      case OpenGL:
        return "opengl";
      case OpenGLES:
        return "opengles";
      case OpenGLES2:
        return "opengles2";
      case Metal:
        return "metal";
      case Software:
        return "software";
      default:
        return "";
    }
  }
};

/**
 * Sets the value of the specified hint. This method will only accept values
 * that are related to the specified hint, supplying the wrong kind of value
 * causes a compile-time error. See the related hint class for more details
 * about the associated value type.
 *
 * @tparam Hint the type of the hint that will be modified.
 * @tparam priority the priority that will be used, defaults to
 * <code>Normal</code>.
 * @tparam Value the type of the hint value.
 * @tparam X a dummy type parameter only used to check if the value type is
 * correct.
 * @param value the new value that will be set for the specified hint.
 * @return true if the hint was successfully set; false otherwise.
 * @since 0.1.0
 */
template <typename Hint,
          HintPrio priority = HintPrio::Normal,
          typename Value,
          typename X = detail::type_if<Hint::template valid_arg<Value>()>>
bool set_hint(const Value& value) noexcept
{
  return static_cast<bool>(
      SDL_SetHintWithPriority(Hint::name(),
                              Hint::to_string(value).c_str(),
                              static_cast<SDL_HintPriority>(priority)));
}

/**
 * Returns the current value of the specified hint. This method returns an
 * <code>Optional</code> of the hint value type.
 *
 * @tparam Hint the type of the Hint to obtain the value of.
 * @return the current value of the specified hint; nothing if there is no
 * value set for the hint.
 * @since 0.1.0
 */
template <typename Hint>
auto get_hint() noexcept
{
  return Hint::value();
}

}  // namespace hint
}  // namespace centurion

#undef CENTURION_BOOL_HINT
#endif  // CENTURION_HINTS_HEADER
