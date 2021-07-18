#ifndef CENTURION_SCANCODES_HEADER
#define CENTURION_SCANCODES_HEADER

#include <SDL.h>

#include "scan_code.hpp"

namespace cen {

/**
 * \namespace cen::scancodes
 *
 * \brief Provides a collection of `scan_code` constants.
 *
 * \ingroup input
 *
 * \details Far from all scan codes are provided. Instead, the most commonly used scan
 * codes are available.
 */
namespace scancodes {

/// \addtogroup input
/// \{

/// \name Scan code constants
/// \{

/**
 * \brief Represents an unknown key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code unknown;

/**
 * \brief Represents the key "A".
 *
 * \since 5.0.0
 */
inline constexpr scan_code a{SDL_SCANCODE_A};

/**
 * \brief Represents the key "B".
 *
 * \since 5.0.0
 */
inline constexpr scan_code b{SDL_SCANCODE_B};

/**
 * \brief Represents the key "C".
 *
 * \since 5.0.0
 */
inline constexpr scan_code c{SDL_SCANCODE_C};

/**
 * \brief Represents the key "D".
 *
 * \since 5.0.0
 */
inline constexpr scan_code d{SDL_SCANCODE_D};

/**
 * \brief Represents the key "E".
 *
 * \since 5.0.0
 */
inline constexpr scan_code e{SDL_SCANCODE_E};

/**
 * \brief Represents the key "F".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f{SDL_SCANCODE_F};

/**
 * \brief Represents the key "G".
 *
 * \since 5.0.0
 */
inline constexpr scan_code g{SDL_SCANCODE_G};

/**
 * \brief Represents the key "H".
 *
 * \since 5.0.0
 */
inline constexpr scan_code h{SDL_SCANCODE_H};

/**
 * \brief Represents the key "I".
 *
 * \since 5.0.0
 */
inline constexpr scan_code i{SDL_SCANCODE_I};

/**
 * \brief Represents the key "J".
 *
 * \since 5.0.0
 */
inline constexpr scan_code j{SDL_SCANCODE_J};

/**
 * \brief Represents the key "K".
 *
 * \since 5.0.0
 */
inline constexpr scan_code k{SDL_SCANCODE_K};

/**
 * \brief Represents the key "L".
 *
 * \since 5.0.0
 */
inline constexpr scan_code l{SDL_SCANCODE_L};

/**
 * \brief Represents the key "M".
 *
 * \since 5.0.0
 */
inline constexpr scan_code m{SDL_SCANCODE_M};

/**
 * \brief Represents the key "N".
 *
 * \since 5.0.0
 */
inline constexpr scan_code n{SDL_SCANCODE_N};

/**
 * \brief Represents the key "O".
 *
 * \since 5.0.0
 */
inline constexpr scan_code o{SDL_SCANCODE_O};

/**
 * \brief Represents the key "P".
 *
 * \since 5.0.0
 */
inline constexpr scan_code p{SDL_SCANCODE_P};

/**
 * \brief Represents the key "Q".
 *
 * \since 5.0.0
 */
inline constexpr scan_code q{SDL_SCANCODE_Q};

/**
 * \brief Represents the key "R".
 *
 * \since 5.0.0
 */
inline constexpr scan_code r{SDL_SCANCODE_R};

/**
 * \brief Represents the key "S".
 *
 * \since 5.0.0
 */
inline constexpr scan_code s{SDL_SCANCODE_S};

/**
 * \brief Represents the key "T".
 *
 * \since 5.0.0
 */
inline constexpr scan_code t{SDL_SCANCODE_T};

/**
 * \brief Represents the key "U".
 *
 * \since 5.0.0
 */
inline constexpr scan_code u{SDL_SCANCODE_U};

/**
 * \brief Represents the key "V".
 *
 * \since 5.0.0
 */
inline constexpr scan_code v{SDL_SCANCODE_V};

/**
 * \brief Represents the key "W".
 *
 * \since 5.0.0
 */
inline constexpr scan_code w{SDL_SCANCODE_W};

/**
 * \brief Represents the key "X".
 *
 * \since 5.0.0
 */
inline constexpr scan_code x{SDL_SCANCODE_X};

/**
 * \brief Represents the key "Y".
 *
 * \since 5.0.0
 */
inline constexpr scan_code y{SDL_SCANCODE_Y};

/**
 * \brief Represents the key "Z".
 *
 * \since 5.0.0
 */
inline constexpr scan_code z{SDL_SCANCODE_Z};

/**
 * \brief Represents the key "1".
 *
 * \note This is not for a potential "1" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code one{SDL_SCANCODE_1};

/**
 * \brief Represents the key "2".
 *
 * \note This is not for a potential "2" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code two{SDL_SCANCODE_2};

/**
 * \brief Represents the key "3".
 *
 * \note This is not for a potential "3" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code three{SDL_SCANCODE_3};

/**
 * \brief Represents the key "4".
 *
 * \note This is not for a potential "4" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code four{SDL_SCANCODE_4};

/**
 * \brief Represents the key "5".
 *
 * \note This is not for a potential "5" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code five{SDL_SCANCODE_5};

/**
 * \brief Represents the key "6".
 *
 * \note This is not for a potential "6" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code six{SDL_SCANCODE_6};

/**
 * \brief Represents the key "7".
 *
 * \note This is not for a potential "7" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code seven{SDL_SCANCODE_7};

/**
 * \brief Represents the key "8".
 *
 * \note This is not for a potential "8" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code eight{SDL_SCANCODE_8};

/**
 * \brief Represents the key "9".
 *
 * \note This is not for a potential "9" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code nine{SDL_SCANCODE_9};

/**
 * \brief Represents the key "0".
 *
 * \note This is not for a potential "0" key on the key pad.
 *
 * \since 5.0.0
 */
inline constexpr scan_code zero{SDL_SCANCODE_0};

/**
 * \brief Represents the function key "F1".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f1{SDL_SCANCODE_F1};

/**
 * \brief Represents the function key "F2".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f2{SDL_SCANCODE_F2};

/**
 * \brief Represents the function key "F3".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f3{SDL_SCANCODE_F3};

/**
 * \brief Represents the function key "F4".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f4{SDL_SCANCODE_F4};

/**
 * \brief Represents the function key "F5".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f5{SDL_SCANCODE_F5};

/**
 * \brief Represents the function key "F6".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f6{SDL_SCANCODE_F6};

/**
 * \brief Represents the function key "F7".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f7{SDL_SCANCODE_F7};

/**
 * \brief Represents the function key "F8".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f8{SDL_SCANCODE_F8};

/**
 * \brief Represents the function key "F9".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f9{SDL_SCANCODE_F9};

/**
 * \brief Represents the function key "F10".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f10{SDL_SCANCODE_F10};

/**
 * \brief Represents the function key "F11".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f11{SDL_SCANCODE_F11};

/**
 * \brief Represents the function key "F12".
 *
 * \since 5.0.0
 */
inline constexpr scan_code f12{SDL_SCANCODE_F12};

/**
 * \brief Represents the left arrow key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code left{SDL_SCANCODE_LEFT};

/**
 * \brief Represents the right arrow key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code right{SDL_SCANCODE_RIGHT};

/**
 * \brief Represents the up arrow key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code up{SDL_SCANCODE_UP};

/**
 * \brief Represents the down arrow key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code down{SDL_SCANCODE_DOWN};

/**
 * \brief Represents the "Space" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code space{SDL_SCANCODE_SPACE};

/**
 * \brief Represents the "Enter" key.
 *
 * \note This key is also referred to as the "Return" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code enter{SDL_SCANCODE_RETURN};

/**
 * \brief Represents the "Escape" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code escape{SDL_SCANCODE_ESCAPE};

/**
 * \brief Represents the "Backspace" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code backspace{SDL_SCANCODE_BACKSPACE};

/**
 * \brief Represents the "Tab" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code tab{SDL_SCANCODE_TAB};

/**
 * \brief Represents the "Caps Lock" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code caps_lock{SDL_SCANCODE_CAPSLOCK};

/**
 * \brief Represents the left "Shift" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code left_shift{SDL_SCANCODE_LSHIFT};

/**
 * \brief Represents the right "Shift" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code right_shift{SDL_SCANCODE_RSHIFT};

/**
 * \brief Represents the left "CTRL" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code left_ctrl{SDL_SCANCODE_LCTRL};

/**
 * \brief Represents the right "CTRL" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code right_ctrl{SDL_SCANCODE_RCTRL};

/**
 * \brief Represents the left "Alt" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code left_alt{SDL_SCANCODE_LALT};

/**
 * \brief Represents the right "Alt" key.
 *
 * \since 5.0.0
 */
inline constexpr scan_code right_alt{SDL_SCANCODE_RALT};

/**
 * \brief Represents the left "GUI" key.
 *
 * \details On Windows, this is the "Windows key"; for macs it's the "CMD" key, etc.
 *
 * \since 5.0.0
 */
inline constexpr scan_code left_gui{SDL_SCANCODE_LGUI};

/**
 * \brief Represents the right "GUI" key.
 *
 * \details On Windows, this is the "Windows" key; for macs it's the "CMD" key, etc.
 *
 * \since 5.0.0
 */
inline constexpr scan_code right_gui{SDL_SCANCODE_RGUI};

/// \} End of scan code constants

/// \} End of group input

}  // namespace scancodes

}  // namespace cen

#endif  // CENTURION_SCANCODES_HEADER
