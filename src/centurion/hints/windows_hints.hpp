#ifndef CENTURION_WINDOWS_HINTS_HEADER
#define CENTURION_WINDOWS_HINTS_HEADER

#include <utility>  // make_pair

#include "../detail/hints_impl.hpp"
#include "enum_hint.hpp"

namespace cen::hint::windows {

/// \addtogroup hints
/// \{

struct d3d_compiler final : enum_hint<d3d_compiler>
{
  static inline constexpr detail::string_map<value, 3> map{
      std::make_pair(value::v46, "d3dcompiler_46.dll"),
      std::make_pair(value::v43, "d3dcompiler_43.dll"),
      std::make_pair(value::none, "none")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_WIN_D3DCOMPILER;
  }
};

struct no_thread_naming final : detail::bool_hint<no_thread_naming>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING;
  }
};

struct enable_message_loop final : detail::bool_hint<enable_message_loop>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP;
  }
};

struct no_close_on_alt_f4 final : detail::bool_hint<no_close_on_alt_f4>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4;
  }
};

struct int_resource_icon final : detail::string_hint<int_resource_icon>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOWS_INTRESOURCE_ICON;
  }
};

struct int_resource_icon_small final : detail::string_hint<int_resource_icon_small>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL;
  }
};

/// \} End of group hints

}  // namespace cen::hint::windows

#endif  // CENTURION_WINDOWS_HINTS_HEADER
