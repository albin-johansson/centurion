// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>

#include <SDL3/SDL_video.h>

namespace cen {

/// The underlying type of `cen::SystemTheme`.
using SystemThemeRepr = std::underlying_type_t<SDL_SystemTheme>;

/// The underlying type of `cen::DisplayOrientation`.
using DisplayOrientationRepr = std::underlying_type_t<SDL_DisplayOrientation>;

/// The underlying type of `cen::FlashOp`.
using FlashOpRepr = std::underlying_type_t<SDL_FlashOperation>;

/// The underlying type of `cen::GLAttr`.
using GLAttrRepr = std::underlying_type_t<SDL_GLAttr>;

/// The underlying type of `cen::HitTestResult`.
using HitTestResultRepr = std::underlying_type_t<SDL_HitTestResult>;

/// \see SDL_SystemTheme
enum class SystemTheme : SystemThemeRepr
{
  kUnknown = SDL_SYSTEM_THEME_UNKNOWN,
  kLight = SDL_SYSTEM_THEME_LIGHT,
  kDark = SDL_SYSTEM_THEME_DARK,
};

/// \see SDL_DisplayOrientation
enum class DisplayOrientation : DisplayOrientationRepr
{
  kUnknown = SDL_ORIENTATION_UNKNOWN,
  kLandscape = SDL_ORIENTATION_LANDSCAPE,
  kLandscapeFlipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  kPortrait = SDL_ORIENTATION_PORTRAIT,
  kPortraitFlipped = SDL_ORIENTATION_PORTRAIT_FLIPPED,
};

/// \see SDL_FlashOperation
enum class FlashOp : FlashOpRepr
{
  kCancel = SDL_FLASH_CANCEL,
  kBriefly = SDL_FLASH_BRIEFLY,
  kUntilFocused = SDL_FLASH_UNTIL_FOCUSED,
};

/// \see SDL_GLAttr
enum class GLAttr : GLAttrRepr
{
  kRedSize = SDL_GL_RED_SIZE,
  kGreenSize = SDL_GL_GREEN_SIZE,
  kBlueSize = SDL_GL_BLUE_SIZE,
  kAlphaSize = SDL_GL_ALPHA_SIZE,
  kBufferSize = SDL_GL_BUFFER_SIZE,
  kDoubleBuffer = SDL_GL_DOUBLEBUFFER,
  kDepthSize = SDL_GL_DEPTH_SIZE,
  kStencilSize = SDL_GL_STENCIL_SIZE,
  kAccumRedSize = SDL_GL_ACCUM_RED_SIZE,
  kAccumGreenSize = SDL_GL_ACCUM_GREEN_SIZE,
  kAccumBlueSize = SDL_GL_ACCUM_BLUE_SIZE,
  kAccumAlphaSize = SDL_GL_ACCUM_ALPHA_SIZE,
  kStereo = SDL_GL_STEREO,
  kMultisampleBuffers = SDL_GL_MULTISAMPLEBUFFERS,
  kMultisamplesSamples = SDL_GL_MULTISAMPLESAMPLES,
  kAcceleratedVisual = SDL_GL_ACCELERATED_VISUAL,
  kRetainedBacking = SDL_GL_RETAINED_BACKING,
  kContextMajorVersion = SDL_GL_CONTEXT_MAJOR_VERSION,
  kContextMinorVersion = SDL_GL_CONTEXT_MINOR_VERSION,
  kContextFlags = SDL_GL_CONTEXT_FLAGS,
  kContextProfileMask = SDL_GL_CONTEXT_PROFILE_MASK,
  kShareWithCurrentContext = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
  kFramebufferSrgbCapable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
  kContextReleaseBehavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  kContextResetNotification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  kContextNoError = SDL_GL_CONTEXT_NO_ERROR,
  kFloatBuffers = SDL_GL_FLOATBUFFERS,
  kEglPlatform = SDL_GL_EGL_PLATFORM
};

/// \see SDL_HitTestResult
enum class HitTestResult : HitTestResultRepr
{
  kNormal = SDL_HITTEST_NORMAL,
  kDraggable = SDL_HITTEST_DRAGGABLE,
  kTopLeft = SDL_HITTEST_RESIZE_TOPLEFT,
  kResizeTop = SDL_HITTEST_RESIZE_TOP,
  kResizeTopRight = SDL_HITTEST_RESIZE_TOPRIGHT,
  kResizeRight = SDL_HITTEST_RESIZE_RIGHT,
  kResizeBottomRight = SDL_HITTEST_RESIZE_BOTTOMRIGHT,
  kResizeBottom = SDL_HITTEST_RESIZE_BOTTOM,
  kResizeBottomLeft = SDL_HITTEST_RESIZE_BOTTOMLEFT,
  kResizeLeft = SDL_HITTEST_RESIZE_LEFT
};

}  // namespace cen
