#pragma once

namespace centurion {
class Centurion;  // TODO rename
class Window;
class Screen;
class Font;

class Positionable;
class Dimensioned;

namespace events {
class Action;
class KeyListener;
class KeyStroke;
}  // namespace events

namespace visuals {
class Renderer;
class Texture;
class TextureFactory;

class Color;
class Drawable;
}  // namespace visuals

namespace geo {
class Rectangle;
class Point;
}  // namespace geo

namespace tools {
class BooleanConverter;
class NullChecker;
}  // namespace tools
}  // namespace centurion

class centurion::Centurion final {
 private:
  static bool initialized;

  Centurion() = delete;

 public:
  ~Centurion() = default;

  static void Init();

  static void Close();

  static bool IsInitialized();
};
