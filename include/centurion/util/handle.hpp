// Copyright (C) 2025 Albin Johansson

#pragma once

#include <type_traits>
#include <utility>

#include <SDL3/SDL.h>
#include <centurion/util/common.hpp>

namespace cen {

/// \addtogroup Handle
/// \{

/// Provides resource handle ownership modes.
enum class HandleMode : u8
{
  /// The handle is owning, and will release the associated resource upon destruction.
  kOwning,

  /// The handle is non-owning, no cleanup is performed upon destruction.
  kNonOwning,
};

/// Deleter for a handle to a generic SDL resource.
///
/// This is the primary specialization, it's intentionally not defined.
///
/// \tparam HandleType The handle type, usually a pointer to an opaque struct.
///
/// \see cen::Handle
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

/// A (possibly owning) handle to an SDL resource.
///
/// This is an RAII type that can act as a `std::unique_ptr` for SDL handles. Similarly,
/// this type has shallow constness, i.e., it's possible to get a non-const handle from a
/// const `Handle`. Null handles are valid. Handles have owning semantics by default.
///
/// When using `cen::HandleMode::kOwning`, this class is basically all you need if you
/// just want improved memory safety compared to using the SDL C API directly. However,
/// there are no handle specific member functions when using this class directly.
/// Dedicated types such as `cen::Window` can be used instead if you're looking for a more
/// convenient C++ API.
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
/// Here's an example of how you could use `Handle` with the SDL APIs directly.
/// \code{cpp}
/// cen::Handle window {SDL_CreateWindow("Demo", 800, 600, 0)};
/// if (window.get() != nullptr) {
///   // ...
/// }
/// \endcode
///
/// \tparam HandleType The handle type.
///
/// \see cen::GpuHandle
/// \see cen::HandleDeleter
template <typename HandleType>
  requires std::is_pointer_v<HandleType>
class Handle final
{
 public:
  /// Creates a handle.
  ///
  /// \param[in] handle The associated handle.
  /// \param[in] mode   The handle ownership mode to use.
  [[nodiscard]]
  explicit Handle(const HandleType handle = nullptr,
                  const HandleMode mode = HandleMode::kOwning) noexcept :
    mHandle {handle},
    mMode {mode}
  {}

  /// Move constructor.
  ///
  /// \param[in] other The handle to move from.
  Handle(Handle&& other) noexcept :
    mHandle {std::exchange(other.mHandle, nullptr)},
    mMode {other.mMode}
  {}

  /// Deleted copy constructor.
  Handle(const Handle&) = delete;

  /// Move assignment operator.
  ///
  /// \param[in] other The handle to move from.
  ///
  /// \returns
  /// A reference to the assigned object.
  auto operator=(Handle&& other) noexcept -> Handle&
  {
    std::swap(mHandle, other.mHandle);
    std::swap(mMode, other.mMode);
    return *this;
  }

  /// Deleted copy assignment operator.
  auto operator=(const Handle&) -> Handle& = delete;

  /// Destroys the handle if its owning and not null.
  ~Handle() noexcept
  {
    if (mMode == HandleMode::kOwning && mHandle != nullptr) {
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

  /// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode
  {
    return mMode;
  }

 private:
  HandleType mHandle;
  HandleMode mMode;
};

/// Deleter for a handle to an SDL GPU resource.
///
/// This is the primary specialization, it's intentionally not defined.
///
/// \tparam HandleType The handle type, usually a pointer to an opaque struct.
///
/// \see cen::GpuHandle
/// \see cen::HandleDeleter
template <typename HandleType>
class GpuHandleDeleter;

/// Deleter for `SDL_GPUShader*`.
template <>
class GpuHandleDeleter<SDL_GPUShader*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUShader* handle) noexcept
  {
    SDL_ReleaseGPUShader(device, handle);
  }
};

/// Deleter for `SDL_GPUBuffer*`.
template <>
class GpuHandleDeleter<SDL_GPUBuffer*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUBuffer* handle) noexcept
  {
    SDL_ReleaseGPUBuffer(device, handle);
  }
};

/// Deleter for `SDL_GPUTransferBuffer*`.
template <>
class GpuHandleDeleter<SDL_GPUTransferBuffer*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUTransferBuffer* handle) noexcept
  {
    SDL_ReleaseGPUTransferBuffer(device, handle);
  }
};

/// Deleter for `SDL_GPUSampler*`.
template <>
class GpuHandleDeleter<SDL_GPUSampler*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUSampler* handle) noexcept
  {
    SDL_ReleaseGPUSampler(device, handle);
  }
};

/// Deleter for `SDL_GPUTexture*`.
template <>
class GpuHandleDeleter<SDL_GPUTexture*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUTexture* handle) noexcept
  {
    SDL_ReleaseGPUTexture(device, handle);
  }
};

/// Deleter for `SDL_GPUGraphicsPipeline*`.
template <>
class GpuHandleDeleter<SDL_GPUGraphicsPipeline*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUGraphicsPipeline* handle) noexcept
  {
    SDL_ReleaseGPUGraphicsPipeline(device, handle);
  }
};

/// Deleter for `SDL_GPUComputePipeline*`.
template <>
class GpuHandleDeleter<SDL_GPUComputePipeline*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUComputePipeline* handle) noexcept
  {
    SDL_ReleaseGPUComputePipeline(device, handle);
  }
};

/// Deleter for `SDL_GPUFence*`.
template <>
class GpuHandleDeleter<SDL_GPUFence*> final
{
 public:
  static void destroy(SDL_GPUDevice* device, SDL_GPUFence* handle) noexcept
  {
    SDL_ReleaseGPUFence(device, handle);
  }
};

/// A (possibly owning) handle to an SDL GPU resource.
///
/// This is the GPU version of `cen::Handle`, refer to its documentation for more details.
///
/// The currently supported handle types are:
/// - `SDL_GPUShader*`
/// - `SDL_GPUBuffer*`
/// - `SDL_GPUTransferBuffer*`
/// - `SDL_GPUSampler*`
/// - `SDL_GPUTexture*`
/// - `SDL_GPUGraphicsPipeline*`
/// - `SDL_GPUComputePipeline*`
/// - `SDL_GPUFence*`
///
/// \tparam HandleType The handle type.
///
/// \see cen::Handle
/// \see cen::GpuHandleDeleter
template <typename HandleType>
  requires std::is_pointer_v<HandleType>
class GpuHandle final
{
 public:
  /// Creates a null owning handle.
  GpuHandle() noexcept = default;

  /// Creates a GPU handle.
  ///
  /// \param[inout] device A device handle.
  /// \param[in]    handle A resource handle.
  /// \param[in]    mode   The handle mode to use.
  GpuHandle(SDL_GPUDevice* device,
            const HandleType handle,
            const HandleMode mode) noexcept :
    mDevice {device},
    mHandle {handle},
    mMode {mode}
  {}

  /// Move constructor.
  ///
  /// \param[in] other The handle to move from.
  GpuHandle(GpuHandle&& other) noexcept :
    mDevice {std::exchange(other.mDevice, nullptr)},
    mHandle {std::exchange(other.mHandle, nullptr)},
    mMode {other.mMode}
  {}

  /// Deleted copy constructor.
  GpuHandle(const GpuHandle&) = delete;

  /// Move assignment operator.
  ///
  /// \param[in] other The handle to move from.
  ///
  /// \returns
  /// A reference to the assigned object.
  auto operator=(GpuHandle&& other) noexcept -> GpuHandle&
  {
    std::swap(mDevice, other.mDevice);
    std::swap(mHandle, other.mHandle);
    std::swap(mMode, other.mMode);
    return *this;
  }

  /// Deleted copy assignment operator.
  auto operator=(const GpuHandle&) -> GpuHandle& = delete;

  /// Destroys the handle if it's owning and not null.
  ~GpuHandle() noexcept
  {
    if (mMode == HandleMode::kOwning && mDevice != nullptr && mHandle != nullptr) {
      GpuHandleDeleter<HandleType>::destroy(mDevice, mHandle);
      mHandle = nullptr;
    }
  }

  /// Returns the associated device handle.
  ///
  /// \return
  /// A possibly null device handle.
  [[nodiscard]]
  auto device() const noexcept -> SDL_GPUDevice*
  {
    return mDevice;
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

  /// Returns the associated handle mode.
  ///
  /// \return
  /// A handle mode.
  [[nodiscard]]
  auto mode() const noexcept -> HandleMode
  {
    return mHandle;
  }

 private:
  SDL_GPUDevice* mDevice {nullptr};
  HandleType mHandle {nullptr};
  HandleMode mMode {HandleMode::kOwning};
};

/// \}

}  // namespace cen
