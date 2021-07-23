#ifndef CENTURION_COLORS_HEADER
#define CENTURION_COLORS_HEADER

#include "color.hpp"

/**
 * \namespace cen::colors
 *
 * \brief Contains pre-defined `color` constants.
 *
 * \see cen::color
 */
namespace cen::colors {

/// \addtogroup video
/// \{

/**
 * \brief An invisible color. Hex: 000000.
 *
 * \since 3.0.0
 */
inline constexpr color transparent{0, 0, 0, 0};

/**
 * \brief Hex: FFFFFF.
 *
 * \since 3.0.0
 */
inline constexpr color white{0xFF, 0xFF, 0xFF};

/**
 * \brief Hex: 000000.
 *
 * \since 3.0.0
 */
inline constexpr color black{0, 0, 0};

/**
 * \brief Hex: F0F8FF.
 *
 * \since 3.0.0
 */
inline constexpr color alice_blue{0xF0, 0xF8, 0xFF};

/**
 * \brief Hex: FAEBD7.
 *
 * \since 3.0.0
 */
inline constexpr color antique_white{0xFA, 0xEB, 0xD7};

/**
 * \brief Hex: 00FFFF.
 *
 * \since 3.0.0
 */
inline constexpr color aqua{0, 0xFF, 0xFF};

/**
 * \brief Hex: 7FFFD4.
 *
 * \since 3.0.0
 */
inline constexpr color aquamarine{0x7F, 0xFF, 0xD4};

/**
 * \brief Hex: F0FFFF.
 *
 * \since 3.0.0
 */
inline constexpr color azure{0xF0, 0xFF, 0xFF};

/**
 * \brief Hex: F5F5DC.
 *
 * \since 3.0.0
 */
inline constexpr color beige{0xF5, 0xF5, 0xDC};

/**
 * \brief Hex: FFE4C4.
 *
 * \since 3.0.0
 */
inline constexpr color bisque{0xFF, 0xE4, 0xC4};

/**
 * \brief Hex: FFEBCD.
 *
 * \since 3.0.0
 */
inline constexpr color blanched_almond{0xFF, 0xEB, 0xCD};

/**
 * \brief Hex: 0000FF.
 *
 * \since 3.0.0
 */
inline constexpr color blue{0, 0, 0xFF};

/**
 * \brief Hex: 8A2BE2.
 *
 * \since 3.0.0
 */
inline constexpr color blue_violet{0x8A, 0x2B, 0xE2};

/**
 * \brief Hex: A52A2A.
 *
 * \since 3.0.0
 */
inline constexpr color brown{0xA5, 0x2A, 0x2A};

/**
 * \brief Hex: DEB887.
 *
 * \since 3.0.0
 */
inline constexpr color burly_wood{0xDE, 0xB8, 0x87};

/**
 * \brief Hex: 5F9EA0.
 *
 * \since 3.0.0
 */
inline constexpr color cadet_blue{0x5F, 0x9E, 0xA0};

/**
 * \brief Hex: 7FFF00.
 *
 * \since 3.0.0
 */
inline constexpr color chartreuse{0x7F, 0xFF, 0};

/**
 * \brief Hex: D2691E.
 *
 * \since 3.0.0
 */
inline constexpr color chocolate{0xD2, 0x69, 0x1E};

/**
 * \brief Hex: FF7F50.
 *
 * \since 3.0.0
 */
inline constexpr color coral{0xFF, 0x7F, 0x50};

/**
 * \brief Hex: 6495ED.
 *
 * \since 3.0.0
 */
inline constexpr color cornflower_blue{0x64, 0x95, 0xED};

/**
 * \brief Hex: FFF8DC.
 *
 * \since 3.0.0
 */
inline constexpr color cornsilk{0xFF, 0xF8, 0xDC};

/**
 * \brief Hex: DC143C.
 *
 * \since 3.0.0
 */
inline constexpr color crimson{0xDC, 0x14, 0x3C};

/**
 * \brief Hex: 00FFFF.
 *
 * \since 3.0.0
 */
inline constexpr color cyan{0, 0xFF, 0xFF};

/**
 * \brief Hex: 00008B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_blue{0, 0, 0x8B};

/**
 * \brief Hex: 008B8B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_cyan{0, 0x8B, 0x8B};

/**
 * \brief Hex: B8860B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_golden_rod{0xB8, 0x86, 0x0B};

/**
 * \brief Hex: A9A9A9.
 *
 * \since 3.0.0
 */
inline constexpr color dark_gray{0xA9, 0xA9, 0xA9};

/**
 * \brief Hex: A9A9A9.
 *
 * \since 3.0.0
 */
inline constexpr color dark_grey{dark_gray};

/**
 * \brief Hex: 006400.
 *
 * \since 3.0.0
 */
inline constexpr color dark_green{0, 0x64, 0};

/**
 * \brief Hex: BDB76B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_khaki{0xBD, 0xB7, 0x6B};

/**
 * \brief Hex: 8B008B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_magenta{0x8B, 0, 0x8B};

/**
 * \brief Hex: 556B2F.
 *
 * \since 3.0.0
 */
inline constexpr color dark_olive_green{0x55, 0x6B, 0x2F};

/**
 * \brief Hex: FF8C00.
 *
 * \since 3.0.0
 */
inline constexpr color dark_orange{0xFF, 0x8C, 0};

/**
 * \brief Hex: 9932CC.
 *
 * \since 3.0.0
 */
inline constexpr color dark_orchid{0x99, 0x32, 0xCC};

/**
 * \brief Hex: 8B0000.
 *
 * \since 3.0.0
 */
inline constexpr color dark_red{0x8B, 0, 0};

/**
 * \brief Hex: E9967A.
 *
 * \since 3.0.0
 */
inline constexpr color dark_salmon{0xE9, 0x96, 0x7A};

/**
 * \brief Hex: 8FBC8F.
 *
 * \since 3.0.0
 */
inline constexpr color dark_sea_green{0x8F, 0xBC, 0x8F};

/**
 * \brief Hex: 483D8B.
 *
 * \since 3.0.0
 */
inline constexpr color dark_slate_blue{0x48, 0x3D, 0x8B};

/**
 * \brief Hex: 2F4F4F.
 *
 * \since 3.0.0
 */
inline constexpr color dark_slate_gray{0x2F, 0x4F, 0x4F};

/**
 * \brief Hex: 2F4F4F.
 *
 * \since 3.0.0
 */
inline constexpr color dark_slate_grey{dark_slate_gray};

/**
 * \brief Hex: 00CED1.
 *
 * \since 3.0.0
 */
inline constexpr color dark_turquoise{0, 0xCE, 0xD1};

/**
 * \brief Hex: 9400D3.
 *
 * \since 3.0.0
 */
inline constexpr color dark_violet{0x94, 0, 0xD3};

/**
 * \brief Hex: FF1493.
 *
 * \since 3.0.0
 */
inline constexpr color deep_pink{0xFF, 0x14, 0x93};

/**
 * \brief Hex: 00BFFF.
 *
 * \since 3.0.0
 */
inline constexpr color deep_sky_blue{0, 0xBF, 0xFF};

/**
 * \brief Hex: 696969.
 *
 * \since 3.0.0
 */
inline constexpr color dim_gray{0x69, 0x69, 0x69};

/**
 * \brief Hex: 696969.
 *
 * \since 3.0.0
 */
inline constexpr color dim_grey{dim_gray};

/**
 * \brief Hex: 1E90FF.
 *
 * \since 3.0.0
 */
inline constexpr color dodger_blue{0x1E, 0x90, 0xFF};

/**
 * \brief Hex: B22222.
 *
 * \since 3.0.0
 */
inline constexpr color fire_brick{0xB2, 0x22, 0x22};

/**
 * \brief Hex: FFFAF0.
 *
 * \since 3.0.0
 */
inline constexpr color floral_white{0xFF, 0xFA, 0xF0};

/**
 * \brief Hex: 228B22.
 *
 * \since 3.0.0
 */
inline constexpr color forest_green{0x22, 0x8B, 0x22};

/**
 * \brief Hex: FF00FF.
 *
 * \since 3.0.0
 */
inline constexpr color fuchsia{0xFF, 0, 0xFF};

/**
 * \brief Hex: DCDCDC.
 *
 * \since 3.0.0
 */
inline constexpr color gainsboro{0xDC, 0xDC, 0xDC};

/**
 * \brief Hex: F8F8FF.
 *
 * \since 3.0.0
 */
inline constexpr color ghost_white{0xF8, 0xF8, 0xFF};

/**
 * \brief Hex: FFD700.
 *
 * \since 3.0.0
 */
inline constexpr color gold{0xFF, 0xD7, 0};

/**
 * \brief Hex: DAA520.
 *
 * \since 3.0.0
 */
inline constexpr color golden_rod{0xDA, 0xA5, 0x20};

/**
 * \brief Hex: 808080.
 *
 * \since 3.0.0
 */
inline constexpr color gray{0x80, 0x80, 0x80};

/**
 * \brief Hex: 808080.
 *
 * \since 3.0.0
 */
inline constexpr color grey{gray};

/**
 * \brief Hex: 008000.
 *
 * \since 3.0.0
 */
inline constexpr color green{0, 0x80, 0};

/**
 * \brief Hex: ADFF2F.
 *
 * \since 3.0.0
 */
inline constexpr color green_yellow{0xAD, 0xFF, 0x2F};

/**
 * \brief Hex: F0FFF0.
 *
 * \since 3.0.0
 */
inline constexpr color honey_dew{0xF0, 0xFF, 0xF0};

/**
 * \brief Hex: FF69B4.
 *
 * \since 3.0.0
 */
inline constexpr color hot_pink{0xFF, 0x69, 0xB4};

/**
 * \brief Hex: CD5C5C.
 *
 * \since 3.0.0
 */
inline constexpr color indian_red{0xCD, 0x5C, 0x5C};

/**
 * \brief Hex: 4B0082.
 *
 * \since 3.0.0
 */
inline constexpr color indigo{0x4B, 0, 0x82};

/**
 * \brief Hex: FFFFF0.
 *
 * \since 3.0.0
 */
inline constexpr color ivory{0xFF, 0xFF, 0xF0};

/**
 * \brief Hex: F0E68C.
 *
 * \since 3.0.0
 */
inline constexpr color khaki{0xF0, 0xE6, 0x8C};

/**
 * \brief Hex: E6E6FA.
 *
 * \since 3.0.0
 */
inline constexpr color lavender{0xE6, 0xE6, 0xFA};

/**
 * \brief Hex: FFF0F5.
 *
 * \since 3.0.0
 */
inline constexpr color lavender_blush{0xFF, 0xF0, 0xF5};

/**
 * \brief Hex: 7CFC00.
 *
 * \since 3.0.0
 */
inline constexpr color lawn_green{0x7C, 0xFC, 0};

/**
 * \brief Hex: FFFACD.
 *
 * \since 3.0.0
 */
inline constexpr color lemon_chiffon{0xFF, 0xFA, 0xCD};

/**
 * \brief Hex: ADD8E6.
 *
 * \since 3.0.0
 */
inline constexpr color light_blue{0xAD, 0xD8, 0xE6};

/**
 * \brief Hex: F08080.
 *
 * \since 3.0.0
 */
inline constexpr color light_coral{0xF0, 0x80, 0x80};

/**
 * \brief Hex: E0FFFF.
 *
 * \since 3.0.0
 */
inline constexpr color light_cyan{0xE0, 0xFF, 0xFF};

/**
 * \brief Hex: FAFAD2.
 *
 * \since 3.0.0
 */
inline constexpr color light_golden_rod_yellow{0xFA, 0xFA, 0xD2};

/**
 * \brief Hex: D3D3D3.
 *
 * \since 3.0.0
 */
inline constexpr color light_gray{0xD3, 0xD3, 0xD3};

/**
 * \brief Hex: D3D3D3.
 *
 * \since 3.0.0
 */
inline constexpr color light_grey{light_gray};

/**
 * \brief Hex: 90EE90.
 *
 * \since 3.0.0
 */
inline constexpr color light_green{0x90, 0xEE, 0x90};

/**
 * \brief Hex: FFB6C1.
 *
 * \since 3.0.0
 */
inline constexpr color light_pink{0xFF, 0xB6, 0xC1};

/**
 * \brief Hex: FFA07A.
 *
 * \since 3.0.0
 */
inline constexpr color light_salmon{0xFF, 0xA0, 0x7A};

/**
 * \brief Hex: 20B2AA.
 *
 * \since 3.0.0
 */
inline constexpr color light_sea_green{0x20, 0xB2, 0xAA};

/**
 * \brief Hex: 87CEFA.
 *
 * \since 3.0.0
 */
inline constexpr color light_sky_blue{0x87, 0xCE, 0xFA};

/**
 * \brief Hex: 778899.
 *
 * \since 3.0.0
 */
inline constexpr color light_slate_gray{0x77, 0x88, 0x99};

/**
 * \brief Hex: 778899.
 *
 * \since 3.0.0
 */
inline constexpr color light_slate_grey{light_slate_gray};

/**
 * \brief Hex: B0C4DE.
 *
 * \since 3.0.0
 */
inline constexpr color light_steel_blue{0xB0, 0xC4, 0xDE};

/**
 * \brief Hex: FFFFE0.
 *
 * \since 3.0.0
 */
inline constexpr color light_yellow{0xFF, 0xFF, 0xE0};

/**
 * \brief Hex: 00FF00.
 *
 * \since 3.0.0
 */
inline constexpr color lime{0, 0xFF, 0};

/**
 * \brief Hex: 32CD32.
 *
 * \since 3.0.0
 */
inline constexpr color lime_green{0x32, 0xCD, 0x32};

/**
 * \brief Hex: FAF0E6.
 *
 * \since 3.0.0
 */
inline constexpr color linen{0xFA, 0xF0, 0xE6};

/**
 * \brief Hex: FF00FF.
 *
 * \since 3.0.0
 */
inline constexpr color magenta{0xFF, 0, 0xFF};

/**
 * \brief Hex: 800000.
 *
 * \since 3.0.0
 */
inline constexpr color maroon{0x80, 0, 0};

/**
 * \brief Hex: 66CDAA.
 *
 * \since 3.0.0
 */
inline constexpr color medium_aqua_marine{0x66, 0xCD, 0xAA};

/**
 * \brief Hex: 0000CD.
 *
 * \since 3.0.0
 */
inline constexpr color medium_blue{0, 0, 0xCD};

/**
 * \brief Hex: BA55D3.
 *
 * \since 3.0.0
 */
inline constexpr color medium_orchid{0xBA, 0x55, 0xD3};

/**
 * \brief Hex: 9370DB.
 *
 * \since 3.0.0
 */
inline constexpr color medium_purple{0x93, 0x70, 0xDB};

/**
 * \brief Hex: 3CB371.
 *
 * \since 3.0.0
 */
inline constexpr color medium_sea_green{0x3C, 0xB3, 0x71};

/**
 * \brief Hex: 7B68EE.
 *
 * \since 3.0.0
 */
inline constexpr color medium_slate_blue{0x7B, 0x68, 0xEE};

/**
 * \brief Hex: 00FA9A.
 *
 * \since 3.0.0
 */
inline constexpr color medium_spring_green{0, 0xFA, 0x9A};

/**
 * \brief Hex: 48D1CC.
 *
 * \since 3.0.0
 */
inline constexpr color medium_turquoise{0x48, 0xD1, 0xCC};

/**
 * \brief Hex: C71585.
 *
 * \since 3.0.0
 */
inline constexpr color medium_violet_red{0xC7, 0x15, 0x85};

/**
 * \brief Hex: 191970.
 *
 * \since 3.0.0
 */
inline constexpr color midnight_blue{0x19, 0x19, 0x70};

/**
 * \brief Hex: F5FFFA.
 *
 * \since 3.0.0
 */
inline constexpr color mint_cream{0xF5, 0xFF, 0xFA};

/**
 * \brief Hex: FFE4E1.
 *
 * \since 3.0.0
 */
inline constexpr color misty_rose{0xFF, 0xE4, 0xE1};

/**
 * \brief Hex: FFE4B5.
 *
 * \since 3.0.0
 */
inline constexpr color moccasin{0xFF, 0xE4, 0xB5};

/**
 * \brief Hex: FFDEAD.
 *
 * \since 3.0.0
 */
inline constexpr color navajo_white{0xFF, 0xDE, 0xAD};

/**
 * \brief Hex: 000080.
 *
 * \since 3.0.0
 */
inline constexpr color navy{0, 0, 0x80};

/**
 * \brief Hex: FDF5E6.
 *
 * \since 3.0.0
 */
inline constexpr color old_lace{0xFD, 0xF5, 0xE6};

/**
 * \brief Hex: 808000.
 *
 * \since 3.0.0
 */
inline constexpr color olive{0x80, 0x80, 0};

/**
 * \brief Hex: 6B8E23.
 *
 * \since 3.0.0
 */
inline constexpr color olive_drab{0x6B, 0x8E, 0x23};

/**
 * \brief Hex: FFA500.
 *
 * \since 3.0.0
 */
inline constexpr color orange{0xFF, 0xA5, 0};

/**
 * \brief Hex: FF4500.
 *
 * \since 3.0.0
 */
inline constexpr color orange_red{0xFF, 0x45, 0};

/**
 * \brief Hex: DA70D6.
 *
 * \since 3.0.0
 */
inline constexpr color orchid{0xDA, 0x70, 0xD6};

/**
 * \brief Hex: EEE8AA.
 *
 * \since 3.0.0
 */
inline constexpr color pale_golden_rod{0xEE, 0xE8, 0xAA};

/**
 * \brief Hex: 98FB98.
 *
 * \since 3.0.0
 */
inline constexpr color pale_green{0x98, 0xFB, 0x98};

/**
 * \brief Hex: AFEEEE.
 *
 * \since 3.0.0
 */
inline constexpr color pale_turquoise{0xAF, 0xEE, 0xEE};

/**
 * \brief Hex: DB7093.
 *
 * \since 3.0.0
 */
inline constexpr color pale_violet_red{0xDB, 0x70, 0x93};

/**
 * \brief Hex: FFEFD5.
 *
 * \since 3.0.0
 */
inline constexpr color papaya_whip{0xFF, 0xEF, 0xD5};

/**
 * \brief Hex: FFDAB9.
 *
 * \since 3.0.0
 */
inline constexpr color peach_puff{0xFF, 0xDA, 0xB9};

/**
 * \brief Hex: CD853F.
 *
 * \since 3.0.0
 */
inline constexpr color peru{0xCD, 0x85, 0x3F};

/**
 * \brief Hex: FFC0CB.
 *
 * \since 3.0.0
 */
inline constexpr color pink{0xFF, 0xC0, 0xCB};

/**
 * \brief Hex: DDA0DD.
 *
 * \since 3.0.0
 */
inline constexpr color plum{0xDD, 0xA0, 0xDD};

/**
 * \brief Hex: B0E0E6.
 *
 * \since 3.0.0
 */
inline constexpr color powder_blue{0xB0, 0xE0, 0xE6};

/**
 * \brief Hex: 800080.
 *
 * \since 3.0.0
 */
inline constexpr color purple{0x80, 0, 0x80};

/**
 * \brief Hex: 663399.
 *
 * \since 3.0.0
 */
inline constexpr color rebecca_purple{0x66, 0x33, 0x99};

/**
 * \brief Hex: FF0000.
 *
 * \since 3.0.0
 */
inline constexpr color red{0xFF, 0, 0};

/**
 * \brief Hex: BC8F8F.
 *
 * \since 3.0.0
 */
inline constexpr color rosy_brown{0xBC, 0x8F, 0x8F};

/**
 * \brief Hex: 4169E1.
 *
 * \since 3.0.0
 */
inline constexpr color royal_blue{0x41, 0x69, 0xE1};

/**
 * \brief Hex: 8B4513.
 *
 * \since 3.0.0
 */
inline constexpr color saddle_brown{0x8B, 0x45, 0x13};

/**
 * \brief Hex: FA8072.
 *
 * \since 3.0.0
 */
inline constexpr color salmon{0xFA, 0x80, 0x72};

/**
 * \brief Hex: F4A460.
 *
 * \since 3.0.0
 */
inline constexpr color sandy_brown{0xF4, 0xA4, 0x60};

/**
 * \brief Hex: 2E8B57.
 *
 * \since 3.0.0
 */
inline constexpr color sea_green{0x2E, 0x8B, 0x57};

/**
 * \brief Hex: FFF5EE.
 *
 * \since 3.0.0
 */
inline constexpr color sea_shell{0xFF, 0xF5, 0xEE};

/**
 * \brief Hex: A0522D.
 *
 * \since 3.0.0
 */
inline constexpr color sienna{0xA0, 0x52, 0x2D};

/**
 * \brief Hex: C0C0C0.
 *
 * \since 3.0.0
 */
inline constexpr color silver{0xC0, 0xC0, 0xC0};

/**
 * \brief Hex: 87CEEB.
 *
 * \since 3.0.0
 */
inline constexpr color sky_blue{0x87, 0xCE, 0xEB};

/**
 * \brief Hex: 6A5ACD.
 *
 * \since 3.0.0
 */
inline constexpr color slate_blue{0x6A, 0x5A, 0xCD};

/**
 * \brief Hex: 708090.
 *
 * \since 3.0.0
 */
inline constexpr color slate_gray{0x70, 0x80, 0x90};

/**
 * \brief Hex: 708090.
 *
 * \since 3.0.0
 */
inline constexpr color slate_grey{slate_gray};

/**
 * \brief Hex: FFFAFA.
 *
 * \since 3.0.0
 */
inline constexpr color snow{0xFF, 0xFA, 0xFA};

/**
 * \brief Hex: 00FF7F.
 *
 * \since 3.0.0
 */
inline constexpr color spring_green{0, 0xFF, 0x7F};

/**
 * \brief Hex: 4682B4.
 *
 * \since 3.0.0
 */
inline constexpr color steel_blue{0x46, 0x82, 0xB4};

/**
 * \brief Hex: D2B48C.
 *
 * \since 3.0.0
 */
inline constexpr color tan{0xD2, 0xB4, 0x8C};

/**
 * \brief Hex: 008080.
 *
 * \since 3.0.0
 */
inline constexpr color teal{0, 0x80, 0x80};

/**
 * \brief Hex: D8BFD8.
 *
 * \since 3.0.0
 */
inline constexpr color thistle{0xD8, 0xBF, 0xD8};

/**
 * \brief Hex: FF6347.
 *
 * \since 3.0.0
 */
inline constexpr color tomato{0xFF, 0x63, 0x47};

/**
 * \brief Hex: 40E0D0.
 *
 * \since 3.0.0
 */
inline constexpr color turquoise{0x40, 0xE0, 0xD0};

/**
 * \brief Hex: EE82EE.
 *
 * \since 3.0.0
 */
inline constexpr color violet{0xEE, 0x82, 0xEE};

/**
 * \brief Hex: F5DEB3.
 *
 * \since 3.0.0
 */
inline constexpr color wheat{0xF5, 0xDE, 0xB3};

/**
 * \brief Hex: F5F5F5.
 *
 * \since 3.0.0
 */
inline constexpr color white_smoke{0xF5, 0xF5, 0xF5};

/**
 * \brief Hex: FFFF00.
 *
 * \since 3.0.0
 */
inline constexpr color yellow{0xFF, 0xFF, 0};

/**
 * \brief Hex: 9ACD32.
 *
 * \since 3.0.0
 */
inline constexpr color yellow_green{0x9A, 0xCD, 0x32};

/// \} End of group video

}  // namespace cen::colors

#endif  // CENTURION_COLORS_HEADER
