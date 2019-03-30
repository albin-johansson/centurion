#pragma once
#include <string>

namespace centurion {

class Centurion;  // TODO rename
class Window;
class Font;

namespace events {
class Action;
class KeyListener;
class KeyStroke;
}  // namespace events

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
