basic_window
============

The ``basic_window`` class provides the base implementation of the renderers in the 
library. This class is the base class of ``window`` and ``window_handle``.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 N/A
Movable                  N/A
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
Header                   ``basic_window.hpp``
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::basic_window
  :members:
  :undoc-members:
  :outline:
  :no-link:

Related functions
-----------------

.. doxygenfunction:: get_renderer(const basic_window<T> &window) noexcept -> renderer_handle
  :outline:
  :no-link:

See also
--------

* :doc:`window </pages/api/graphics/window>`
* :doc:`window_handle </pages/api/graphics/window_handle>`