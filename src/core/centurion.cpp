#include "centurion.hpp"

#include "exception.hpp"

namespace cen {

library::library()
{
  init();
}

library::library(const config& cfg) : m_cfg{cfg}
{
  init();
}

void library::init()
{
  if (m_cfg.initCore) {
    m_sdl.emplace(m_cfg.coreFlags);
  }

  if (m_cfg.initImage) {
    m_img.emplace(m_cfg.imageFlags);
  }

  if (m_cfg.initTTF) {
    m_ttf.emplace();
  }

  if (m_cfg.initMixer) {
    m_mixer.emplace(m_cfg.mixerFlags,
                    m_cfg.mixerFreq,
                    m_cfg.mixerFormat,
                    m_cfg.mixerChannels,
                    m_cfg.mixerChunkSize);
  }
}

library::sdl::sdl(u32 flags)
{
  const auto result = SDL_Init(flags);
  if (result < 0) {
    throw sdl_error{"Failed to initialize SDL2"};
  }
}

library::sdl::~sdl() noexcept
{
  SDL_Quit();
}

library::sdl_ttf::sdl_ttf()
{
  const auto result = TTF_Init();
  if (result == -1) {
    throw ttf_error{"Failed to initialize SDL2_ttf"};
  }
}

library::sdl_ttf::~sdl_ttf() noexcept
{
  TTF_Quit();
}

library::sdl_mixer::sdl_mixer(int flags,
                              int freq,
                              u16 format,
                              int nChannels,
                              int chunkSize)
{
  if (!Mix_Init(flags)) {
    throw mix_error{"Failed to initialize SDL2_mixer"};
  }

  if (Mix_OpenAudio(freq, format, nChannels, chunkSize) == -1) {
    throw mix_error{"Failed to open audio"};
  }
}

library::sdl_mixer::~sdl_mixer() noexcept
{
  Mix_CloseAudio();
  Mix_Quit();
}

library::sdl_image::sdl_image(int flags)
{
  if (!IMG_Init(flags)) {
    throw img_error{"Failed to initialize SDL2_image"};
  }
}

library::sdl_image::~sdl_image() noexcept
{
  IMG_Quit();
}

}  // namespace cen
