#ifndef CENTURION_TEXTURE_HPP_
#define CENTURION_TEXTURE_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>      // assert
#include <cstddef>      // size_t
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "color.hpp"
#include "common.hpp"
#include "features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "surface.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class TextureAccess {
  Static = SDL_TEXTUREACCESS_STATIC,        ///< Texture changes rarely and isn't lockable.
  Streaming = SDL_TEXTUREACCESS_STREAMING,  ///< Texture changes frequently and is lockable.
  Target = SDL_TEXTUREACCESS_TARGET         ///< Texture can be used as a render target.
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

enum class ScaleMode {
  Nearest = SDL_ScaleModeNearest,
  Linear = SDL_ScaleModeLinear,
  Best = SDL_ScaleModeBest
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

template <typename T>
class BasicTexture;

using Texture = BasicTexture<detail::OwnerTag>;
using TextureHandle = BasicTexture<detail::HandleTag>;

template <typename T>
class BasicTexture final {
 public:
  explicit BasicTexture(MaybeOwner<SDL_Texture*> source) noexcept(detail::is_handle<T>)
      : mTexture{source}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mTexture) {
        throw Error{"Cannot create texture from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicTexture(Texture& owner) noexcept : mTexture{owner.get()}
  {}

#ifndef CENTURION_NO_SDL_IMAGE

  /* Creates a texture based the image at the specified path. */
  template <typename Renderer, typename TT = T, detail::EnableOwner<TT> = 0>
  BasicTexture(const Renderer& renderer, const char* path)
      : mTexture{IMG_LoadTexture(renderer.get(), path)}
  {
    if (!mTexture) {
      throw IMGError{};
    }
  }

  template <typename Renderer, typename TT = T, detail::EnableOwner<TT> = 0>
  BasicTexture(const Renderer& renderer, const std::string& path)
      : BasicTexture{renderer, path.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

  /* Creates a texture that is a copy of the supplied surface. */
  template <typename Renderer, typename TT = T, detail::EnableOwner<TT> = 0>
  BasicTexture(const Renderer& renderer, const Surface& surface)
      : mTexture{SDL_CreateTextureFromSurface(renderer.get(), surface.get())}
  {
    if (!mTexture) {
      throw SDLError{};
    }
  }

  /* Creates a texture with the specified size, format, and access. */
  template <typename Renderer, typename TT = T, detail::EnableOwner<TT> = 0>
  BasicTexture(const Renderer& renderer,
               const PixelFormat format,
               const TextureAccess access,
               const Area size)
      : mTexture{SDL_CreateTexture(renderer.get(),
                                   ToUnderlying(format),
                                   ToUnderlying(access),
                                   size.width,
                                   size.height)}
  {
    if (!mTexture) {
      throw SDLError{};
    }
  }

  void SetAlpha(const Uint8 alpha) noexcept { SDL_SetTextureAlphaMod(mTexture, alpha); }

  void SetBlendMode(const BlendMode mode) noexcept
  {
    SDL_SetTextureBlendMode(mTexture, static_cast<SDL_BlendMode>(mode));
  }

  void SetColorMod(const Color& color) noexcept
  {
    SDL_SetTextureColorMod(mTexture, color.GetRed(), color.GetGreen(), color.GetBlue());
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void SetScaleMode(const ScaleMode mode) noexcept
  {
    SDL_SetTextureScaleMode(mTexture, static_cast<SDL_ScaleMode>(mode));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto GetSize() const noexcept -> Area
  {
    int width{};
    int height{};
    SDL_QueryTexture(mTexture, nullptr, nullptr, &width, &height);
    return {width, height};
  }

  [[nodiscard]] auto GetWidth() const noexcept -> int
  {
    const auto [width, height] = GetSize();
    return width;
  }

  [[nodiscard]] auto GetHeight() const noexcept -> int
  {
    const auto [width, height] = GetSize();
    return height;
  }

  [[nodiscard]] auto GetFormat() const noexcept -> PixelFormat
  {
    Uint32 format{};
    SDL_QueryTexture(mTexture, &format, nullptr, nullptr, nullptr);
    return static_cast<PixelFormat>(format);
  }

  [[nodiscard]] auto GetAccess() const noexcept -> TextureAccess
  {
    int access{};
    SDL_QueryTexture(mTexture, nullptr, &access, nullptr, nullptr);
    return static_cast<TextureAccess>(access);
  }

  [[nodiscard]] auto IsTarget() const noexcept -> bool
  {
    return GetAccess() == TextureAccess::Target;
  }

  [[nodiscard]] auto IsStatic() const noexcept -> bool
  {
    return GetAccess() == TextureAccess::Static;
  }

  [[nodiscard]] auto IsStreaming() const noexcept -> bool
  {
    return GetAccess() == TextureAccess::Streaming;
  }

  [[nodiscard]] auto GetAlpha() const noexcept -> Uint8
  {
    Uint8 alpha{};
    SDL_GetTextureAlphaMod(mTexture, &alpha);
    return alpha;
  }

  [[nodiscard]] auto GetColorMod() const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    SDL_GetTextureColorMod(mTexture, &red, &green, &blue);
    return Color{red, green, blue};
  }

  [[nodiscard]] auto GetBlendMode() const noexcept -> BlendMode
  {
    SDL_BlendMode mode{};
    SDL_GetTextureBlendMode(mTexture, &mode);
    return static_cast<BlendMode>(mode);
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto GetScaleMode() const noexcept -> ScaleMode
  {
    SDL_ScaleMode mode{};
    SDL_GetTextureScaleMode(mTexture, &mode);
    return static_cast<ScaleMode>(mode);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /* Releases ownership of the associated SDL texture and returns a pointer to it. */
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] auto release() noexcept -> Owner<SDL_Texture*>
  {
    return mTexture.release();
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Texture* { return mTexture.get(); }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mTexture != nullptr;
  }

 private:
  detail::Pointer<T, SDL_Texture> mTexture;
};

[[nodiscard]] constexpr auto to_string(const TextureAccess access) -> std::string_view
{
  switch (access) {
    case TextureAccess::Static:
      return "Static";

    case TextureAccess::Streaming:
      return "Streaming";

    case TextureAccess::Target:
      return "Target";

    default:
      throw Error{"Did not recognize texture GetAccess!"};
  }
}

inline auto operator<<(std::ostream& stream, const TextureAccess access) -> std::ostream&
{
  return stream << to_string(access);
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

[[nodiscard]] constexpr auto to_string(const ScaleMode mode) -> std::string_view
{
  switch (mode) {
    case ScaleMode::Nearest:
      return "Nearest";

    case ScaleMode::Linear:
      return "Linear";

    case ScaleMode::Best:
      return "Best";

    default:
      throw Error{"Did not recognize scale mode!"};
  }
}

inline auto operator<<(std::ostream& stream, const ScaleMode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

template <typename T>
[[nodiscard]] auto to_string(const BasicTexture<T>& texture) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("texture{{data: {}, width: {}, height: {}}}",
                     detail::address_of(texture.get()),
                     texture.width(),
                     texture.height());
#else
  return "texture{data: " + detail::address_of(texture.get()) +
         ", GetWidth: " + std::to_string(texture.GetWidth()) +
         ", GetHeight: " + std::to_string(texture.GetHeight()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicTexture<T>& texture) -> std::ostream&
{
  return stream << to_string(texture);
}

}  // namespace cen

#endif  // CENTURION_TEXTURE_HPP_
