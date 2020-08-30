base_path
=========

The ``base_path`` class is used to obtain the file path to the current executable.

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
Printable                Yes
Namespace                ``::centurion``
Header                   ``paths.hpp``
Since                    3.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: centurion::base_path
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++
  
  #include <cen.hpp>
  #include <paths.hpp>

  void foo()
  {
    if (cen::base_path path; path) {
      // successfully obtained the path of the application executable
      auto str = path.get();
    }
  }