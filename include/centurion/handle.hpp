// Copyright (C) 2025 Albin Johansson

#pragma once

#include <utility>

#include <SDL3/SDL.h>

namespace cen {

/// \addtogroup Handle
/// \{

/// Deleter for a handle to an SDL resource.
///
/// This is the primary specialization, it's intentionally not defined.
///
/// \tparam HandleType The handle type, usually a pointer to an opaque struct.
///
/// \see cen::UniqueHandle
template <typename HandleType>
class HandleDeleter;

/// Deleter for `SDL_AsyncIOQueue*`.
template <>
class HandleDeleter<SDL_AsyncIOQueue*> final
{
 public:
  static void destroy(SDL_AsyncIOQueue* handle) noexcept
  {
    SDL_DestroyAsyncIOQueue(handle);
  }
};

/// Deleter for `SDL_AudioStream*`.
template <>
class HandleDeleter<SDL_AudioStream*> final
{
 public:
  static void destroy(SDL_AudioStream* handle) noexcept
  {
    SDL_DestroyAudioStream(handle);
  }
};

/// Deleter for `SDL_Condition*`.
template <>
class HandleDeleter<SDL_Condition*> final
{
 public:
  static void destroy(SDL_Condition* handle) noexcept
  {
    SDL_DestroyCondition(handle);
  }
};

/// Deleter for `SDL_Cursor*`.
template <>
class HandleDeleter<SDL_Cursor*> final
{
 public:
  static void destroy(SDL_Cursor* handle) noexcept
  {
    SDL_DestroyCursor(handle);
  }
};

/// Deleter for `SDL_Environment*`.
template <>
class HandleDeleter<SDL_Environment*> final
{
 public:
  static void destroy(SDL_Environment* handle) noexcept
  {
    SDL_DestroyEnvironment(handle);
  }
};

/// Deleter for `SDL_GPUComputePass*`.
template <>
class HandleDeleter<SDL_GPUComputePass*> final
{
 public:
  static void destroy(SDL_GPUComputePass* handle) noexcept
  {
    SDL_EndGPUComputePass(handle);
  }
};

/// Deleter for `SDL_GPUCopyPass*`.
template <>
class HandleDeleter<SDL_GPUCopyPass*> final
{
 public:
  static void destroy(SDL_GPUCopyPass* handle) noexcept
  {
    SDL_EndGPUCopyPass(handle);
  }
};

/// Deleter for `SDL_GPUDevice*`.
template <>
class HandleDeleter<SDL_GPUDevice*> final
{
 public:
  static void destroy(SDL_GPUDevice* handle) noexcept
  {
    SDL_DestroyGPUDevice(handle);
  }
};

/// Deleter for `SDL_GPURenderPass*`.
template <>
class HandleDeleter<SDL_GPURenderPass*> final
{
 public:
  static void destroy(SDL_GPURenderPass* handle) noexcept
  {
    SDL_EndGPURenderPass(handle);
  }
};

/// Deleter for `SDL_Mutex*`.
template <>
class HandleDeleter<SDL_Mutex*> final
{
 public:
  static void destroy(SDL_Mutex* handle) noexcept
  {
    SDL_DestroyMutex(handle);
  }
};

/// Deleter for `SDL_Palette*`.
template <>
class HandleDeleter<SDL_Palette*> final
{
 public:
  static void destroy(SDL_Palette* handle) noexcept
  {
    SDL_DestroyPalette(handle);
  }
};

/// Deleter for `SDL_Process*`.
template <>
class HandleDeleter<SDL_Process*> final
{
 public:
  static void destroy(SDL_Process* handle) noexcept
  {
    SDL_DestroyProcess(handle);
  }
};

/// Deleter for `SDL_Renderer*`.
template <>
class HandleDeleter<SDL_Renderer*> final
{
 public:
  static void destroy(SDL_Renderer* handle) noexcept
  {
    SDL_DestroyRenderer(handle);
  }
};

/// Deleter for `SDL_RWLock*`.
template <>
class HandleDeleter<SDL_RWLock*> final
{
 public:
  static void destroy(SDL_RWLock* handle) noexcept
  {
    SDL_DestroyRWLock(handle);
  }
};

/// Deleter for `SDL_Semaphore*`.
template <>
class HandleDeleter<SDL_Semaphore*> final
{
 public:
  static void destroy(SDL_Semaphore* handle) noexcept
  {
    SDL_DestroySemaphore(handle);
  }
};

/// Deleter for `SDL_Surface*`.
template <>
class HandleDeleter<SDL_Surface*> final
{
 public:
  static void destroy(SDL_Surface* handle) noexcept
  {
    SDL_DestroySurface(handle);
  }
};

/// Deleter for `SDL_Texture*`.
template <>
class HandleDeleter<SDL_Texture*> final
{
 public:
  static void destroy(SDL_Texture* handle) noexcept
  {
    SDL_DestroyTexture(handle);
  }
};

/// Deleter for `SDL_Tray*`.
template <>
class HandleDeleter<SDL_Tray*> final
{
 public:
  static void destroy(SDL_Tray* handle) noexcept
  {
    SDL_DestroyTray(handle);
  }
};

/// Deleter for `SDL_Window*`.
template <>
class HandleDeleter<SDL_Window*> final
{
 public:
  static void destroy(SDL_Window* handle) noexcept
  {
    SDL_DestroyWindow(handle);
  }
};

/// A unique handle to an SDL resource.
///
/// This is an RAII type that acts as a `std::unique_ptr` for SDL handles. Similarly, this
/// type has shallow constness, i.e., it's possible to get a non-const handle from a const
/// `UniqueHandle`. Null handles are valid.
///
/// This class is basically all you need if you just want improved memory safety compared
/// to using the SDL C API directly. However, there are no handle specific member
/// functions when using this class directly. Dedicated types such as `cen::Window` can be
/// used instead if you're looking for more C++-esque APIs.
///
/// The currently supported handle types are:
/// - `SDL_AsyncIOQueue*`
/// - `SDL_AudioStream*`
/// - `SDL_Condition*`
/// - `SDL_Cursor*`
/// - `SDL_Environment*`
/// - `SDL_GPUComputePass*`
/// - `SDL_GPUCopyPass*`
/// - `SDL_GPUDevice*`
/// - `SDL_GPURenderPass*`
/// - `SDL_Mutex*`
/// - `SDL_Palette*`
/// - `SDL_Process*`
/// - `SDL_Renderer*`
/// - `SDL_RWLock*`
/// - `SDL_Semaphore*`
/// - `SDL_Surface*`
/// - `SDL_Texture*`
/// - `SDL_Tray*`
/// - `SDL_Window*`
///
/// Here's an example of how you could use `UniqueHandle` with the SDL APIs directly.
/// \code{cpp}
/// cen::UniqueHandle window {SDL_CreateWindow("Demo", 800, 600, 0)};
/// if (window.get() != nullptr) {
///   // ...
/// }
/// \endcode
///
/// \tparam HandleType The handle type, usually a pointer to an opaque struct.
template <typename HandleType>
class UniqueHandle final
{
 public:
  /// Creates a unique handle.
  ///
  /// \param[in] handle The handle to claim ownership of.
  [[nodiscard]]
  explicit UniqueHandle(HandleType handle = nullptr) noexcept
    : mHandle {handle}
  {}

  /// Move constructor.
  ///
  /// \param[in] other The handle to move from.
  UniqueHandle(UniqueHandle&& other) noexcept
    : mHandle {std::exchange(other.mHandle)}
  {}

  /// Deleted copy constructor.
  UniqueHandle(const UniqueHandle&) = delete;

  /// Move assignment operator.
  ///
  /// \param[in] other The handle to move from.
  ///
  /// \returns
  /// A reference to the assigned object.
  auto operator=(UniqueHandle&& other) noexcept -> UniqueHandle&
  {
    std::swap(mHandle, other.mHandle);
    return *this;
  }

  /// Deleted copy assignment operator.
  auto operator=(const UniqueHandle&) -> UniqueHandle& = delete;

  /// Destroys the handle if it's not null.
  ~UniqueHandle() noexcept
  {
    if (mHandle != nullptr) {
      HandleDeleter<HandleType>::destroy(mHandle);
      mHandle = nullptr;
    }
  }

  /// Returns the associated handle.
  ///
  /// \return
  /// A possibly null handle.
  [[nodiscard]]
  auto get() const noexcept -> HandleType
  {
    return mHandle;
  }

 private:
  HandleType mHandle;
};

/// \}

}  // namespace cen
