# Centurion roadmap

This document illustrates what aspects of the SDL2 API that is currently covered by the Centurion library.

---

## Basics

### Initialization and shutdown

Covered by the `Centurion` class located in `centurion.h`.

- [X] SDL_Init
- [X] SDL_InitSubSystem
- [X] SDL_Quit
- [X] SDL_QuitSubSystem
- [ ] SDL_SetMainReady
- [ ] SDL_WasInit
- [ ] SDL_WinRTRunApp

### Configuration variables

Not covered.

### Error handling

Not exposed publicly (see `detail::Error` in `error.h`), but SDL error messages are used when Centurion throws exceptions.

### Log handling

Handled solely by the `Log` class. All categories and priorities are supported. The logging API is located in the `log.h` header.

### Assertions

Not covered.

### Querying SDL version

Not covered for all SDL2 libraries. The `Font` class has the `ttf_version()` method which returns the SDL2_ttf version.

---

## Video

### Display and window management

### 2D Accelerated rendering

Covered in `renderer.h`, `texture.h`, `blend_mode.h`.

- [ ] `SDL_ComposeCustomBlendMode`
- [X] `SDL_CreateRenderer`
- [ ] `SDL_CreateSoftwareRenderer`
- [X] `SDL_CreateTexture`
- [X] `SDL_CreateTextureFromSurface`
- [ ] `SDL_CreateWindowAndRenderer`
- [ ] `SDL_GL_BindTexture`
- [ ] `SDL_GL_UnbindTexture`
- [X] `SDL_GetNumRenderDrivers`
- [X] `SDL_GetRenderDrawBlendMode`
- [X] `SDL_GetRenderDrawColor`
- [X] `SDL_GetRenderDriverInfo`
- [ ] `SDL_GetRenderTarget`
- [X] `SDL_GetRenderer`
- [X] `SDL_GetRendererInfo`
- [X] `SDL_GetRendererOutputSize`
- [X] `SDL_GetTextureAlphaMod`
- [X] `SDL_GetTextureBlendMode`
- [X] `SDL_GetTextureColorMod`
- [ ] `SDL_LockTexture`
- [ ] `SDL_QueryTexture`
- [X] `SDL_RenderClear`
- [X] `SDL_RenderCopy`
- [X] `SDL_RenderCopyEx`
- [X] `SDL_RenderCopyF`
- [X] `SDL_RenderCopyExF`
- [X] `SDL_RenderDrawLine`
- [X] `SDL_RenderDrawLines`
- [ ] `SDL_RenderDrawPoint`
- [ ] `SDL_RenderDrawPoints`
- [X] `SDL_RenderDrawRect`
- [ ] `SDL_RenderDrawRects`
- [X] `SDL_RenderFillRect`
- [ ] `SDL_RenderFillRects`
- [X] `SDL_RenderGetClipRect`
- [X] `SDL_RenderGetIntegerScale`
- [X] `SDL_RenderGetLogicalSize`
- [X] `SDL_RenderGetScale`
- [X] `SDL_RenderGetViewport`
- [X] `SDL_RenderIsClipEnabled`
- [X] `SDL_RenderPresent`
- [ ] `SDL_RenderReadPixels`
- [X] `SDL_RenderSetClipRect`
- [X] `SDL_RenderSetIntegerScale`
- [X] `SDL_RenderSetLogicalSize`
- [X] `SDL_RenderSetScale`
- [X] `SDL_RenderSetViewport`
- [X] `SDL_RenderTargetSupported`
- [X] `SDL_SetRenderDrawBlendMode`
- [X] `SDL_SetRenderDrawColor`
- [X] `SDL_SetRenderTarget`
- [X] `SDL_SetTextureAlphaMod`
- [X] `SDL_SetTextureBlendMode`
- [X] `SDL_SetTextureColorMod`
- [ ] `SDL_UnlockTexture`
- [ ] `SDL_UpdateTexture`
- [ ] `SDL_UpdateYUVTexture`

### Pixel formats and conversion routines

### Rectangle functions

### Surface creation and simple drawing

### Platform-specific window managment

Not covered.

### Clipboard handling

Not covered.

### Vulkan support

Not covered.

---

## Input events

### Event handling

### Keyboard support

Keyboard support is provided through events and through raw key state, see `key_state.h`.

- [X] `SDL_GetKeyFromName`
- [X] `SDL_GetKeyFromScancode`
- [ ] `SDL_GetKeyName` (available indirectly in `Key` class)
- [ ] `SDL_GetKeyboardFocus`
- [X] `SDL_GetKeyboardState`
- [X] `SDL_GetModState`
- [X] `SDL_GetScancodeFromKey`
- [X] `SDL_GetScancodeFromName`
- [X] `SDL_GetScancodeName`
- [ ] `SDL_HasScreenKeyboardSupport`
- [ ] `SDL_IsScreenKeyboardShown`
- [ ] `SDL_IsTextInputActive`
- [ ] `SDL_SetModState`
- [ ] `SDL_SetTextInputRect`
- [ ] `SDL_StartTextInput`
- [ ] `SDL_StopTextInput`

### Mouse support

Available through events and by checking the mouse state. Mouse state API is covered in `mouse_state.h`. The SDL2 cursor API is covered the `Cursor` class, located in `cursor.h`. Additional mouse stuff that is related to windows is handled by the `Window` class.

- [X] `SDL_CaptureMouse`
- [X] `SDL_CreateColorCursor`
- [X] `SDL_CreateCursor`
- [X] `SDL_CreateSystemCursor`
- [ ] `SDL_GetCursor`
- [X] `SDL_GetDefaultCursor`
- [ ] `SDL_GetGlobalMouseState`
- [ ] `SDL_GetMouseFocus`
- [X] `SDL_GetMouseState`
- [ ] `SDL_GetRelativeMouseMode`
- [ ] `SDL_GetRelativeMouseState`
- [X] `SDL_SetCursor`
- [ ] `SDL_SetRelativeMouseMode`
- [X] `SDL_ShowCursor`
- [ ] `SDL_WarpMouseGlobal`
- [ ] `SDL_WarpMouseInWindow`

### Joystick support

Not covered, planned to be added soon.

### Game controller support

Not covered, planned to be added soon.

### Sensors

Not covered.

---

## Force feedback

---

## Audio

The core SDL2 audio API is not covered at all. Instead, the SDL2_mixer API is used. See `sound_effect.h` and `music.h`.

---

## Threads

There are **no** plans for thread support in Centurion, as that is available in the C++ standard library.

---

## Timers

Handled in the `timer.h`.

- [ ] `SDL_AddTimer`
- [X] `SDL_Delay`
- [X] `SDL_GetPerformanceCounter`
- [X] `SDL_GetPerformanceFrequency`
- [X] `SDL_GetTicks`
- [ ] `SDL_RemoveTimer`

---

## File abstraction

This will not be added to Centurion, this is also better handled throught the C++ standard library.

---

## Shared object support

---

## Platform and CPU information
