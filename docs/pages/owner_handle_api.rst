Owner/handle framework
======================

An important aspect of the Centurion library is the idea of "owners" and "handles", i.e. 
versions of Centurion classes with owning and non-owning semantics. For instance, you can default
construct a ``cen::window`` instance and don't have to worry about freeing its associated memory, 
but you could also create a ``cen::window_handle`` instance from a raw pointer, which doesn't 
manage the supplied pointer at all. In order to clarify this concept, let's look at some code 
examples.

.. code:: C++ 

  #include <window.hpp>

  void foo() 
  {
    { // Basic usage, no need to worry about ownership and lifetimes
      cen::window window;

      // ...do fun stuff with window...

    } // window is destroyed

    {
      // Perfectly legal example, the handle doesn't take ownership of the underlying pointer
      cen::window window;
      cen::window_handle handle{window};
    } // window is only destroyed once 

    { // The following is an example of incorrect usage of a handle, don't do this at home
      cen::window_handle handle{SDL_CreateWindow("foo", 0, 0, 800, 600, SDL_WINDOW_HIDDEN)};
    
    } // MEMORY LEAK: Handle does not manage lifetime of pointer!
  }

Okay so this is all well and good, but what's the point of all of this? Well, there a few
different reasons why this is incredibly useful and makes Centurion a better library. So 
let's look at a few more examples!

The first example we'll look at involves a simple function that takes a pointer to some SDL 
component, such as ``SDL_Renderer`` (it doesn't really matter). Now, we might also 
imagine that there's a lot of code in our hypothetical code base that pass along raw 
pointers to SDL components that we just cannot claim ownership of. This function might
look something like the following.

.. code:: C++

  void draw(SDL_Renderer* renderer) 
  {
    // ...A bunch of fancy rendering...
  }

Alright so here we have a typical function using SDL, but since we want to use Centurion 
instead of raw SDL, so it might be tempting to just do something like the following.

.. code:: C++

  void draw(SDL_Renderer* renderer) 
  {
    cen::renderer ren{renderer}; // Claims ownership of the pointer!

    // ...A bunch of fancier rendering...

  } // Oops, the SDL renderer is deleted here! 

The problem with the above approach is that **we cannot supply a non-owning pointer to 
an owning Centurion component**. This is where handles come to rescue! Handles are perfect 
for providing a view into the nice Centurion APIs without committing ownership of 
the associated resources. So a correct version of the earlier example would look like 
the following.

.. code:: C++

  void draw(SDL_Renderer* renderer) 
  {
    cen::renderer_handle ren{renderer}; // Does not claim ownership of the pointer!

    // ...A bunch of fancier rendering...

  } // All is good, the SDL renderer is not deleted!

The second example involves SDL functions that return non-owning raw pointers. For instance, one such 
function is ``SDL_GetWindowFromID()``, which returns a ``SDL_Window*``. It would be impossible to safely 
wrap the returned pointer of such functions in the corresponding Centurion component if we did not 
have the ability to explicitly state the ownership semantics. So as a result of handles, there is a corresponding
Centurion function for the aforementioned SDL function, ``get_window()``, which is defined in
``window_utils.hpp``. Many similiar examples can be found throughout the Centurion library.

Whilst it is not important to understand how this works behind-the-scenes, the basic premise is
that Centurion classes that feature owning and non-owning versions take a template parameter that 
dictates the ownership semantics. The following table lists all of the Centurion classes that 
feature owning and non-owning versions. You'll notice that the naming convention is that the "pretty" 
names are dedicated to the owning versions, and handles feature the ``_handle`` suffix.

.. note::

  Owning versions of Centurion classes will throw when passed null pointers to their associated 
  SDL component, whilst handles are perfectly content with being assigned null pointers. In fact, 
  handles define explicit ``bool`` conversions for checking whether or not the associated 
  pointer is null.

============================= ======================= ==============================  
 Underlying class              Owner                   Handle
----------------------------- ----------------------- ------------------------------
 ``basic_controller``          ``controller``          ``controller_handle``
 ``basic_cursor``              ``cursor``              ``cursor_handle``
 ``basic_haptic``              ``haptic``              ``haptic_handle``
 ``basic_joystick``            ``joystick``            ``joystick_handle``
 ``basic_pixel_format_info``   ``pixel_format_info``   ``pixel_format_info_handle``
 ``basic_renderer``            ``renderer``            ``renderer_handle``
 ``basic_sensor``              ``sensor``              ``sensor_handle``
 ``basic_surface``             ``surface``             ``surface_handle``
 ``basic_texture``             ``texture``             ``texture_handle``
 ``basic_window``              ``window``              ``window_handle``
============================= ======================= ============================== 
