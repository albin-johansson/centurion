# Introduction to Centurion

This document covers the basics needed to get going with the Centurion library. Furthermore, this document also provides a brief introduction to some of the modern C++ concepts needed to understand the library. Which might be useful for programmers that are used to using SDL2 with C, and want to switch to C++.

## Table of contents

- [Introduction to Centurion](#introduction-to-centurion)
  - [Table of contents](#table-of-contents)
  - [Conventions](#conventions)
    - [Implementation details](#implementation-details)
    - [Factory methods](#factory-methods)
    - [String representation](#string-representation)
    - [Naming convention](#naming-convention)
  - [Smart pointers](#smart-pointers)
  - [Ownership](#ownership)
  - [Optional values](#optional-values)
  - [Aliases](#aliases)
    - [Optional](#optional)
    - [UniquePtr](#uniqueptr)
    - [SharedPtr](#sharedptr)
    - [WeakPtr](#weakptr)
    - [Owner](#owner)
    - [Strings](#strings)
      - [ZString](#zstring)
      - [CZString](#czstring)

---

## Conventions

### Implementation details

Some components, methods and aliases in the Centurion library reside in the `centurion::detail` namespace. These are reserved for use in the implementation of the library, and might change without notice. So don't directly use anything from the `detail` namespace, and you'll be fine.

### Factory methods

Many Centurion components have static factory methods for creating smart pointers, for convenience. For example, if you're working with the Centurion class `T`, then you can expect to be able to call `T::unique()`, in order to create a unique pointer to a `T` instance. There is one of these factory methods for every constructor.

### String representation

Most Centurion components feature a `to_string()` method that returns a textual representation of the component, which can be useful for logging and/or debugging.

### Naming convention

The Centurion library utilizes a naming convention inspired by the Qt framework. In general, if a class has a setter `set_foo(int)`, then you'd expect the corresponding getter to be `foo()`.

---

## Smart pointers

Smart pointers are essential for modern C++ and for good reason, they make life a whole lot easier! In a nutshell, smart pointers are called "smart" because they, when used correctly, manage the lifetime of their associated resources *automatically*. No need for explicit usage of `new` and `delete`! There are three different types of smart pointers: unique, shared and weak.

---

## Ownership

Since Centurion is a wrapper library for SDL2, it would be very hard to avoid raw pointers completely. The Centurion library adheres to the principle that raw pointers are **non-owning** by default. This means that if a method of a Centurion class returns a `T*`, then you should **not** claim ownership of that pointer. Likewise, if a Centurion method takes a `T*` as a parameter, then the method does **not** claim ownership of the pointer. See `Owner<T>` for more details about explicit ownership.

---

## Optional values

Many things can go wrong when attempting to compute values, something might not be available on the current system or some internal call might just fail, etc. This is a very common problem when working with value-based return types, since there is no good way of signal that the value *isn't* actually valid. For example, imagine a method that returns an `int` as the result of some complex calculation, which might fail. Now, how should we handle failure? Historically, this has been "solved" by using combinations of out-parameters, error codes and letting special values denote different outcomes. However, these error handling strategies are arbitrarily designed and based on personal preference, e.g. does -1 or 0 as a return value denote failure/success? In C++, we could also throw an exception, but this is overkill when a computation is allowed to fail. This is where `Optional<T>` comes in handy. It can assume *all* of its normal values **and** it can easily be checked to see if it's empty. As a result, the Centurion library utilizes this type heavily in order to solve this problem.

---

## Aliases

There are quite a few aliases utilized in the Centurion library, in order to make the code shorter, clearer and easier to understand. All of the public aliases in the Centurion library are declared in `centurion_utils.h`.

### Optional

`Optional` is an alias for a wrapper type for values, used the determine whether or not a value exists. In the documentation, the empty value is referred to as `nothing`.

- **Since** `4.0.0`

```C++
template <typename T>
using Optional = tl::optional<T>;

constexpr tl::nullopt_t nothing = tl::nullopt;
```

### UniquePtr

`UniquePtr` is an alias for a unique pointers. This smart pointer should be your go-to when you need to use dynamic memory allocation. You won't have any issues with memory leaks with it.

- **Since** `4.0.0`

```C++
template <typename T, typename Deleter = std::default_delete<T>()>
using UniquePtr = std::unique_ptr<T, Deleter>;
```

### SharedPtr

`SharedPtr` is an alias for a shared pointers. This smart pointer is meant to be used when multiple component need to share ownership of some resource. However, be mindful of cyclic dependencies, which would introduce memory leaks.

- **Since** `4.0.0`

```C++
template <typename T>
using SharedPtr = std::shared_ptr<T>;
```

### WeakPtr

`WeakPtr` is an alias for a weak pointers. Weak pointers are a special kind of shared-ownership pointer with "weak" semantics. This means that if the only references to some shared resource are weak pointers, then the resource will be released. In other words, a weak pointer doesn't own the referenced resource. Note, weak pointers can only be created from shared pointers.

- **Since** `4.0.0`

```C++
template <typename T>
using WeakPtr = std::weak_ptr<T>;
```

### Owner

`Owner` is an alias for a simple tag type that is very useful when dealing with raw pointers. The idea is to flag ownership directly in the code. For example, if a method takes an `Owner<SDL_Texture*>` as a parameter, then the method *will* claim the ownership of that pointer, and will subsequently be responsible for the destruction of it.  

- **Since** `4.0.0`

```C++
template <typename T>
using Owner = gsl::owner<T>;
```

---

### Strings

The aliases for strings follow a basic naming convention, set by the guidelines support library (GSL), where `C` = const and `Z` = null-terminated.

#### ZString

`ZString` is an alias for a null-terminated C-style string. It's the same as `char*`. This alias is used to clarify that we're dealing with strings, and not raw data, which could be the case, as you would know if you're used to programming in C.

- **Since** `4.0.0`

```C++
using ZString = gsl::zstring;
```

#### CZString

`CZString` is a type alias for a `const` null-terminated C-style string. It's the same as `const char*`. This alias is used to clarify that we're dealing with strings, and not raw data, which could be the case, as you would know if you're used to programming in C.

- **Since** `4.0.0`

```C++
using CZString = gsl::czstring;
```
