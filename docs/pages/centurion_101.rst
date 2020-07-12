Centurion 101
=============
This page provides information that is good to know before continuing reading the rest of the
documentation.

Implementation details
~~~~~~~~~~~~~~~~~~~~~~
All aspects of the Centurion library that are considered to be implementation details, are
located in the ``centurion::detail`` namespace. You should never anything that resides in this
namespace directly. The members of the detail namespace are subject to change at any time, and
may not even be documented.

API Conventions
~~~~~~~~~~~~~~~
The library does its best to follow the C++ Core Guidelines (which can be found
`here <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>`_).

One of the most important conventions that the library adheres to is the principle that raw
pointers are non-owning. This means that whenever you see a Centurion function that returns a
raw pointer, then you should **never** claim ownership of it. The same principle applies for
functions that take raw pointers in the library. Ownership of raw pointers is explicitly
marked through use of the ``Owner`` template.

Furthermore, C-style strings, ``const char*`` and ``char*``, are denoted with the aliases
``czstring`` and ``zstring`` respectively. The ``c`` prefix denotes that the string is
``const``-qualified, and the ``z`` prefix denotes that the string is null-terminated.

For convenience, most Centurion classes feature factory methods for smart pointers. There's
always a factory method for each constructor. For instance, you can create a unique pointer to a
``ctn::window`` instance with ``ctn::window::unique()``. The factory methods are always called
``unique`` or ``shared``, for ``std::unique_ptr`` and ``std::shared_ptr`` respectively.

Another convenience that most classes provide is a `to_string()` method, which is useful for
debugging and logging purposes.