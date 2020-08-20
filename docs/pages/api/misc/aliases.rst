Aliases
=======

The library utilizes a wide array of type aliases, this document serves as 
a reference for these aliases. Most aliases are provided in the 
``centurion_types.hpp`` header.

owner<T>
--------

Equivalent to ``gsl::owner<T>``. Used to denote ownership of raw pointers.

nn_owner<T>
-----------

Equivalent to ``gsl::not_null<owner<T>>``. Represents a non-null raw pointer
to a resource that must be deleted using the pointer. This is commonly featured in 
constructors for owning types, such as ``window``, ``renderer``, ``texture``, etc.

czstring
--------

Equivalent to ``gsl::czstring<>`` (or simply ``const char*``).

nn_czstring
-----------

Equivalent to ``gsl::not_null<czstring>``. 

zstring
-------

Equivalent to ``gsl::zstring<>`` (or simply ``char*``). Occasionally used behind-the-scenes.

hash_id
-------

Equivalent to ``entt::id_type``. This is the type of the identifiers obtained from
hashing strings using EnTT. For example, given ``constexpr auto id = "foo"_hs``, the type of 
``id`` is ``hash_id``.

buffer<std::size_t size>
------------------------

Equivalent to ``std:array<std::byte, size>``. Represents a stack buffer, used to avoid dynamic
memory allocations with ``std::pmr`` types.

u64
---

Equivalent to ``Uint64``. Represents a 64-bit unsigned integer.

u32
---

Equivalent to ``Uint32``. Represents a 32-bit unsigned integer.

u16
---

Equivalent to ``Uint16``. Represents a 16-bit unsigned integer.

u8
--

Equivalent to ``Uint8``. Represents an 8-bit unsigned integer.

i64
---

Equivalent to ``Sint64``. Represents a 64-bit signed integer.

i32
---

Equivalent to ``Sint32``. Represents a 32-bit signed integer.

i16
---

Equivalent to ``Sint16``. Represents a 16-bit signed integer.

i8
--

Equivalent to ``Sint8``. Represents an 8-bit signed integer.

unicode
-------

Equivalent to ``u16``. Represents a Unicode code point.

seconds<T>
----------

Equivalent to ``std::chrono::duration<T>``. 

milliseconds<T>
---------------

Equivalent to ``std::chrono::duration<T, std::milli>``. 

microseconds<T>
---------------

Equivalent to ``std::chrono::duration<T, std::micro>``. 

nanoseconds<T>
--------------

Equivalent to ``std::chrono::duration<T, std::nano>``.

minutes<T>
----------

Equivalent to ``std::chrono::duration<T, std::ratio<60>>``.

Smart pointer aliases
---------------------

Some Centurion clases provide aliases for smart pointers to themselves. For example,
the ``window`` class provides these.

.. code-block:: C++

  ctn::window::uptr unique; // std::unique_ptr<ctn::window> unique;
  ctn::window::sptr shared; // std::shared_ptr<ctn::window> shared;
  ctn::window::wptr weak;   // std::weak_ptr<ctn::window> weak;


