Introduction
============

About Centurion
---------------
Centurion is a modern C++ library built on top of SDL2 in order to improve
type-safety, memory safety and overall ease-of-use. It can be used for
creating windows, 2D-rendering, keyboard input, mouse input, sound effects,
music, etc. In other words, most of the things you can do with SDL2!

Why use Centurion?
------------------
Centurion is written in modern C++17, which means that the API is much more
expressive, type-safe and easy-to-use than raw SDL2, which is written in C.
By using Centurion effectively, there's no need to worry about memory leaks and
ownership of  resources! By using Centurion you will write type-safe, expressive
and efficient code.

Getting started
---------------
Hopefully, you're at least a little bit interested in the library by know! So let's find how to
get started with Centurion.

Installation
~~~~~~~~~~~~
There are two options for how you can use the library.

- The first option is to use Centurion as a shared library. Binaries are available for MSVC,
  MinGW and GCC. For this approach, all you need to do is to link against the shared library and
  include the headers in the ``include`` directory, just like with any other library.

- You can also use the library in a pseudo-header-only mode. This means that you don't have to link
  against a pre-compiled binary. However, you'll have to include both the headers in the
  ``include`` directory, **and** the sources in the ``src`` directory. Furthermore, you'll also
  need to define the ``CENTURION_HEADER_ONLY`` macro in the ``<centurion_cfg.hpp>`` header.

.. note::

  The recommended way to use Centurion is as a shared library. Linking against a shared library
  should already be familiar to you if you've ever used SDL before. Oh, and your compilation times
  will benefit greatly.

Initialization
~~~~~~~~~~~~~~
The first thing that you must do if you want to use the library in your project is to initialize
the library. This is simply done by creating an instance of the ``Centurion`` class. Be aware
that the signature of the main-method **must** be ``int main(int, char**)``, this is because SDL
actually performs some setup before the main method is entered through some macro magic.

.. note::

   All Centurion classes, functions and aliases are located in the ``centurion``
   namespace. However, since it's tedious to qualify everything with ``centurion::``,
   it's recommended to use the ``<centurion_as_ctn.hpp>`` header to get access to
   the ``ctn`` namespace alias.


.. code-block:: c++

  #include <centurion_as_ctn.hpp>

  int main(int, char**)
  {
    ctn::Centurion c;
    // the library is now initialized!

    return 0;
  }



