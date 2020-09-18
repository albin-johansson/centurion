surface
=======

The ``surface`` class represents an image that is not hardware accelerated. Instances 
of this class is often used for icons. Furthermore, ``surface`` instances can be 
converted to a corresponding ``texture``. Additionally, the ``surface`` class is copyable, 
which is quite rare for Centurion classes that allocate memory behind-the-scenes.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``SDL_Surface*``, ``const SDL_Surface*``
Overloaded operators     ``<<``
Namespace                ``::cen``
Header                   ``surface.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::surface
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: to_string(const surface &surface) -> std::string
  :outline:
  :no-link:

.. doxygenfunction:: operator<<(std::ostream &stream, const surface &surface) -> std::ostream&
  :outline:
  :no-link:

Examples
--------

Creating a texture from a surface
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <surface.hpp>
  #include <texture.hpp>
  #include <renderer.hpp>
  #include <window.hpp>

  void foo()
  {   
    cen::window window;
    cen::renderer renderer{window};

    const cen::surface surface{"images/bar.png"};
    cen::texture texture{renderer, surface};
  }