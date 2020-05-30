# Texture

The `Texture` class represents a hardware-accelerated image. This is the type used for all non-primitive rendering in the Centurion library.

## Table of contents

- [Texture](#texture)
  - [Table of contents](#table-of-contents)
  - [General information](#general-information)
  - [Construction and destruction](#construction-and-destruction)
    - [`Texture(Owner<SDL_Texture*>)`](#textureownersdl_texture)
    - [`Texture(const Renderer&, CZString)`](#textureconst-renderer-czstring)
    - [`Texture(const Renderer&, const Surface&)`](#textureconst-renderer-const-surface)
    - [`Texture(const Renderer&, PixelFormat, Access, IArea)`](#textureconst-renderer-pixelformat-access-iarea)
  - [Smart pointer factory methods](#smart-pointer-factory-methods)
    - [`Texture::unique(Owner<SDL_Texture*>)`](#textureuniqueownersdl_texture)
    - [`Texture::unique(const Renderer&, CZString)`](#textureuniqueconst-renderer-czstring)
    - [`Texture::unique(const Renderer&, const Surface&)`](#textureuniqueconst-renderer-const-surface)
    - [`Texture::unique(const Renderer&, PixelFormat, Access, IArea)`](#textureuniqueconst-renderer-pixelformat-access-iarea)
    - [`Texture::streaming(const Renderer&, CZString, PixelFormat)`](#texturestreamingconst-renderer-czstring-pixelformat)
    - [`Texture::shared(Owner<SDL_Texture*>)`](#texturesharedownersdl_texture)
    - [`Texture::shared(const Renderer&, CZString)`](#texturesharedconst-renderer-czstring)
    - [`Texture::shared(const Renderer&, const Surface&)`](#texturesharedconst-renderer-const-surface)
    - [`Texture::shared(const Renderer&, PixelFormat, Access, IArea)`](#texturesharedconst-renderer-pixelformat-access-iarea)
  - [Copying](#copying)
  - [Moving](#moving)
    - [`Texture(Texture&&)`](#texturetexture)
    - [`operator=(Texture&&)`](#operatortexture)
  - [Members](#members)
    - [Mutators](#mutators)
    - [Setters](#setters)
      - [`Texture::set_pixel(IPoint, const Color&)`](#textureset_pixelipoint-const-color)
      - [`Texture::set_alpha(Uint8)`](#textureset_alphauint8)
      - [`Texture::set_blend_mode(BlendMode)`](#textureset_blend_modeblendmode)
      - [`Texture::set_color_mod(Color)`](#textureset_color_modcolor)
      - [`Texture::set_scale_mod(ScaleMode)`](#textureset_scale_modscalemode)
    - [Getters](#getters)
      - [`Texture::format()`](#textureformat)
      - [`Texture::access()`](#textureaccess)
      - [`Texture::width()`](#texturewidth)
      - [`Texture::height()`](#textureheight)
      - [`Texture::size()`](#texturesize)
      - [`Texture::is_target()`](#textureis_target)
      - [`Texture::is_static()`](#textureis_static)
      - [`Texture::is_streaming()`](#textureis_streaming)
      - [`Texture::alpha()`](#texturealpha)
      - [`Texture::blend_mode()`](#textureblend_mode)
      - [`Texture::color_mod()`](#texturecolor_mod)
      - [`Texture::scale_mode()`](#texturescale_mode)
      - [`Texture::to_string()`](#textureto_string)
      - [`Texture::get()`](#textureget)
    - [Conversions](#conversions)
      - [`operator SDL_Texture*()`](#operator-sdl_texture)
      - [`operator const SDL_Texture*()`](#operator-const-sdl_texture)
  - [Overloaded operators](#overloaded-operators)

---

## General information

| Property              | Value                                |
| --------------------- | :----------------------------------- |
| Default constructible | No                                   |
| Movable               | Yes                                  |
| Copyable              | No                                   |
| Explicit conversions  | None                                 |
| Implicit conversions  | `SDL_Texture*`, `const SDL_Texture*` |
| Overloaded operators  | None                                 |
| Namespace             | `centurion`                          |
| Header                | `texture.h`                          |

---

## Construction and destruction

### `Texture(Owner<SDL_Texture*>)`

Creates a texture based on an existing SDL_Texture. The created Texture will claim ownership of the supplied texture.

- **`texture`** a pointer to the texture that will be claimed, can't be null.
- ***Throws*** `CenturionException` if the supplied pointer is null.
- ***Since*** `3.0.0`

```C++
explicit Texture(Owner<SDL_Texture*> texture);
```

---

### `Texture(const Renderer&, CZString)`

Creates a texture based on the image located at the specified file path.

- **`renderer`** the renderer that will be used to create the texture.
- **`path`** the file path of the image that will be loaded, mustn't be null.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `4.0.0`

```C++
Texture(const Renderer& renderer, CZString path);
```

---

### `Texture(const Renderer&, const Surface&)`

Creates a texture based on the supplied `Surface` instance.

- **`renderer`** the renderer that will be used to create the texture.
- **`surface`** the surface that the texture will be based on.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `4.0.0`

```C++
Texture(const Renderer& renderer, const Surface& surface);
```

---

### `Texture(const Renderer&, PixelFormat, Access, IArea)`

Creates a texture with the specified characteristics.

- **`renderer`** the renderer that will be used to create the texture.
- **`format`** the pixel format that will be used by the texture.
- **`access`** the texture access that will be used by the texture.
- **`size`** the size of the texture, components must be greater than zero.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `4.0.0`

```C++
Texture(const Renderer& renderer, PixelFormat format, Access access, IArea size);
```

---

## Smart pointer factory methods

### `Texture::unique(Owner<SDL_Texture*>)`

Creates and returns a unique pointer to a texture based on an existing SDL texture. The created texture will claim ownership of the supplied SDL texture.

- **`texture`** a pointer to the SDL texture that will be claimed, can't be null.
- ***Returns*** a unique pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the supplied pointer is null.
- ***Since*** `3.0.0`

```C++
UniquePtr<Texture> unique(Owner<SDL_Texture*> texture);
```

---

### `Texture::unique(const Renderer&, CZString)`

Creates and returns a unique pointer to a texture loaded from the image at the specified path.

- **`renderer`** the renderer that will be used to create the texture.
- **`path`** the file path of the image that the texture will be based on, can't be null.
- ***Returns*** a unique pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `3.0.0`

```C++
UniquePtr<Texture> unique(const Renderer& renderer, CZString path);
```

---

### `Texture::unique(const Renderer&, const Surface&)`

Creates and returns a unique pointer to a texture that is based on the supplied `Surface` instance.

- **`renderer`** the renderer that will be used to create the texture.
- **`surface`** the surface that the texture will be based on.
- ***Returns*** a unique pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `4.0.0`

```C++
UniquePtr<Texture> unique(const Renderer& renderer, const Surface& surface);
```

---

### `Texture::unique(const Renderer&, PixelFormat, Access, IArea)`

Creates and returns a unique pointer to a texture with the specified characteristics.

- **`renderer`** the renderer that will be used to create the texture.
- **`format`** the pixel format that will be used by the texture.
- **`access`** the texture access that will be used by the texture.
- ***Returns*** a unique pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `3.1.0`

```C++
UniquePtr<Texture> unique(const Renderer& renderer, PixelFormat format, Access access, IArea size);
```

---

### `Texture::streaming(const Renderer&, CZString, PixelFormat)`

Creates and returns a unique pointer to a texture based on the image at the specified path with `Streaming` texture access.
  
- **`renderer`** the renderer that will be used to create the texture.
- **`path`** the path of the image that the texture will be based on.
- **`format`** the pixel format that will be used by the texture.
- ***Returns*** a unique pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `4.0.0`

```C++
UniquePtr<Texture> streaming(const Renderer& renderer, CZString path, PixelFormat format);
```

---

### `Texture::shared(Owner<SDL_Texture*>)`

Creates and returns a shared pointer to a texture based on an existing SDL texture. The created texture will claim ownership of the supplied SDL texture.

- **`texture`** a pointer to the SDL texture that will be claimed, can't be null.
- ***Returns*** a shared pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the supplied pointer is null.
- ***Since*** `3.0.0`

```C++
UniquePtr<Texture> shared(Owner<SDL_Texture*> texture);
```

---

### `Texture::shared(const Renderer&, CZString)`

Creates and returns a shared pointer to a texture loaded from the image at the specified path.

- **`renderer`** the renderer that will be used to create the texture.
- **`path`** the file path of the image that the texture will be based on, can't be null.
- ***Returns*** a shared pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `3.0.0`

```C++
UniquePtr<Texture> shared(const Renderer& renderer, CZString path);
```

---

### `Texture::shared(const Renderer&, const Surface&)`

Creates and returns a shared pointer to a texture that is based on the supplied `Surface` instance.

- **`renderer`** the renderer that will be used to create the texture.
- **`surface`** the surface that the texture will be based on.
- ***Returns*** a shared pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `3.0.0`

```C++
UniquePtr<Texture> shared(const Renderer& renderer, const Surface& surface);
```

---

### `Texture::shared(const Renderer&, PixelFormat, Access, IArea)`

Creates and returns a shared pointer to a texture with the specified characteristics.

- **`renderer`** the renderer that will be used to create the texture.
- **`format`** the pixel format that will be used by the texture.
- **`access`** the texture access that will be used by the texture.
- ***Returns*** a shared pointer to a `Texture` instance.
- ***Throws*** `CenturionException` if the texture cannot be created.
- ***Since*** `3.1.0`

```C++
UniquePtr<Texture> shared(const Renderer& renderer, PixelFormat format, Access access, IArea size);
```

---

## Copying

N/A

---

## Moving

### `Texture(Texture&&)`

Creates a texture by moving the contents of the supplied texture.

- **`other`** the texture that will be moved.
- ***Since*** `3.0.0`

```C++
Texture(Texture&& other) noexcept;
```

### `operator=(Texture&&)`

Moves the contents of the supplied texture into the invoked texture.

- **`other`** the texture that will be moved.
- ***Returns*** the texture that had its contents replaced.
- ***Since*** `3.0.0`

```C++
Texture& operator=(Texture&& other) noexcept;
```

## Members

### Mutators

N/A

---

### Setters

#### `Texture::set_pixel(IPoint, const Color&)`

Sets the color of the pixel at the specified coordinate. This method has no effect if the texture access of the texture isn't `Streaming` or if the supplied coordinate is out-of-bounds.

- **pixel** the coordinate of the pixel that will be changed, can safely be out-of-bounds.
- **`color`** the new color of the pixel at the specified coordinate.
- ***Since*** `4.0.0`

```C++
void set_pixel(IPoint pixel, const Color& color) noexcept;
```

---

#### `Texture::set_alpha(Uint8)`

Sets the alpha (opacity) value that is used by the texture.

- **`alpha`** the new alpha value, in the range [0, 255].
- ***Since*** `3.0.0`

```C++
void set_alpha(Uint8 alpha) noexcept;
```

---

#### `Texture::set_blend_mode(BlendMode)`

Sets the blend mode that will be used by the texture.

- **`mode`** the new blend mode that will be used by the texture.
- ***Since*** `3.0.0`

```C++
void set_blend_mode(BlendMode mode) noexcept;
```

---

#### `Texture::set_color_mod(Color)`

Sets the color modulation that is used by the texture. Note, the alpha component of the supplied color is ignored by this method.

- **`color`** the color that will be used to modulate the color of the texture.
- ***Since*** `3.0.0`

```C++
void set_color_mod(Color color) noexcept;
```

---

#### `Texture::set_scale_mod(ScaleMode)`

Sets the scale mode that will be used by the texture.

- **`mode`** the new scale mode that will be used by the texture.
- ***Since*** `4.0.0`

```C++
void set_scale_mode(ScaleMode mode) noexcept;
```

---

### Getters

#### `Texture::format()`

Returns the pixel format that is used by the texture.

- ***Returns*** the pixel format that is currently being used by the texture.
- ***Since*** `3.0.0`

```C++
PixelFormat format() const noexcept;
```

---

#### `Texture::access()`

Returns the texture access that is used by the texture.

- ***Returns*** the texture access that is currently being used by the texture.
- ***Since*** `3.0.0`

```C++
Access access() const noexcept;
```

---

#### `Texture::width()`

Returns the width of the texture.

- ***Returns*** the width of the texture, in pixels.
- ***Since*** `3.0.0`

```C++
int width() const noexcept;
```

---

#### `Texture::height()`

Returns the height of the texture.

- ***Returns*** the height of the texture, in pixels.
- ***Since*** `3.0.0`

```C++
int height() const noexcept;
```

---

#### `Texture::size()`

Returns the size (width and height) of the texture.

- ***Returns*** the size of the texture, in pixels.
- ***Since*** `4.0.0`

```C++
IArea size() const noexcept;
```

---

#### `Texture::is_target()`

Indicates whether or not the texture is a possible render target.

- ***Returns*** `true` if the texture can be used as a render target; `false` otherwise.
- ***Since*** `3.0.0`

```C++
bool is_target() const noexcept;
```

---

#### `Texture::is_static()`

Indicates whether or not the texture has `Static` texture access. Which would indicate that the texture rarely changes and isn't lockable.

- ***Returns*** `true` if the texture has `Static` texture access; `false` otherwise.
- ***Since*** `3.0.0`

```C++
bool is_static() const noexcept;
```

---

#### `Texture::is_streaming()`

Indicates whether or not the texture has `Streaming` texture access. Which would indicate that the texture changes frequently and is therefore lockable.

- ***Returns*** `true` if the texture has `Streaming` texture access; `false` otherwise.
- ***Since*** `3.0.0`

```C++
bool is_streaming() const noexcept;
```

---

#### `Texture::alpha()`

Returns the alpha of the texture.

- ***Returns*** the alpha value used by the texture.
- ***Since*** `3.0.0`

```C++
Uint8 alpha() const noexcept;
```

---

#### `Texture::blend_mode()`

Returns the blend mode used by the texture.

- ***Returns*** the blend mode that is being used by the texture.
- ***Since*** `3.0.0`

```C++
BlendMode blend_mode() const noexcept;
```

---

#### `Texture::color_mod()`

Returns the color modulation of the texture.

- ***Returns*** the color modulation of the texture, represented by a `Color` instance.
- ***Since*** `3.0.0`

```C++
Color color_mod() const noexcept;
```

---

#### `Texture::scale_mode()`

Returns the scale mode used by the texture.

- ***Returns*** the scale mode that is being used by the texture.
- ***Since*** `4.0.0`

```C++
ScaleMode scale_mode() const noexcept;
```

---

#### `Texture::to_string()`

Returns a string representation of the texture. The returned string will look something like `[Texture@0x7cf388 | Width: 200, Height: 150]`.

- ***Returns*** a textual representation of the texture.
- ***Since*** `3.0.0`

```C++
std::string to_string() const;
```

---

#### `Texture::get()`

Returns a pointer to the internal SDL_Texture. Use of this method is not recommended, since it purposefully breaks const-correctness. However, it is useful since many SDL calls use non-const pointers even when no change will be applied.

- ***Returns*** a pointer to the internal `SDL_Texture`.
- ***Since*** `4.0.0`

```C++
SDL_Texture* get() const noexcept;
```

---

### Conversions

#### `operator SDL_Texture*()`

Implicitly converts to `SDL_Texture*`.

- ***Returns*** a pointer to the internal `SDL_Texture`.
- ***Since*** `3.0.0`

```C++
operator SDL_Texture*() noexcept;
```

---

#### `operator const SDL_Texture*()`

Implicitly converts to `const SDL_Texture*`.

- ***Returns*** a pointer to the internal `SDL_Texture`.
- ***Since*** `3.0.0`

```C++
operator const SDL_Texture*() const noexcept;
```

---

## Overloaded operators

N/A
