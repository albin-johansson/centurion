#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "opengl.hpp"

using Attr = cen::GLAttribute;

TEST(GLAttribute, Values)
{
  ASSERT_EQ(SDL_GL_RED_SIZE, ToUnderlying(Attr::RedSize));
  ASSERT_EQ(SDL_GL_GREEN_SIZE, ToUnderlying(Attr::GreenSize));
  ASSERT_EQ(SDL_GL_BLUE_SIZE, ToUnderlying(Attr::BlueSize));
  ASSERT_EQ(SDL_GL_ALPHA_SIZE, ToUnderlying(Attr::AlphaSize));
  ASSERT_EQ(SDL_GL_BUFFER_SIZE, ToUnderlying(Attr::BufferSize));

  ASSERT_EQ(SDL_GL_DOUBLEBUFFER, ToUnderlying(Attr::DoubleBuffer));

  ASSERT_EQ(SDL_GL_DEPTH_SIZE, ToUnderlying(Attr::DepthSize));
  ASSERT_EQ(SDL_GL_STENCIL_SIZE, ToUnderlying(Attr::StencilSize));

  ASSERT_EQ(SDL_GL_ACCUM_RED_SIZE, ToUnderlying(Attr::AccumRedSize));
  ASSERT_EQ(SDL_GL_ACCUM_GREEN_SIZE, ToUnderlying(Attr::AccumGreenSize));
  ASSERT_EQ(SDL_GL_ACCUM_BLUE_SIZE, ToUnderlying(Attr::AccumBlueSize));
  ASSERT_EQ(SDL_GL_ACCUM_ALPHA_SIZE, ToUnderlying(Attr::AccumAlphaSize));

  ASSERT_EQ(SDL_GL_STEREO, ToUnderlying(Attr::Stereo));
  ASSERT_EQ(SDL_GL_MULTISAMPLEBUFFERS, ToUnderlying(Attr::MultisampleBuffers));
  ASSERT_EQ(SDL_GL_MULTISAMPLESAMPLES, ToUnderlying(Attr::MultisampleSamples));
  ASSERT_EQ(SDL_GL_ACCELERATED_VISUAL, ToUnderlying(Attr::AcceleratedVisual));
  ASSERT_EQ(SDL_GL_RETAINED_BACKING, ToUnderlying(Attr::RetainedBacking));

  ASSERT_EQ(SDL_GL_CONTEXT_MAJOR_VERSION, ToUnderlying(Attr::ContextMajorVersion));
  ASSERT_EQ(SDL_GL_CONTEXT_MINOR_VERSION, ToUnderlying(Attr::ContextMinorVersion));
  ASSERT_EQ(SDL_GL_CONTEXT_PROFILE_MASK, ToUnderlying(Attr::ContextProfileMask));
  ASSERT_EQ(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, ToUnderlying(Attr::ContextReleaseBehavior));
  ASSERT_EQ(SDL_GL_CONTEXT_RESET_NOTIFICATION, ToUnderlying(Attr::ContextResetNotification));
  ASSERT_EQ(SDL_GL_CONTEXT_NO_ERROR, ToUnderlying(Attr::ContextNoError));
  ASSERT_EQ(SDL_GL_CONTEXT_EGL, ToUnderlying(Attr::EGL));
  ASSERT_EQ(SDL_GL_CONTEXT_FLAGS, ToUnderlying(Attr::ContextFlags));

  ASSERT_EQ(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, ToUnderlying(Attr::ShareWithCurrentContext));
  ASSERT_EQ(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, ToUnderlying(Attr::FramebufferSRGBCapable));
}

TEST(GLAttribute, ToString)
{
  ASSERT_EQ("RedSize", to_string(Attr::RedSize));
  ASSERT_EQ("GreenSize", to_string(Attr::GreenSize));
  ASSERT_EQ("BlueSize", to_string(Attr::BlueSize));
  ASSERT_EQ("AlphaSize", to_string(Attr::AlphaSize));
  ASSERT_EQ("BufferSize", to_string(Attr::BufferSize));

  ASSERT_EQ("DoubleBuffer", to_string(Attr::DoubleBuffer));

  ASSERT_EQ("DepthSize", to_string(Attr::DepthSize));
  ASSERT_EQ("StencilSize", to_string(Attr::StencilSize));

  ASSERT_EQ("AccumRedSize", to_string(Attr::AccumRedSize));
  ASSERT_EQ("AccumGreenSize", to_string(Attr::AccumGreenSize));
  ASSERT_EQ("AccumBlueSize", to_string(Attr::AccumBlueSize));
  ASSERT_EQ("AccumAlphaSize", to_string(Attr::AccumAlphaSize));

  ASSERT_EQ("Stereo", to_string(Attr::Stereo));
  ASSERT_EQ("MultisampleBuffers", to_string(Attr::MultisampleBuffers));
  ASSERT_EQ("MultisampleSamples", to_string(Attr::MultisampleSamples));
  ASSERT_EQ("AcceleratedVisual", to_string(Attr::AcceleratedVisual));
  ASSERT_EQ("RetainedBacking", to_string(Attr::RetainedBacking));

  ASSERT_EQ("ContextMajorVersion", to_string(Attr::ContextMajorVersion));
  ASSERT_EQ("ContextMinorVersion", to_string(Attr::ContextMinorVersion));
  ASSERT_EQ("ContextProfileMask", to_string(Attr::ContextProfileMask));
  ASSERT_EQ("ContextReleaseBehavior", to_string(Attr::ContextReleaseBehavior));
  ASSERT_EQ("ContextResetNotification", to_string(Attr::ContextResetNotification));
  ASSERT_EQ("ContextNoError", to_string(Attr::ContextNoError));

  ASSERT_EQ("EGL", to_string(Attr::EGL));
  ASSERT_EQ("ContextFlags", to_string(Attr::ContextFlags));

  ASSERT_EQ("ShareWithCurrentContext", to_string(Attr::ShareWithCurrentContext));
  ASSERT_EQ("FramebufferSRGBCapable", to_string(Attr::FramebufferSRGBCapable));

  std::clog << "OpenGL attribute example: " << Attr::DoubleBuffer << '\n';
}
