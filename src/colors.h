/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include <SDL_pixels.h>
#include <cstdint>
#include "color.h"

namespace centurion {

/**
 * The Colors class is a utility class that provides more than 140 SDL colors. The colors
 * defined in this class were based on
 * <a href=https://www.w3schools.com/colors/colors_names.asp>this</a> list.
 *
 * @since 3.0.0
 * @author Albin Johansson
 */
class Colors final {
 public:
  /**
   * An invisible color. Hex: #000000.
   *
   * @since 3.0.0
   */
  static constexpr Color transparent{0, 0, 0, 0};

  /**
   * Hex: #FFFFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color white{0xFF, 0xFF, 0xFF, 0xFF};

  /**
   * Hex: #000000.
   *
   * @since 3.0.0
   */
  static constexpr Color black{0, 0, 0, 0xFF};

  /**
   * Hex: #F0F8FF.
   *
   * @since 3.0.0
   */
  static constexpr Color alice_blue{0xF0, 0xF8, 0xFF, 0xFF};

  /**
   * Hex: #FAEBD7.
   *
   * @since 3.0.0
   */
  static constexpr Color antique_white{0xFA, 0xEB, 0xD7, 0xFF};

  /**
   * Hex: #00FFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color aqua{0, 0xFF, 0xFF, 0xFF};

  /**
   * Hex: #7FFFD4.
   *
   * @since 3.0.0
   */
  static constexpr Color aquamarine{0x7F, 0xFF, 0xD4, 0xFF};

  /**
   * Hex: #F0FFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color azure{0xF0, 0xFF, 0xFF, 0xFF};

  /**
   * Hex: #F5F5DC.
   *
   * @since 3.0.0
   */
  static constexpr Color beige{0xF5, 0xF5, 0xDC, 0xFF};

  /**
   * Hex: #FFE4C4.
   *
   * @since 3.0.0
   */
  static constexpr Color bisque{0xFF, 0xE4, 0xC4, 0xFF};

  /**
   * Hex: #FFEBCD.
   *
   * @since 3.0.0
   */
  static constexpr Color blanched_almond{0xFF, 0xEB, 0xCD, 0xFF};

  /**
   * Hex: #0000FF.
   *
   * @since 3.0.0
   */
  static constexpr Color blue{0, 0, 0xFF, 0xFF};

  /**
   * Hex: #8A2BE2.
   *
   * @since 3.0.0
   */
  static constexpr Color blue_violet{0x8A, 0x2B, 0xE2, 0xFF};

  /**
   * Hex: #A52A2A.
   *
   * @since 3.0.0
   */
  static constexpr Color brown{0xA5, 0x2A, 0x2A, 0xFF};

  /**
   * Hex: #DEB887.
   *
   * @since 3.0.0
   */
  static constexpr Color burly_wood{0xDE, 0xB8, 0x87, 0xFF};

  /**
   * Hex: #5F9EA0.
   *
   * @since 3.0.0
   */
  static constexpr Color cadet_blue{0x5F, 0x9E, 0xA0, 0xFF};

  /**
   * Hex: #7FFF00.
   *
   * @since 3.0.0
   */
  static constexpr Color chartreuse{0x7F, 0xFF, 0, 0xFF};

  /**
   * Hex: #D2691E.
   *
   * @since 3.0.0
   */
  static constexpr Color chocolate{0xD2, 0x69, 0x1E, 0xFF};

  /**
   * Hex: #FF7F50.
   *
   * @since 3.0.0
   */
  static constexpr Color coral{0xFF, 0x7F, 0x50, 0xFF};

  /**
   * Hex: #6495ED.
   *
   * @since 3.0.0
   */
  static constexpr Color cornflower_blue{0x64, 0x95, 0xED, 0xFF};

  /**
   * Hex: #FFF8DC.
   *
   * @since 3.0.0
   */
  static constexpr Color cornsilk{0xFF, 0xF8, 0xDC, 0xFF};

  /**
   * Hex: #DC143C.
   *
   * @since 3.0.0
   */
  static constexpr Color crimson{0xDC, 0x14, 0x3C, 0xFF};

  /**
   * Hex: #00FFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color cyan{0, 0xFF, 0xFF, 0xFF};

  /**
   * Hex: #00008B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_blue{0, 0, 0x8B, 0xFF};

  /**
   * Hex: #008B8B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_cyan{0, 0x8B, 0x8B, 0xFF};

  /**
   * Hex: #B8860B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_golden_rod{0xB8, 0x86, 0x0B, 0xFF};

  /**
   * Hex: #A9A9A9.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_gray{0xA9, 0xA9, 0xA9, 0xFF};

  /**
   * Hex: #A9A9A9.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_grey{dark_gray};

  /**
   * Hex: #006400.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_green{0, 0x64, 0, 0xFF};

  /**
   * Hex: #BDB76B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_khaki{0xBD, 0xB7, 0x6B, 0xFF};

  /**
   * Hex: #8B008B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_magenta{0x8B, 0, 0x8B, 0xFF};

  /**
   * Hex: #556B2F.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_olive_green{0x55, 0x6B, 0x2F, 0xFF};

  /**
   * Hex: #FF8C00.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_orange{0xFF, 0x8C, 0, 0xFF};

  /**
   * Hex: #9932CC.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_orchid{0x99, 0x32, 0xCC, 0xFF};

  /**
   * Hex: #8B0000.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_red{0x8B, 0, 0, 0xFF};

  /**
   * Hex: #E9967A.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_salmon{0xE9, 0x96, 0x7A, 0xFF};

  /**
   * Hex: #8FBC8F.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_sea_green{0x8F, 0xBC, 0x8F, 0xFF};

  /**
   * Hex: #483D8B.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_slate_blue{0x48, 0x3D, 0x8B, 0xFF};

  /**
   * Hex: #2F4F4F.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_slate_gray{0x2F, 0x4F, 0x4F, 0xFF};

  /**
   * Hex: #2F4F4F.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_slate_grey{dark_slate_gray};

  /**
   * Hex: #00CED1.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_turquoise{0, 0xCE, 0xD1, 0xFF};

  /**
   * Hex: #9400D3.
   *
   * @since 3.0.0
   */
  static constexpr Color dark_violet{0x94, 0, 0xD3, 0xFF};

  /**
   * Hex: #FF1493.
   *
   * @since 3.0.0
   */
  static constexpr Color deep_pink{0xFF, 0x14, 0x93, 0xFF};

  /**
   * Hex: #00BFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color deep_sky_blue{0, 0xBF, 0xFF, 0xFF};

  /**
   * Hex: #696969.
   *
   * @since 3.0.0
   */
  static constexpr Color dim_gray{0x69, 0x69, 0x69, 0xFF};

  /**
   * Hex: #696969.
   *
   * @since 3.0.0
   */
  static constexpr Color dim_grey{dim_gray};

  /**
   * Hex: #1E90FF.
   *
   * @since 3.0.0
   */
  static constexpr Color dodger_blue{0x1E, 0x90, 0xFF, 0xFF};

  /**
   * Hex: #B22222.
   *
   * @since 3.0.0
   */
  static constexpr Color fire_brick{0xB2, 0x22, 0x22, 0xFF};

  /**
   * Hex: #FFFAF0.
   *
   * @since 3.0.0
   */
  static constexpr Color floral_white{0xFF, 0xFA, 0xF0, 0xFF};

  /**
   * Hex: #228B22.
   *
   * @since 3.0.0
   */
  static constexpr Color forest_green{0x22, 0x8B, 0x22, 0xFF};

  /**
   * Hex: #FF00FF.
   *
   * @since 3.0.0
   */
  static constexpr Color fuchsia{0xFF, 0, 0xFF, 0xFF};

  /**
   * Hex: #DCDCDC.
   *
   * @since 3.0.0
   */
  static constexpr Color gainsboro{0xDC, 0xDC, 0xDC, 0xFF};

  /**
   * Hex: #F8F8FF.
   *
   * @since 3.0.0
   */
  static constexpr Color ghost_white{0xF8, 0xF8, 0xFF, 0xFF};

  /**
   * Hex: #FFD700.
   *
   * @since 3.0.0
   */
  static constexpr Color gold{0xFF, 0xD7, 0, 0xFF};

  /**
   * Hex: #DAA520.
   *
   * @since 3.0.0
   */
  static constexpr Color golden_rod{0xDA, 0xA5, 0x20, 0xFF};

  /**
   * Hex: #808080.
   *
   * @since 3.0.0
   */
  static constexpr Color gray{0x80, 0x80, 0x80, 0xFF};

  /**
   * Hex: #808080.
   *
   * @since 3.0.0
   */
  static constexpr Color grey{gray};

  /**
   * Hex: #008000.
   *
   * @since 3.0.0
   */
  static constexpr Color green{0, 0x80, 0, 0xFF};

  /**
   * Hex: #ADFF2F.
   *
   * @since 3.0.0
   */
  static constexpr Color green_yellow{0xAD, 0xFF, 0x2F, 0xFF};

  /**
   * Hex: #F0FFF0.
   *
   * @since 3.0.0
   */
  static constexpr Color honey_dew{0xF0, 0xFF, 0xF0, 0xFF};

  /**
   * Hex: #FF69B4.
   *
   * @since 3.0.0
   */
  static constexpr Color hot_pink{0xFF, 0x69, 0xB4, 0xFF};

  /**
   * Hex: #CD5C5C.
   *
   * @since 3.0.0
   */
  static constexpr Color indian_red{0xCD, 0x5C, 0x5C, 0xFF};

  /**
   * Hex: #4B0082.
   *
   * @since 3.0.0
   */
  static constexpr Color indigo{0x4B, 0, 0x82, 0xFF};

  /**
   * Hex: #FFFFF0.
   *
   * @since 3.0.0
   */
  static constexpr Color ivory{0xFF, 0xFF, 0xF0, 0xFF};

  /**
   * Hex: #F0E68C.
   *
   * @since 3.0.0
   */
  static constexpr Color khaki{0xF0, 0xE6, 0x8C, 0xFF};

  /**
   * Hex: #E6E6FA.
   *
   * @since 3.0.0
   */
  static constexpr Color lavender{0xE6, 0xE6, 0xFA, 0xFF};

  /**
   * Hex: #FFF0F5.
   *
   * @since 3.0.0
   */
  static constexpr Color lavender_blush{0xFF, 0xF0, 0xF5, 0xFF};

  /**
   * Hex: #7CFC00.
   *
   * @since 3.0.0
   */
  static constexpr Color lawn_green{0x7C, 0xFC, 0, 0xFF};

  /**
   * Hex: #FFFACD.
   *
   * @since 3.0.0
   */
  static constexpr Color lemon_chiffon{0xFF, 0xFA, 0xCD, 0xFF};

  /**
   * Hex: #ADD8E6.
   *
   * @since 3.0.0
   */
  static constexpr Color light_blue{0xAD, 0xD8, 0xE6, 0xFF};

  /**
   * Hex: #F08080.
   *
   * @since 3.0.0
   */
  static constexpr Color light_coral{0xF0, 0x80, 0x80, 0xFF};

  /**
   * Hex: #E0FFFF.
   *
   * @since 3.0.0
   */
  static constexpr Color light_cyan{0xE0, 0xFF, 0xFF, 0xFF};

  /**
   * Hex: #FAFAD2.
   *
   * @since 3.0.0
   */
  static constexpr Color light_golden_rod_yellow{0xFA, 0xFA, 0xD2, 0xFF};

  /**
   * Hex: #D3D3D3.
   *
   * @since 3.0.0
   */
  static constexpr Color light_gray{0xD3, 0xD3, 0xD3, 0xFF};

  /**
   * Hex: #D3D3D3.
   *
   * @since 3.0.0
   */
  static constexpr Color light_grey{light_gray};

  /**
   * Hex: #90EE90.
   *
   * @since 3.0.0
   */
  static constexpr Color light_green{0x90, 0xEE, 0x90, 0xFF};

  /**
   * Hex: #FFB6C1.
   *
   * @since 3.0.0
   */
  static constexpr Color light_pink{0xFF, 0xB6, 0xC1, 0xFF};

  /**
   * Hex: #FFA07A.
   *
   * @since 3.0.0
   */
  static constexpr Color light_salmon{0xFF, 0xA0, 0x7A, 0xFF};

  /**
   * Hex: #20B2AA.
   *
   * @since 3.0.0
   */
  static constexpr Color light_sea_green{0x20, 0xB2, 0xAA, 0xFF};

  /**
   * Hex: #87CEFA.
   *
   * @since 3.0.0
   */
  static constexpr Color light_sky_blue{0x87, 0xCE, 0xFA, 0xFF};

  /**
   * Hex: #778899.
   *
   * @since 3.0.0
   */
  static constexpr Color light_slate_gray{0x77, 0x88, 0x99, 0xFF};

  /**
   * Hex: #778899.
   *
   * @since 3.0.0
   */
  static constexpr Color light_slate_grey{light_slate_gray};

  /**
   * Hex: #B0C4DE.
   *
   * @since 3.0.0
   */
  static constexpr Color light_steel_blue{0xB0, 0xC4, 0xDE, 0xFF};

  /**
   * Hex: #FFFFE0.
   *
   * @since 3.0.0
   */
  static constexpr Color light_yellow{0xFF, 0xFF, 0xE0, 0xFF};

  /**
   * Hex: #00FF00.
   *
   * @since 3.0.0
   */
  static constexpr Color lime{0, 0xFF, 0, 0xFF};

  /**
   * Hex: #32CD32.
   *
   * @since 3.0.0
   */
  static constexpr Color lime_green{0x32, 0xCD, 0x32, 0xFF};

  /**
   * Hex: #FAF0E6.
   *
   * @since 3.0.0
   */
  static constexpr Color linen{0xFA, 0xF0, 0xE6, 0xFF};

  /**
   * Hex: #FF00FF.
   *
   * @since 3.0.0
   */
  static constexpr Color magenta{0xFF, 0, 0xFF, 0xFF};

  /**
   * Hex: #800000.
   *
   * @since 3.0.0
   */
  static constexpr Color maroon{0x80, 0, 0, 0xFF};

  /**
   * Hex: #66CDAA.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_aqua_marine{0x66, 0xCD, 0xAA, 0xFF};

  /**
   * Hex: #0000CD.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_blue{0, 0, 0xCD, 0xFF};

  /**
   * Hex: #BA55D3.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_orchid{0xBA, 0x55, 0xD3, 0xFF};

  /**
   * Hex: #9370DB.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_purple{0x93, 0x70, 0xDB, 0xFF};

  /**
   * Hex: #3CB371.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_sea_green{0x3C, 0xB3, 0x71, 0xFF};

  /**
   * Hex: #7B68EE.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_slate_blue{0x7B, 0x68, 0xEE, 0xFF};

  /**
   * Hex: #00FA9A.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_spring_green{0, 0xFA, 0x9A, 0xFF};

  /**
   * Hex: #48D1CC.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_turquoise{0x48, 0xD1, 0xCC, 0xFF};

  /**
   * Hex: #C71585.
   *
   * @since 3.0.0
   */
  static constexpr Color medium_violet_red{0xC7, 0x15, 0x85, 0xFF};

  /**
   * Hex: #191970.
   *
   * @since 3.0.0
   */
  static constexpr Color midnight_blue{0x19, 0x19, 0x70, 0xFF};

  /**
   * Hex: #F5FFFA.
   *
   * @since 3.0.0
   */
  static constexpr Color mint_cream{0xF5, 0xFF, 0xFA, 0xFF};

  /**
   * Hex: #FFE4E1.
   *
   * @since 3.0.0
   */
  static constexpr Color misty_rose{0xFF, 0xE4, 0xE1, 0xFF};

  /**
   * Hex: #FFE4B5.
   *
   * @since 3.0.0
   */
  static constexpr Color moccasin{0xFF, 0xE4, 0xB5, 0xFF};

  /**
   * Hex: #FFDEAD.
   *
   * @since 3.0.0
   */
  static constexpr Color navajo_white{0xFF, 0xDE, 0xAD, 0xFF};

  /**
   * Hex: #000080.
   *
   * @since 3.0.0
   */
  static constexpr Color navy{0, 0, 0x80, 0xFF};

  /**
   * Hex: #FDF5E6.
   *
   * @since 3.0.0
   */
  static constexpr Color old_lace{0xFD, 0xF5, 0xE6, 0xFF};

  /**
   * Hex: #808000.
   *
   * @since 3.0.0
   */
  static constexpr Color olive{0x80, 0x80, 0, 0xFF};

  /**
   * Hex: #6B8E23.
   *
   * @since 3.0.0
   */
  static constexpr Color olive_drab{0x6B, 0x8E, 0x23, 0xFF};

  /**
   * Hex: #FFA500.
   *
   * @since 3.0.0
   */
  static constexpr Color orange{0xFF, 0xA5, 0, 0xFF};

  /**
   * Hex: #FF4500.
   *
   * @since 3.0.0
   */
  static constexpr Color orange_red{0xFF, 0x45, 0, 0xFF};

  /**
   * Hex: #DA70D6.
   *
   * @since 3.0.0
   */
  static constexpr Color orchid{0xDA, 0x70, 0xD6, 0xFF};

  /**
   * Hex: #EEE8AA.
   *
   * @since 3.0.0
   */
  static constexpr Color pale_golden_rod{0xEE, 0xE8, 0xAA, 0xFF};

  /**
   * Hex: #98FB98.
   *
   * @since 3.0.0
   */
  static constexpr Color pale_green{0x98, 0xFB, 0x98, 0xFF};

  /**
   * Hex: #AFEEEE.
   *
   * @since 3.0.0
   */
  static constexpr Color pale_turquoise{0xAF, 0xEE, 0xEE, 0xFF};

  /**
   * Hex: #DB7093.
   *
   * @since 3.0.0
   */
  static constexpr Color pale_violet_red{0xDB, 0x70, 0x93, 0xFF};

  /**
   * Hex: #FFEFD5.
   *
   * @since 3.0.0
   */
  static constexpr Color papaya_whip{0xFF, 0xEF, 0xD5, 0xFF};

  /**
   * Hex: #FFDAB9.
   *
   * @since 3.0.0
   */
  static constexpr Color peach_puff{0xFF, 0xDA, 0xB9, 0xFF};

  /**
   * Hex: #CD853F.
   *
   * @since 3.0.0
   */
  static constexpr Color peru{0xCD, 0x85, 0x3F, 0xFF};

  /**
   * Hex: #FFC0CB.
   *
   * @since 3.0.0
   */
  static constexpr Color pink{0xFF, 0xC0, 0xCB, 0xFF};

  /**
   * Hex: #DDA0DD.
   *
   * @since 3.0.0
   */
  static constexpr Color plum{0xDD, 0xA0, 0xDD, 0xFF};

  /**
   * Hex: #B0E0E6.
   *
   * @since 3.0.0
   */
  static constexpr Color powder_blue{0xB0, 0xE0, 0xE6, 0xFF};

  /**
   * Hex: #800080.
   *
   * @since 3.0.0
   */
  static constexpr Color purple{0x80, 0, 0x80, 0xFF};

  /**
   * Hex: #663399.
   *
   * @since 3.0.0
   */
  static constexpr Color rebecca_purple{0x66, 0x33, 0x99, 0xFF};

  /**
   * Hex: #FF0000.
   *
   * @since 3.0.0
   */
  static constexpr Color red{0xFF, 0, 0, 0xFF};

  /**
   * Hex: #BC8F8F.
   *
   * @since 3.0.0
   */
  static constexpr Color rosy_brown{0xBC, 0x8F, 0x8F, 0xFF};

  /**
   * Hex: #4169E1.
   *
   * @since 3.0.0
   */
  static constexpr Color royal_blue{0x41, 0x69, 0xE1, 0xFF};

  /**
   * Hex: #8B4513.
   *
   * @since 3.0.0
   */
  static constexpr Color saddle_brown{0x8B, 0x45, 0x13, 0xFF};

  /**
   * Hex: #FA8072.
   *
   * @since 3.0.0
   */
  static constexpr Color salmon{0xFA, 0x80, 0x72, 0xFF};

  /**
   * Hex: #F4A460.
   *
   * @since 3.0.0
   */
  static constexpr Color sandy_brown{0xF4, 0xA4, 0x60, 0xFF};

  /**
   * Hex: #2E8B57.
   *
   * @since 3.0.0
   */
  static constexpr Color sea_green{0x2E, 0x8B, 0x57, 0xFF};

  /**
   * Hex: #FFF5EE.
   *
   * @since 3.0.0
   */
  static constexpr Color sea_shell{0xFF, 0xF5, 0xEE, 0xFF};

  /**
   * Hex: #A0522D.
   *
   * @since 3.0.0
   */
  static constexpr Color sienna{0xA0, 0x52, 0x2D, 0xFF};

  /**
   * Hex: #C0C0C0.
   *
   * @since 3.0.0
   */
  static constexpr Color silver{0xC0, 0xC0, 0xC0, 0xFF};

  /**
   * Hex: #87CEEB.
   *
   * @since 3.0.0
   */
  static constexpr Color sky_blue{0x87, 0xCE, 0xEB, 0xFF};

  /**
   * Hex: #6A5ACD.
   *
   * @since 3.0.0
   */
  static constexpr Color slate_blue{0x6A, 0x5A, 0xCD, 0xFF};

  /**
   * Hex: #708090.
   *
   * @since 3.0.0
   */
  static constexpr Color slate_gray{0x70, 0x80, 0x90, 0xFF};

  /**
   * Hex: #708090.
   *
   * @since 3.0.0
   */
  static constexpr Color slate_grey{slate_gray};

  /**
   * Hex: #FFFAFA.
   *
   * @since 3.0.0
   */
  static constexpr Color snow{0xFF, 0xFA, 0xFA, 0xFF};

  /**
   * Hex: #00FF7F.
   *
   * @since 3.0.0
   */
  static constexpr Color spring_green{0, 0xFF, 0x7F, 0xFF};

  /**
   * Hex: #4682B4.
   *
   * @since 3.0.0
   */
  static constexpr Color steel_blue{0x46, 0x82, 0xB4, 0xFF};

  /**
   * Hex: #D2B48C.
   *
   * @since 3.0.0
   */
  static constexpr Color tan{0xD2, 0xB4, 0x8C, 0xFF};

  /**
   * Hex: #008080.
   *
   * @since 3.0.0
   */
  static constexpr Color teal{0, 0x80, 0x80, 0xFF};

  /**
   * Hex: #D8BFD8.
   *
   * @since 3.0.0
   */
  static constexpr Color thistle{0xD8, 0xBF, 0xD8, 0xFF};

  /**
   * Hex: #FF6347.
   *
   * @since 3.0.0
   */
  static constexpr Color tomato{0xFF, 0x63, 0x47, 0xFF};

  /**
   * Hex: #40E0D0.
   *
   * @since 3.0.0
   */
  static constexpr Color turquoise{0x40, 0xE0, 0xD0, 0xFF};

  /**
   * Hex: #EE82EE.
   *
   * @since 3.0.0
   */
  static constexpr Color violet{0xEE, 0x82, 0xEE, 0xFF};

  /**
   * Hex: #F5DEB3.
   *
   * @since 3.0.0
   */
  static constexpr Color wheat{0xF5, 0xDe, 0xB3, 0xFF};

  /**
   * Hex: #F5F5F5.
   *
   * @since 3.0.0
   */
  static constexpr Color white_smoke{0xF5, 0xF5, 0xF5, 0xFF};

  /**
   * Hex: #FFFF00.
   *
   * @since 3.0.0
   */
  static constexpr Color yellow{0xFF, 0xFF, 0, 0xFF};

  /**
   * Hex: #9ACD32.
   *
   * @since 3.0.0
   */
  static constexpr Color yellow_green{0x9A, 0xCD, 0x32, 0xFF};

  Colors() = delete;

};

}
