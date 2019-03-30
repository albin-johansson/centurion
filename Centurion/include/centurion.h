#pragma once
#include <string>

namespace centurion {
class Centurion;  // TODO rename

namespace events {
class Action;
class KeyListener;
class KeyStroke;
}  // namespace events

namespace visuals {
class Window;
class Renderer;
class Texture;
class TextureFactory;
class Font;
class Color;
class Drawable;
}  // namespace visuals

namespace audio {
class SoundEffect;
class Music;
//class Jukebox;
}  // namespace audio

namespace geo {
class Positionable;
class Dimensioned;
class Rectangle;
class Point;
}  // namespace geo

//namespace tools {
//class BooleanConverter;
//class NullChecker;
//class Screen;
//}  // namespace tools
}  // namespace centurion

class centurion::Centurion final {
 private:
  static bool initialized;

  Centurion() = delete;

  static void InitCore();

  static void InitSDLImage();

  static void InitSDLTTF();

  static void InitSDLMixer();

  static void ThrowInitializationException(const std::string& error);

 public:
  ~Centurion() = default;

  static void Init();

  static void Close();

  static bool IsInitialized() { return initialized; }
};
