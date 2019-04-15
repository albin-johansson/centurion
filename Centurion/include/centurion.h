#pragma once
#include <string>

namespace centurion {

/**
\brief The Centurion class is responsible for the initialization and
deinitialization of the Centurion library.
\since 1.0.0
*/
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

  /**
  \brief Initializes the Centurion library. This method MUST be called before
  using ANY other Centurion components.
  */
  static void Init();

  /**
  \brief Closes the Centurion library.
  */
  static void Close();

  /**
  \brief Indicates whether or not the Centurion library is initialized or not.
  Returns true if the library is initialized, false otherwise.
  */
  inline static bool IsInitialized() { return initialized; }
};

}  // namespace centurion