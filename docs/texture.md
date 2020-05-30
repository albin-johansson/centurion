# Texture

The Texture class represents a hardware-accelerated image.

## Table of contents

- [Texture](#texture)
  - [Table of contents](#table-of-contents)
  - [General information](#general-information)
  - [Construction and destruction](#construction-and-destruction)
    - [`Texture(Owner<SDL_Texture*>)`](#textureownersdl_texture)
  - [Smart pointer factory methods](#smart-pointer-factory-methods)
    - [Unique](#unique)
    - [Shared](#shared)
  - [Copying](#copying)
  - [Moving](#moving)
  - [Members](#members)
    - [Mutators](#mutators)
    - [Setters](#setters)
    - [Getters](#getters)
    - [Conversions](#conversions)
  - [Overloaded operators](#overloaded-operators)

## General information

| Property              | Value         |
| --------------------- |:--------------|
| Default constructible | Yes |
| Movable               | Yes |
| Copyable              | No |
| Explicit conversions  | None |
| Implicit conversions  | `SDL_Texture*`, `const SDL_Texture*` |
| Overloaded operators  | None |
| Namespace             | `centurion` |
| Header                | `texture.h` |

## Construction and destruction

### `Texture(Owner<SDL_Texture*>)`

Creates a texture based on an existing SDL_Texture. The created Texture will claim ownership of the supplied texture.

- **texture** a pointer to the texture that will be claimed, can't be null.
- ***Throws*** CenturionException if the supplied pointer is null.
- ***Since*** `3.0.0`

```C++
explicit Texture(Owner<SDL_Texture*> texture);
```

## Smart pointer factory methods

### Unique

### Shared

## Copying

## Moving

## Members

### Mutators

### Setters

### Getters

### Conversions

## Overloaded operators