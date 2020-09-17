Centurion 101
=============
This page provides good-to-know information before continuing reading the rest of the
documentation.

Implementation details
----------------------
All aspects of the Centurion library that are considered to be implementation details, are
located in the ``centurion::detail`` namespace. You should never use anything that resides in this
namespace directly. The members of the detail namespace are subject to change at any time, and
may not even be documented.

API Conventions
---------------
The library does its best to follow the C++ Core Guidelines (which can be found
`here <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>`_).

One of the most important conventions that the library adheres to, is the principle that raw
pointers are non-owning. This means that whenever you see a Centurion function that returns a
raw pointer, then you should **never** claim ownership of it. The same principle applies for
functions that take raw pointers in the library. Ownership of raw pointers is explicitly
marked through use of the ``owner`` template.

Textual representation
----------------------

Obtaining textual representations of Centurion components is primarily done using overloads of 
the ``cen::to_string`` function. This is very useful for debugging and logging purposes. 
Additionally, all types that provide an overload of ``to_string`` are also printable using C++
streams, using ``operator<<``.
