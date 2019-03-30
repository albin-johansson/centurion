#pragma once
#include <string>

namespace centurion {

class Centurion final {
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

}  // namespace centurion