#ifndef CENTURION_RENDER_HPP_
#define CENTURION_RENDER_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, string_literals

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core/features.hpp"
#include "math.hpp"
#include "video.hpp"
#include "video/renderer.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

class RendererInfo final {
  template <typename T>
  friend auto GetInfo(const BasicRenderer<T>& renderer) noexcept
      -> std::optional<RendererInfo>;

 public:
  [[nodiscard]] auto GetSupportedFlags() const noexcept -> Uint32 { return mInfo.flags; }

  [[nodiscard]] auto HasVSync() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_PRESENTVSYNC;
  }

  [[nodiscard]] auto HasTargetTextures() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_TARGETTEXTURE;
  }

  [[nodiscard]] auto HasHardwareAcceleration() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_ACCELERATED;
  }

  [[nodiscard]] auto HasSoftwareRenderer() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_SOFTWARE;
  }

  [[nodiscard]] auto GetPixelFormats() const noexcept -> Uint32
  {
    return mInfo.num_texture_formats;
  }

  [[nodiscard]] auto GetFormat(const std::size_t index) const noexcept -> pixel_format
  {
    assert(index < GetPixelFormats());
    return static_cast<pixel_format>(mInfo.texture_formats[index]);
  }

  [[nodiscard]] auto GetMaxTextureSize() const noexcept -> Area
  {
    return {mInfo.max_texture_width, mInfo.max_texture_height};
  }

  [[nodiscard]] auto GetMaxTextureWidth() const noexcept -> int
  {
    return mInfo.max_texture_width;
  }

  [[nodiscard]] auto GetMaxTextureHeight() const noexcept -> int
  {
    return mInfo.max_texture_height;
  }

  [[nodiscard]] auto GetName() const noexcept -> const char* { return mInfo.name; }

 private:
  SDL_RendererInfo mInfo;

  explicit RendererInfo(const SDL_RendererInfo info) noexcept : mInfo{info} {}
};

template <typename T>
[[nodiscard]] auto GetInfo(const BasicRenderer<T>& renderer) noexcept
    -> std::optional<RendererInfo>
{
  SDL_RendererInfo info;
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return RendererInfo{info};
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto to_string(const RendererInfo& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("RendererInfo(name: {})", str_or_na(info.GetName()));
#else
  using namespace std::string_literals;
  return "RendererInfo(name: "s + str_or_na(info.GetName()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const RendererInfo& info) -> std::ostream&
{
  return stream << to_string(info);
}

}  // namespace cen

#endif  // CENTURION_RENDER_HPP_
