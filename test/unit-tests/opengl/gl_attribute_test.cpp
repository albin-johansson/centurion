#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "opengl.hpp"

using Attr = cen::GLAttribute;

TEST(GLAttribute, Values)
{
  ASSERT_EQ(SDL_GL_RED_SIZE, to_underlying(Attr::RedSize));
  ASSERT_EQ(SDL_GL_GREEN_SIZE, to_underlying(Attr::GreenSize));
  ASSERT_EQ(SDL_GL_BLUE_SIZE, to_underlying(Attr::BlueSize));
  ASSERT_EQ(SDL_GL_ALPHA_SIZE, to_underlying(Attr::AlphaSize));
  ASSERT_EQ(SDL_GL_BUFFER_SIZE, to_underlying(Attr::BufferSize));

  ASSERT_EQ(SDL_GL_DOUBLEBUFFER, to_underlying(Attr::DoubleBuffer));

  ASSERT_EQ(SDL_GL_DEPTH_SIZE, to_underlying(Attr::DepthSize));
  ASSERT_EQ(SDL_GL_STENCIL_SIZE, to_underlying(Attr::StencilSize));

  ASSERT_EQ(SDL_GL_ACCUM_RED_SIZE, to_underlying(Attr::AccumRedSize));
  ASSERT_EQ(SDL_GL_ACCUM_GREEN_SIZE, to_underlying(Attr::AccumGreenSize));
  ASSERT_EQ(SDL_GL_ACCUM_BLUE_SIZE, to_underlying(Attr::AccumBlueSize));
  ASSERT_EQ(SDL_GL_ACCUM_ALPHA_SIZE, to_underlying(Attr::AccumAlphaSize));

  ASSERT_EQ(SDL_GL_STEREO, to_underlying(Attr::Stereo));
  ASSERT_EQ(SDL_GL_MULTISAMPLEBUFFERS, to_underlying(Attr::MultisampleBuffers));
  ASSERT_EQ(SDL_GL_MULTISAMPLESAMPLES, to_underlying(Attr::MultisampleSamples));
  ASSERT_EQ(SDL_GL_ACCELERATED_VISUAL, to_underlying(Attr::AcceleratedVisual));
  ASSERT_EQ(SDL_GL_RETAINED_BACKING, to_underlying(Attr::RetainedBacking));

  ASSERT_EQ(SDL_GL_CONTEXT_MAJOR_VERSION, to_underlying(Attr::ContextMajorVersion));
  ASSERT_EQ(SDL_GL_CONTEXT_MINOR_VERSION, to_underlying(Attr::ContextMinorVersion));
  ASSERT_EQ(SDL_GL_CONTEXT_PROFILE_MASK, to_underlying(Attr::ContextProfileMask));
  ASSERT_EQ(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, to_underlying(Attr::ContextReleaseBehavior));
  ASSERT_EQ(SDL_GL_CONTEXT_RESET_NOTIFICATION, to_underlying(Attr::ContextResetNotification));
  ASSERT_EQ(SDL_GL_CONTEXT_NO_ERROR, to_underlying(Attr::ContextNoError));
  ASSERT_EQ(SDL_GL_CONTEXT_EGL, to_underlying(Attr::EGL));
  ASSERT_EQ(SDL_GL_CONTEXT_FLAGS, to_underlying(Attr::ContextFlags));

  ASSERT_EQ(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, to_underlying(Attr::ShareWithCurrentContext));
  ASSERT_EQ(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, to_underlying(Attr::FramebufferSRGBCapable));
}

TEST(GLAttribute, ToString)
{
  ASSERT_EQ("RedSize", ToString(Attr::RedSize));
  ASSERT_EQ("GreenSize", ToString(Attr::GreenSize));
  ASSERT_EQ("BlueSize", ToString(Attr::BlueSize));
  ASSERT_EQ("AlphaSize", ToString(Attr::AlphaSize));
  ASSERT_EQ("BufferSize", ToString(Attr::BufferSize));

  ASSERT_EQ("DoubleBuffer", ToString(Attr::DoubleBuffer));

  ASSERT_EQ("DepthSize", ToString(Attr::DepthSize));
  ASSERT_EQ("StencilSize", ToString(Attr::StencilSize));

  ASSERT_EQ("AccumRedSize", ToString(Attr::AccumRedSize));
  ASSERT_EQ("AccumGreenSize", ToString(Attr::AccumGreenSize));
  ASSERT_EQ("AccumBlueSize", ToString(Attr::AccumBlueSize));
  ASSERT_EQ("AccumAlphaSize", ToString(Attr::AccumAlphaSize));

  ASSERT_EQ("Stereo", ToString(Attr::Stereo));
  ASSERT_EQ("MultisampleBuffers", ToString(Attr::MultisampleBuffers));
  ASSERT_EQ("MultisampleSamples", ToString(Attr::MultisampleSamples));
  ASSERT_EQ("AcceleratedVisual", ToString(Attr::AcceleratedVisual));
  ASSERT_EQ("RetainedBacking", ToString(Attr::RetainedBacking));

  ASSERT_EQ("ContextMajorVersion", ToString(Attr::ContextMajorVersion));
  ASSERT_EQ("ContextMinorVersion", ToString(Attr::ContextMinorVersion));
  ASSERT_EQ("ContextProfileMask", ToString(Attr::ContextProfileMask));
  ASSERT_EQ("ContextReleaseBehavior", ToString(Attr::ContextReleaseBehavior));
  ASSERT_EQ("ContextResetNotification", ToString(Attr::ContextResetNotification));
  ASSERT_EQ("ContextNoError", ToString(Attr::ContextNoError));

  ASSERT_EQ("EGL", ToString(Attr::EGL));
  ASSERT_EQ("ContextFlags", ToString(Attr::ContextFlags));

  ASSERT_EQ("ShareWithCurrentContext", ToString(Attr::ShareWithCurrentContext));
  ASSERT_EQ("FramebufferSRGBCapable", ToString(Attr::FramebufferSRGBCapable));

  std::clog << "OpenGL attribute example: " << Attr::DoubleBuffer << '\n';
}
