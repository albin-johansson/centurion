Platform
========

The platform API is a small interface meant to be used to deduce the 
platform of the current system.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::cen::platform``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: cen::platform
  :outline:
  :members:

Examples
--------

The following example demonstrates how the platform API is used. Note, that the example utilizes ``using enum``,
which is a C++20 feature, of course you could fully qualify the enumerators as well.

.. code-block:: c++
  
  #include <platform.hpp>

  void foo()
  {
    if (const auto name = cen::platform::name()) {
      // successfully obtained platform name, e.g. "Windows" or "Linux"
    }

    if (cen::platform::is_windows()) {
      // running on Windows
    }

    switch (cen::platform::id()) {
      using enum cen::plaform::platform_id;
      case windows: 
        // running on Windows
        break;
      case linux:
        // running on Linux
        break;
      case mac_osx:
        // running on OSX
        break;
      case ios:
        // running on iOS
        break;
      case android:
        // running on Android
        break;
      case unknown:
        // running on unknown platform
        break;
    }
  }