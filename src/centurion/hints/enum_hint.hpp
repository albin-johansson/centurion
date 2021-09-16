#ifndef CENTURION_ENUM_HINT_HEADER
#define CENTURION_ENUM_HINT_HEADER

#include <SDL.h>

#include <optional>     // optional
#include <string>       // string
#include <type_traits>  // is_same_v

#include "../core/str.hpp"

namespace cen::hint {

/// \addtogroup hints
/// \{

struct render_driver;
struct audio_resampling_mode;
struct scale_quality;
struct framebuffer_acceleration;
struct audio_category;
struct wave_riff_chunk_size;
struct wave_truncation;
struct wave_fact_chunk;
struct logical_size_mode;

namespace qtwayland {
struct content_orientation;
}

namespace windows {
struct d3d_compiler;
}

/// \} End of group hints

/// \cond FALSE

template <class Hint>
struct enum_hint_traits;

template <>
struct enum_hint_traits<render_driver> final
{
  enum class value
  {
    direct3d,
    opengl,
    opengles,
    opengles2,
    metal,
    software
  };
};

template <>
struct enum_hint_traits<audio_resampling_mode> final
{
  enum class value
  {
    normal = 0,
    fast = 1,
    medium = 2,
    best = 3
  };
};

template <>
struct enum_hint_traits<scale_quality> final
{
  enum class value
  {
    nearest = 0,
    linear = 1,
    best = 2
  };
};

template <>
struct enum_hint_traits<framebuffer_acceleration> final
{
  enum class value
  {
    off,
    on,
    direct3d,
    opengl,
    opengles,
    opengles2,
    metal,
    software
  };
};

template <>
struct enum_hint_traits<audio_category> final
{
  enum class value
  {
    ambient,
    playback
  };
};

template <>
struct enum_hint_traits<wave_riff_chunk_size> final
{
  enum class value
  {
    force,
    ignore_zero,
    ignore,
    maximum
  };
};

template <>
struct enum_hint_traits<wave_truncation> final
{
  enum class value
  {
    very_strict,
    strict,
    drop_frame,
    drop_block
  };
};

template <>
struct enum_hint_traits<wave_fact_chunk> final
{
  enum class value
  {
    truncate,
    strict,
    ignore_zero,
    ignore
  };
};

template <>
struct enum_hint_traits<logical_size_mode> final
{
  enum class value
  {
    letterbox,
    overscan
  };
};

template <>
struct enum_hint_traits<qtwayland::content_orientation> final
{
  enum class value
  {
    primary,
    portrait,
    landscape,
    inverted_portrait,
    inverted_landscape
  };
};

template <>
struct enum_hint_traits<windows::d3d_compiler> final
{
  enum class value
  {
    v46,
    v43,
    none
  };
};

/// \endcond

/// \addtogroup hints
/// \{

template <class Derived>
class enum_hint
{
 public:
  using value = typename enum_hint_traits<Derived>::value;
  using value_type = value;

  template <typename T>
  [[nodiscard]] constexpr static auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, value>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<value_type>
  {
    if (const str hint = SDL_GetHint(Derived::name())) {
      return Derived::map.key_from(hint);
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] static auto from_string(const str value) -> value_type
  {
    return Derived::map.key_from(value);
  }

  [[nodiscard]] static auto to_string(const value_type value) -> std::string
  {
    return Derived::map.find(value);
  }
};

/// \} End of group hints

}  // namespace cen::hint

#endif  // CENTURION_ENUM_HINT_HEADER