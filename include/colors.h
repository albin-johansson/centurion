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
#include <cstdint>
#include "centurion_api.h"
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
class CENTURION_API Colors final {
 public:
  /**
   * The maximum possible color component value.
   *
   * @since 3.0.0
   */
  CENTURION_API static const uint8_t max = 0xFF;

  /**
   * The minimum possible color component value.
   *
   * @since 3.0.0
   */
  CENTURION_API static const uint8_t min = 0;

  /**
   * An invisible color. Hex: #000000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color transparent;

  /**
   * Hex: #FFFFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color white;

  /**
   * Hex: #000000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color black;

  /**
   * Hex: #F0F8FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color alice_blue;

  /**
   * Hex: #FAEBD7.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color antique_white;

  /**
   * Hex: #00FFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color aqua;

  /**
   * Hex: #7FFFD4.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color aquamarine;

  /**
   * Hex: #F0FFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color azure;

  /**
   * Hex: #F5F5DC.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color beige;

  /**
   * Hex: #FFE4C4.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color bisque;

  /**
   * Hex: #FFEBCD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color blanched_almond;

  /**
   * Hex: #0000FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color blue;

  /**
   * Hex: #8A2BE2.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color blue_violet;

  /**
   * Hex: #A52A2A.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color brown;

  /**
   * Hex: #DEB887.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color burly_wood;

  /**
   * Hex: #5F9EA0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color cadet_blue;

  /**
   * Hex: #7FFF00.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color chartreuse;

  /**
   * Hex: #D2691E.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color chocolate;

  /**
   * Hex: #FF7F50.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color coral;

  /**
   * Hex: #6495ED.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color cornflower_blue;

  /**
   * Hex: #FFF8DC.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color cornsilk;

  /**
   * Hex: #DC143C.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color crimson;

  /**
   * Hex: #00FFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color cyan;

  /**
   * Hex: #00008B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_blue;

  /**
   * Hex: #008B8B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_cyan;

  /**
   * Hex: #B8860B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_golden_rod;

  /**
   * Hex: #A9A9A9.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_gray;

  /**
   * Hex: #A9A9A9.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_grey;

  /**
   * Hex: #006400.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_green;

  /**
   * Hex: #BDB76B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_khaki;

  /**
   * Hex: #8B008B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_magenta;

  /**
   * Hex: #556B2F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_olive_green;

  /**
   * Hex: #FF8C00.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_orange;

  /**
   * Hex: #9932CC.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_orchid;

  /**
   * Hex: #8B0000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_red;

  /**
   * Hex: #E9967A.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_salmon;

  /**
   * Hex: #8FBC8F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_sea_green;

  /**
   * Hex: #483D8B.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_slate_blue;

  /**
   * Hex: #2F4F4F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_slate_gray;

  /**
   * Hex: #2F4F4F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_slate_grey;

  /**
   * Hex: #00CED1.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_turquoise;

  /**
   * Hex: #9400D3.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dark_violet;

  /**
   * Hex: #FF1493.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color deep_pink;

  /**
   * Hex: #00BFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color deep_sky_blue;

  /**
   * Hex: #696969.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dim_gray;

  /**
   * Hex: #696969.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dim_grey;

  /**
   * Hex: #1E90FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color dodger_blue;

  /**
   * Hex: #B22222.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color fire_brick;

  /**
   * Hex: #FFFAF0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color floral_white;

  /**
   * Hex: #228B22.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color forest_green;

  /**
   * Hex: #FF00FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color fuchsia;

  /**
   * Hex: #DCDCDC.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color gainsboro;

  /**
   * Hex: #F8F8FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color ghost_white;

  /**
   * Hex: #FFD700.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color gold;

  /**
   * Hex: #DAA520.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color golden_rod;

  /**
   * Hex: #808080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color gray;

  /**
   * Hex: #808080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color grey;

  /**
   * Hex: #008000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color green;

  /**
   * Hex: #ADFF2F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color green_yellow;

  /**
   * Hex: #F0FFF0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color honey_dew;

  /**
   * Hex: #FF69B4.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color hot_pink;

  /**
   * Hex: #CD5C5C.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color indian_red;

  /**
   * Hex: #4B0082.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color indigo;

  /**
   * Hex: #FFFFF0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color ivory;

  /**
   * Hex: #F0E68C.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color khaki;

  /**
   * Hex: #E6E6FA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lavender;

  /**
   * Hex: #FFF0F5.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lavender_blush;

  /**
   * Hex: #7CFC00.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lawn_green;

  /**
   * Hex: #FFFACD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lemon_chiffon;

  /**
   * Hex: #ADD8E6.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_blue;

  /**
   * Hex: #F08080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_coral;

  /**
   * Hex: #E0FFFF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_cyan;

  /**
   * Hex: #FAFAD2.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_golden_rod_yellow;

  /**
   * Hex: #D3D3D3.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_gray;

  /**
   * Hex: #D3D3D3.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_grey;

  /**
   * Hex: #90EE90.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_green;

  /**
   * Hex: #FFB6C1.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_pink;

  /**
   * Hex: #FFA07A.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_salmon;

  /**
   * Hex: #20B2AA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_sea_green;

  /**
   * Hex: #87CEFA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_sky_blue;

  /**
   * Hex: #778899.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_slate_gray;

  /**
   * Hex: #778899.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_slate_grey;

  /**
   * Hex: #B0C4DE.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_steel_blue;

  /**
   * Hex: #FFFFE0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color light_yellow;

  /**
   * Hex: #00FF00.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lime;

  /**
   * Hex: #32CD32.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color lime_green;

  /**
   * Hex: #FAF0E6.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color linen;

  /**
   * Hex: #FF00FF.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color magenta;

  /**
   * Hex: #800000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color maroon;

  /**
   * Hex: #66CDAA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_aqua_marine;

  /**
   * Hex: #0000CD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_blue;

  /**
   * Hex: #BA55D3.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_orchid;

  /**
   * Hex: #9370DB.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_purple;

  /**
   * Hex: #3CB371.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_sea_green;

  /**
   * Hex: #7B68EE.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_slate_blue;

  /**
   * Hex: #00FA9A.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_spring_green;

  /**
   * Hex: #48D1CC.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_turquoise;

  /**
   * Hex: #C71585.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color medium_violet_red;

  /**
   * Hex: #191970.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color midnight_blue;

  /**
   * Hex: #F5FFFA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color mint_cream;

  /**
   * Hex: #FFE4E1.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color misty_rose;

  /**
   * Hex: #FFE4B5.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color moccasin;

  /**
   * Hex: #FFDEAD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color navajo_white;

  /**
   * Hex: #000080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color navy;

  /**
   * Hex: #FDF5E6.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color old_lace;

  /**
   * Hex: #808000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color olive;

  /**
   * Hex: #6B8E23.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color olive_drab;

  /**
   * Hex: #FFA500.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color orange;

  /**
   * Hex: #FF4500.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color orange_red;

  /**
   * Hex: #DA70D6.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color orchid;

  /**
   * Hex: #EEE8AA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color pale_golden_rod;

  /**
   * Hex: #98FB98.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color pale_green;

  /**
   * Hex: #AFEEEE.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color pale_turquoise;

  /**
   * Hex: #DB7093.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color pale_violet_red;

  /**
   * Hex: #FFEFD5.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color papaya_whip;

  /**
   * Hex: #FFDAB9.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color peach_puff;

  /**
   * Hex: #CD853F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color peru;

  /**
   * Hex: #FFC0CB.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color pink;

  /**
   * Hex: #DDA0DD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color plum;

  /**
   * Hex: #B0E0E6.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color powder_blue;

  /**
   * Hex: #800080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color purple;

  /**
   * Hex: #663399.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color rebecca_purple;

  /**
   * Hex: #FF0000.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color red;

  /**
   * Hex: #BC8F8F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color rosy_brown;

  /**
   * Hex: #4169E1.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color royal_blue;

  /**
   * Hex: #8B4513.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color saddle_brown;

  /**
   * Hex: #FA8072.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color salmon;

  /**
   * Hex: #F4A460.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color sandy_brown;

  /**
   * Hex: #2E8B57.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color sea_green;

  /**
   * Hex: #FFF5EE.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color sea_shell;

  /**
   * Hex: #A0522D.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color sienna;

  /**
   * Hex: #C0C0C0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color silver;

  /**
   * Hex: #87CEEB.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color sky_blue;

  /**
   * Hex: #6A5ACD.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color slate_blue;

  /**
   * Hex: #708090.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color slate_gray;

  /**
   * Hex: #708090.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color slate_grey;

  /**
   * Hex: #FFFAFA.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color snow;

  /**
   * Hex: #00FF7F.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color spring_green;

  /**
   * Hex: #4682B4.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color steel_blue;

  /**
   * Hex: #D2B48C.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color tan;

  /**
   * Hex: #008080.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color teal;

  /**
   * Hex: #D8BFD8.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color thistle;

  /**
   * Hex: #FF6347.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color tomato;

  /**
   * Hex: #40E0D0.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color turquoise;

  /**
   * Hex: #EE82EE.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color violet;

  /**
   * Hex: #F5DEB3.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color wheat;

  /**
   * Hex: #F5F5F5.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color white_smoke;

  /**
   * Hex: #FFFF00.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color yellow;

  /**
   * Hex: #9ACD32.
   *
   * @since 3.0.0
   */
  CENTURION_API static const Color yellow_green;

  Colors() = delete;

};

}
