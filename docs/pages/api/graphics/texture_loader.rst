texture_loader
==============

The ``texture_loader`` class is a simple helper class useful for not having to 
pass around renderers in order to create textures.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Printable                No
Namespace                ``::centurion``
Header                   ``texture_loader.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::texture_loader
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++

  #include <texture_loader.hpp>
  #include <cen.hpp>

  void demo()
  {
    cen::window window;
    cen::renderer renderer{window};
    cen::texture_loader loader{renderer};

    // creates a unique pointer to a texture
    auto unique = loader.unique("resources/some_image.png");

    // creates a shared pointer to a texture
    auto shared = loader.shared("resources/other_image.png");

    // creates a local texture instance
    auto local = loader.create("resources/last_image.png");
  }