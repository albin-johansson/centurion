#pragma once
#include "centurion.h"

namespace centurion::audio {
class Jukebox {
 private:
  Jukebox() = delete;

 public:
  ~Jukebox() = default;

  static void PlayMusic();

  static void PauseMusic();

  static void StopMusic();

  static void SetVolume(int volume);
};
}  // namespace centurion::audio
// class centurion::audio::Jukebox {
// private:
//  Jukebox() = delete;
//
// public:
//  ~Jukebox() = default;
//
//  static void PlayMusic();
//
//  static void PauseMusic();
//
//  static void StopMusic();
//
//  static void SetVolume(int volume);
//};
