#ifndef CENTURION_FWD_HEADER
#define CENTURION_FWD_HEADER

#include "centurion_api.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/**
 * @file centurion_fwd.hpp
 *
 * @brief Provides forward declarations.
 *
 * @since 5.0.0
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

namespace centurion {

template <typename T>
struct basic_area;

template <typename Traits>
class basic_rect;

template <typename Traits>
class basic_point;

template <typename Derived>
class basic_renderer;

template <typename Traits>
class basic_window;

class renderer;

class renderer_handle;

class texture;

class surface;

class window;

class window_handle;

class font;

class font_cache;

class unicode_string;

class color;

class cursor;

class event;

class scan_code;

class key_code;

class sound_effect;

class music;

class pref_path;

class base_path;

class key_state;

class mouse_state;

namespace messagebox {

class message_box;

}

}  // namespace centurion

#endif  // CENTURION_FWD_HEADER
