sound_effect
============

The ``sound_effect`` class represents a short sound effect, stored in various formats. Unlike music, 
multiple sound effects can be playing simultaneously. The supported file formats are: WAVE/RIFF (``.wav``), 
AIFF (``.aiff``), VOC (``.voc``), OGG (``.ogg``) and VOC (``.voc``).
 
General information
-------------------

======================  =========================================
  Property               Value
----------------------  -----------------------------------------
Default constructible    No
Copyable                 No
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``Mix_Chunk*``, ``const Mix_Chunk*``
Overloaded operators     ``<<``
Printable                Yes
Namespace                ``::centurion``
Header                   ``sound_effect.hpp``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: centurion::sound_effect
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

.. code-block:: C++

  #include <centurion_as_ctn.hpp>
  #include <sound_effect.hpp>

  void foo()
  {
    ctn::sound_effect sound{"click.wav"};

    // play once
    sound.play(); 

    // stop playback
    sound.stop(); 

    // sets the volume in the range [0, sound_effect::max_volume()]
    sound.set_volume(64);

    // play twice
    sound.play(2);
    
    // loops forever
    sound.play(ctn::sound_effect::loopForever);

    // fades in over 500 milliseconds
    sound.fade_in(ctn::milliseconds<int>{500});

    if (sfx.is_fading()) {
      // ...
    }
  }