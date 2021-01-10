basic_controller
================

Represents a game controller, such as Xbox and Playstation 
controllers. This class has both owning and non-owning versions, 
``controller`` and ``controller_handle``, respectively.

.. note:: 

  You may need to load appropriate game controller mappings before 
  you can begin using the game controller API with certain controllers. 
  This can be done through the ``cen::hint::gamecontroller::config_file`` 
  hint, or by using the ``load_mappings()`` and ``add_mapping()`` functions.

General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    Only ``controller``
Copyable                 Only ``controller_handle``
Movable                  Both ``controller`` and ``controller_handle``
Implicit conversions     None
Explicit conversions     None
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::cen``
Header                   ``controller.hpp``
Since                    5.0.0
======================  =========================================

Interface 
---------

.. doxygenclass:: cen::basic_controller
  :members:
  :outline:
  :no-link:

Examples
--------

.. tip::

  For a community-managed database file of game controller mappings,
  see `this <https://github.com/gabomdq/SDL_GameControllerDB>`_ link (if 
  the link doesn't work for some reason, you should be able to find a copy in the 
  Centurion test resources folder).

Set up controllers using ``basic_controller`` API
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <controller.hpp>

  void foo() 
  {
    // Parse all mappings from controller database file
    const auto count = cen::controller::load_mappings("resources/controllers.txt");
    if (!count) {
      // potential error handling here, since no mappings were added...
    } 

    cen::controller controller; // Defaults to controller associated with index 0
    // ...
  }

Set up controllers using hint API
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: C++

  #include <centurion.hpp>
  #include <controller.hpp>
  #include <hints.hpp>

  namespace {

  void init_controller_mappings() 
  {
    using cen::hint::gamecontroller::config_file;

    // Specify the file path to the controller mappings,
    // this has to happen before the library is initialized
    cen::set_hint<config_file>("resources/controllers.txt");
  }

  }  // namespace

  int main(int, char**) 
  {
    init_controller_mappings();

    // Note how the library is initialized after mappings
    const cen::library lib; 

    cen::controller controller;
    // ...
  
    return 0;
  }

See also
--------
* :doc:`Hints </pages/api/config/hint>`