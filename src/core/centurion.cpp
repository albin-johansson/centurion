#include "centurion.hpp"

#include "centurion_exception.hpp"

namespace centurion {

centurion_lib::centurion_lib()
{
  init();
}

centurion_lib::centurion_lib(const centurion_config& cfg) : m_cfg{cfg}
{
  init();
}

void centurion_lib::init()
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

auto ttf_version() noexcept -> SDL_version
{
  SDL_version version;
  SDL_TTF_VERSION(&version)
  return version;
}

centurion_lib::sdl::sdl(u32 flags)
{
  const auto result = SDL_Init(flags);
  if (result < 0) {
    throw sdl_error{"Failed to initialize SDL2!"};
  }
}

centurion_lib::sdl::~sdl() noexcept
{
  SDL_Quit();
}

centurion_lib::sdl_ttf::sdl_ttf()
{
  const auto result = TTF_Init();
  if (result == -1) {
    throw ttf_error{"Failed to initialize SDL2_ttf!"};
  }
}

centurion_lib::sdl_ttf::~sdl_ttf() noexcept
{
  TTF_Quit();
}

centurion_lib::sdl_mixer::sdl_mixer(int flags,
                                    int freq,
                                    u16 format,
                                    int nChannels,
                                    int chunkSize)
{
  if (!Mix_Init(flags)) {
    throw mix_error{"Failed to initialize SDL2_mixer!"};
  }

  if (Mix_OpenAudio(freq, format, nChannels, chunkSize) == -1) {
    throw mix_error{"Failed to open audio!"};
  }
}

centurion_lib::sdl_mixer::~sdl_mixer() noexcept
{
  Mix_CloseAudio();
  Mix_Quit();
}

centurion_lib::sdl_image::sdl_image(int flags)
{
  if (!IMG_Init(flags)) {
    throw img_error{"Failed to initialize SDL2_image!"};
  }
}

centurion_lib::sdl_image::~sdl_image() noexcept
{
  IMG_Quit();
}

}  // namespace centurion
