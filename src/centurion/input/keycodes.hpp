#ifndef CENTURION_KEYCODES_HEADER
#define CENTURION_KEYCODES_HEADER

#include <SDL.h>

#include "key_code.hpp"

namespace cen {

/**
 * \namespace cen::keycodes
 *
 * \brief Provides a collection of `key_code` constants.
 *
 * \details Far from all key codes are provided. Instead, some of the most commonly used
 * key codes are available.
 *
 * \since 5.0.0
 */
namespace keycodes {

/// \addtogroup input
/// \{

/// \name Key code constants
/// \{

/**
 * \brief Represents an unknown key.
 *
 * \since 5.0.0
 */
inline constexpr key_code unknown;

/**
 * \brief Represents the key with the label "A".
 *
 * \since 5.0.0
 */
inline constexpr key_code a{SDLK_a};

/**
 * \brief Represents the key with the label "B".
 *
 * \since 5.0.0
 */
inline constexpr key_code b{SDLK_b};

/**
 * \brief Represents the key with the label "C".
 *
 * \since 5.0.0
 */
inline constexpr key_code c{SDLK_c};

/**
 * \brief Represents the key with the label "D".
 *
 * \since 5.0.0
 */
inline constexpr key_code d{SDLK_d};

/**
 * \brief Represents the key with the label "E".
 *
 * \since 5.0.0
 */
inline constexpr key_code e{SDLK_e};

/**
 * \brief Represents the key with the label "F".
 *
 * \since 5.0.0
 */
inline constexpr key_code f{SDLK_f};

/**
 * \brief Represents the key with the label "G".
 *
 * \since 5.0.0
 */
inline constexpr key_code g{SDLK_g};

/**
 * \brief Represents the key with the label "H".
 *
 * \since 5.0.0
 */
inline constexpr key_code h{SDLK_h};

/**
 * \brief Represents the key with the label "I".
 *
 * \since 5.0.0
 */
inline constexpr key_code i{SDLK_i};

/**
 * \brief Represents the key with the label "J".
 *
 * \since 5.0.0
 */
inline constexpr key_code j{SDLK_j};

/**
 * \brief Represents the key with the label "K".
 *
 * \since 5.0.0
 */
inline constexpr key_code k{SDLK_k};

/**
 * \brief Represents the key with the label "L".
 *
 * \since 5.0.0
 */
inline constexpr key_code l{SDLK_l};

/**
 * \brief Represents the key with the label "M".
 *
 * \since 5.0.0
 */
inline constexpr key_code m{SDLK_m};

/**
 * \brief Represents the key with the label "N".
 *
 * \since 5.0.0
 */
inline constexpr key_code n{SDLK_n};

/**
 * \brief Represents the key with the label "O".
 *
 * \since 5.0.0
 */
inline constexpr key_code o{SDLK_o};

/**
 * \brief Represents the key with the label "P".
 *
 * \since 5.0.0
 */
inline constexpr key_code p{SDLK_p};

/**
 * \brief Represents the key with the label "Q".
 *
 * \since 5.0.0
 */
inline constexpr key_code q{SDLK_q};

/**
 * \brief Represents the key with the label "R".
 *
 * \since 5.0.0
 */
inline constexpr key_code r{SDLK_r};

/**
 * \brief Represents the key with the label "S".
 *
 * \since 5.0.0
 */
inline constexpr key_code s{SDLK_s};

/**
 * \brief Represents the key with the label "T".
 *
 * \since 5.0.0
 */
inline constexpr key_code t{SDLK_t};

/**
 * \brief Represents the key with the label "U".
 *
 * \since 5.0.0
 */
inline constexpr key_code u{SDLK_u};

/**
 * \brief Represents the key with the label "V".
 *
 * \since 5.0.0
 */
inline constexpr key_code v{SDLK_v};

/**
 * \brief Represents the key with the label "W".
 *
 * \since 5.0.0
 */
inline constexpr key_code w{SDLK_w};

/**
 * \brief Represents the key with the label "X".
 *
 * \since 5.0.0
 */
inline constexpr key_code x{SDLK_x};

/**
 * \brief Represents the key with the label "Y".
 *
 * \since 5.0.0
 */
inline constexpr key_code y{SDLK_y};

/**
 * \brief Represents the key with the label "Z".
 *
 * \since 5.0.0
 */
inline constexpr key_code z{SDLK_z};

/**
 * \brief Represents the key with the label "1".
 *
 * \note This is not for a potential "1" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code one{SDLK_1};

/**
 * \brief Represents the key with the label "2".
 *
 * \note This is not for a potential "2" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code two{SDLK_2};

/**
 * \brief Represents the key with the label "3".
 *
 * \note This is not for a potential "3" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code three{SDLK_3};

/**
 * \brief Represents the key with the label "4".
 *
 * \note This is not for a potential "4" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code four{SDLK_4};

/**
 * \brief Represents the key with the label "5".
 *
 * \note This is not for a potential "5" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code five{SDLK_5};

/**
 * \brief Represents the key with the label "6".
 *
 * \note This is not for a potential "6" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code six{SDLK_6};

/**
 * \brief Represents the key with the label "7".
 *
 * \note This is not for a potential "7" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code seven{SDLK_7};

/**
 * \brief Represents the key with the label "8".
 *
 * \note This is not for a potential "8" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code eight{SDLK_8};

/**
 * \brief Represents the key with the label "9".
 *
 * \note This is not for a potential "9" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code nine{SDLK_9};

/**
 * \brief Represents the key with the label "0".
 *
 * \note This is not for a potential "0" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr key_code zero{SDLK_0};

/**
 * \brief Represents the function key "F1".
 *
 * \since 5.0.0
 */
inline constexpr key_code f1{SDLK_F1};

/**
 * \brief Represents the function key "F2".
 *
 * \since 5.0.0
 */
inline constexpr key_code f2{SDLK_F2};

/**
 * \brief Represents the function key "F3".
 *
 * \since 5.0.0
 */
inline constexpr key_code f3{SDLK_F3};

/**
 * \brief Represents the function key "F4".
 *
 * \since 5.0.0
 */
inline constexpr key_code f4{SDLK_F4};

/**
 * \brief Represents the function key "F5".
 *
 * \since 5.0.0
 */
inline constexpr key_code f5{SDLK_F5};

/**
 * \brief Represents the function key "F6".
 *
 * \since 5.0.0
 */
inline constexpr key_code f6{SDLK_F6};

/**
 * \brief Represents the function key "F7".
 *
 * \since 5.0.0
 */
inline constexpr key_code f7{SDLK_F7};

/**
 * \brief Represents the function key "F8".
 *
 * \since 5.0.0
 */
inline constexpr key_code f8{SDLK_F8};

/**
 * \brief Represents the function key "F9".
 *
 * \since 5.0.0
 */
inline constexpr key_code f9{SDLK_F9};

/**
 * \brief Represents the function key "F10".
 *
 * \since 5.0.0
 */
inline constexpr key_code f10{SDLK_F10};

/**
 * \brief Represents the function key "F11".
 *
 * \since 5.0.0
 */
inline constexpr key_code f11{SDLK_F11};

/**
 * \brief Represents the function key "F12".
 *
 * \since 5.0.0
 */
inline constexpr key_code f12{SDLK_F12};

/**
 * \brief Represents the left arrow key.
 *
 * \since 5.0.0
 */
inline constexpr key_code left{SDLK_LEFT};

/**
 * \brief Represents the right arrow key.
 *
 * \since 5.0.0
 */
inline constexpr key_code right{SDLK_RIGHT};

/**
 * \brief Represents the up arrow key.
 *
 * \since 5.0.0
 */
inline constexpr key_code up{SDLK_UP};

/**
 * \brief Represents the down arrow key.
 *
 * \since 5.0.0
 */
inline constexpr key_code down{SDLK_DOWN};

/**
 * \brief Represents the "Space" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code space{SDLK_SPACE};

/**
 * \brief Represents the "Enter" key.
 *
 * \note This key is also referred to as the "Return" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code enter{SDLK_RETURN};

/**
 * \brief Represents the "Escape" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code escape{SDLK_ESCAPE};

/**
 * \brief Represents the "Backspace" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code backspace{SDLK_BACKSPACE};

/**
 * \brief Represents the "Tab" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code tab{SDLK_TAB};

/**
 * \brief Represents the "Caps Lock" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code caps_lock{SDLK_CAPSLOCK};

/**
 * \brief Represents the left "Shift" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code left_shift{SDLK_LSHIFT};

/**
 * \brief Represents the right "Shift" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code right_shift{SDLK_RSHIFT};

/**
 * \brief Represents the left "CTRL" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code left_ctrl{SDLK_LCTRL};

/**
 * \brief Represents the right "CTRL" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code right_ctrl{SDLK_RCTRL};

/**
 * \brief Represents the left "Alt" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code left_alt{SDLK_LALT};

/**
 * \brief Represents the right "Alt" key.
 *
 * \since 5.0.0
 */
inline constexpr key_code right_alt{SDLK_RALT};

/**
 * \brief Represents the left "GUI" key.
 *
 * \details On Windows, this is the "Windows key"; for macs it's the "CMD" key, etc.
 *
 * \since 5.0.0
 */
inline constexpr key_code left_gui{SDLK_LGUI};

/**
 * \brief Represents the right "GUI" key.
 *
 * \details On Windows, this is the "Windows" key; for macs it's the "CMD" key, etc.
 *
 * \since 5.0.0
 */
inline constexpr key_code right_gui{SDLK_RGUI};

/// \} End of key code constants

/// \} End of group input

}  // namespace keycodes

}  // namespace cen

#endif  // CENTURION_KEYCODES_HEADER
