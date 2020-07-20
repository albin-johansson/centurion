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
 * @todo Provide more forward declarations.
 *
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 * @since 5.0.0
 */

namespace centurion {

template <typename T>
struct basic_area;

template <typename T>
class basic_rect;

template <typename T>
class basic_point;

class renderer;

class renderer_view;

class texture;

class surface;

class window;

class window_view;

class font;

class color;

class cursor;

class event;

class scan_code;

class key_code;

class sound_effect;

class music;

class pref_path;

class base_path;

namespace input {

class key_state;

class mouse_state;

}  // namespace input

namespace messagebox {

class message_box;

}

namespace experimental {

class font_cache;

class unicode_string;

}  // namespace experimental

}  // namespace centurion

#endif  // CENTURION_FWD_HEADER
