Clipboard
=========

Centurion provides an easy-to-use clipboard API. The clipboard 
API makes it possible to both query and set the system clipboard. 
This API is very similar to the SDL counterpart. However, there's no need 
to worry about freeing returned strings with the Centurion API.

General information
-------------------
======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Namespace                ``::centurion::clipboard``
Header                   ``clipboard.hpp``
Since                    5.0.0
======================  =========================================

Interface
---------

.. doxygennamespace:: centurion::clipboard
  :outline:
  :members:

Example
-------

Usage of the clipboard API is very simple, it's pretty much self-explanatory!

.. code-block:: c++
  :linenos:
  
  #include <cen.hpp>
  #include <clipboard.hpp>

  void foo() 
  {
    // Checks if there's non-empty text in the clipboard
    if (cen::clipboard::has_text()) {
      // ...
    }
    
    // Obtains the current clipboard text
    const auto text = cen::clipboard::get_text();

    // Sets the current clipboard text
    cen::clipboard::set_text("bar");
  }