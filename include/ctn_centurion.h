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
  static bool isInit;

  Centurion() = delete;

  static void InitCore();

  static void InitSDLImage();

  static void InitSDLTTF();

  static void InitSDLMixer();

  static void ThrowInitializationException(const std::string error);

 public:
  ~Centurion() = default;

  /**
  \brief Initializes the Centurion library. This method MUST be called before
  using ANY other Centurion component.
  \since 1.0.0
  */
  static void Init();

  /**
  \brief Closes the Centurion library.
  \since 1.0.0
  */
  static void Close() noexcept;

  /**
  \brief Returns true if the library is initialized, returns false otherwise.
  \since 1.0.0
  */
  inline static bool IsInitialized() noexcept { return isInit; }
};

}  // namespace centurion