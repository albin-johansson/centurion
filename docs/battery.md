# Battery

The `Battery` class is a simple utility class for querying the state of the potential battery of the system.

Related components: `PowerState`

## Table of contents

- [Battery](#battery)
  - [Table of contents](#table-of-contents)
  - [General information](#general-information)
  - [Members](#members)
    - [Getters](#getters)
      - [`seconds_left()`](#seconds_left)
      - [`minutes_left()`](#minutes_left)
      - [`percentage()`](#percentage)
      - [`state()`](#state)
      - [`exists()`](#exists)

---

## General information

| Property              | Value       |
| --------------------- | :---------- |
| Default constructible | No          |
| Movable               | No          |
| Copyable              | No          |
| Explicit conversions  | None        |
| Implicit conversions  | None        |
| Overloaded operators  | None        |
| Namespace             | `centurion` |
| Header                | `battery.h` |

---

## Members

### Getters

#### `seconds_left()`

Returns the current amount of remaining seconds of battery life.

- ***Returns*** the amount of remaining seconds of battery life; `nothing` if the value can't be determined.
- ***Since*** `3.0.0`

```C++
static Optional<int> seconds_left() noexcept;
```

---

#### `minutes_left()`

Returns the current amount of remaining minutes of battery life.

- ***Returns*** the amount of remaining minutes of battery life; `nothing` if the value can't be determined.
- ***Since*** `3.0.0`

```C++
static Optional<int> minutes_left() noexcept;
```

---

#### `percentage()`

Returns the current percentage of remaining battery life.

- ***Returns*** the percentage of remaining battery life, in the range [0, 100]; `nothing` if the value can't be determined.
- ***Since*** `3.0.0`

```C++
static Optional<int> percentage() noexcept;
```

---

#### `state()`

Returns the power state of the current system.

- ***Returns*** the power state of the current system.
- ***Since*** `3.0.0`

```C++
static PowerState state() noexcept;
```

---

#### `exists()`

Indicates whether or not the system is running on a battery. This method is simply a convenience method that is based on the `Battery::state()` method.

- ***Returns*** `true` if the system is running on a battery; `false` otherwise.
- ***Since*** `4.0.0`

```C++
static bool exists() noexcept;
```
