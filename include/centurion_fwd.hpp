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
 * @todo Remove this header
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

namespace cen {

template <typename T>
struct basic_area;

template <typename T>
class basic_rect;

template <typename T>
class basic_point;

template <typename T>
class basic_renderer;

template <typename T>
class basic_window;

template <typename T>
class basic_joystick;

template <typename T>
class basic_texture;

template <typename T>
class basic_surface;

class thread;

class mutex;

class scoped_lock;

class texture;

class texture_handle;

class font;

class font_cache;

class unicode_string;

class color;

class event;

class scan_code;

class key_code;

class sound_effect;

class music;

class pref_path;

class base_path;

class key_state;

class mouse_state;

class message_box;

}  // namespace cen

#endif  // CENTURION_FWD_HEADER
