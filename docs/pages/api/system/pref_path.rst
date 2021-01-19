pref_path
=========

The ``pref_path`` class is used to obtain the preferred file path for storing files related to your
application. This is useful for handling persistent data such as game saves or preferences.

.. note:: 

  This class is deprecated since Centurion 5.2.0. Use the ``get_pref_path()`` function instead.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``bool``
Overloaded operators     ``<<``
Namespace                ``::cen``
Header                   ``pref_path.hpp``
Since                    3.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::pref_path
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: get_pref_path(not_null<czstring>, not_null<czstring>) -> sdl_string
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++
  
  #include <paths.hpp>

  void foo()
  {
    if (cen::pref_path path{"my organization", "my awesome app"}; path) {
      // successfully obtained the preferred path for application files
      auto str = path.get();
    }
  }