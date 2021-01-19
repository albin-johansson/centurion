base_path
=========

The ``base_path`` class is used to obtain the path to directory from which the application 
was run.

.. note:: 

  This class is deprecated since Centurion 5.2.0. Use the ``get_base_path()`` function instead.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Yes
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``bool``
Overloaded operators     ``<<``
Namespace                ``::cen``
Header                   ``base_path.hpp``
Since                    3.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::base_path
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: get_base_path() -> sdl_string
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++
  
  #include <paths.hpp>

  void foo()
  {
    if (cen::base_path path; path) {
      // successfully obtained the path of the application executable
      auto str = path.get();
    }
  }