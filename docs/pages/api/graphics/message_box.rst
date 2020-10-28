message_box
===========

The ``message_box`` class represents a modal window used to provide
information, warnings and errors. The appearance of these message boxes
varies depending on the platform, and certain styling is not available 
on all platforms.

General information
-------------------

======================  =========================================
Default constructible    Yes
Copyable                 Yes
Movable                  Yes
Implicit conversions     None
Explicit conversions     None
Overloaded operators     None
Namespace                ``::cen``
Header                   ``message_box.hpp``
======================  =========================================

Interface
---------

.. doxygenclass:: cen::message_box
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Showing a message box using message_box instance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The non-static version of the ``show`` function is not as terse as the static
counterpart. However, it is possible to customize the message box more using the 
instance-based approach.

.. code-block:: C++

  #include <message_box.hpp>

  void foo()
  {
    cen::message_box mb;

    mb.set_title("Hello World!");
    mb.set_message("This is a message box!");

    mb.show();
  }

Showing a message box using static show function
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The static version of the ``show`` function is very easy to use. The type and button order
used by the message box can optionally be supplied as parameters.

.. code-block:: C++

  #include <message_box.hpp>

  void foo()
  {
    cen::message_box::show("Hello!", "This is a piece of information!");

    cen::message_box::show("Hello!", 
                           "This is a warning!", 
                           cen::message_box::type::warning);

    cen::message_box::show("Hello!", 
                           "This is an error!", 
                           cen::message_box::type::error,
                           cen::message_box::button_order::right_to_left);
  }