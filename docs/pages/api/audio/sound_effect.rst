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
Copyable                 Only ``sound_effect_handle``
Movable                  Yes
Implicit conversions     None
Explicit conversions     ``Mix_Chunk*``, ``const Mix_Chunk*``
Overloaded operators     ``<<``
Namespace                ``::cen``
Since                    3.0.0
======================  =========================================

Interface
---------

.. doxygenclass:: cen::basic_sound_effect
  :members:
  :undoc-members:
  :outline:
  :no-link:

Examples
--------

Basic playback
~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion.hpp>

  using ms = cen::milliseconds<int>;

  void foo()
  {
    cen::sound_effect sound{"click.wav"};

    // play once
    sound.play(); 

    // stop playback
    sound.stop(); 

    // play twice
    sound.play(2);
    cen::thread::sleep(ms{50});

    // loops forever
    sound.play(cen::sound_effect::forever);

    // checks whether or not the sound effect is currently being played
    if (sound.is_playing()) {
      // ...
    }

    sound.stop();
  }

Fading a sound effect in and out
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion.hpp>

  using ms = cen::milliseconds<int>;

  void foo()
  {
    cen::sound_effect sound{"click.wav"};

    // fades in over 500 milliseconds
    sound.fade_in(ms{500});

    // checks whether or not the sound effect is currently being faded
    if (sound.is_fading()) {
      // ...
    }

    // fades out over 1 second
    sound.fade_out(ms{1'000});
  }

Handling sound effect volume
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: C++

  #include <centurion.hpp>

  void foo()
  {
    cen::sound_effect sound{"click.wav"};

    // gets the current volume
    const auto vol = sound.volume();

    // obtains the sound effect max volume, equal to MIX_MAX_VOLUME
    constexpr auto max = cen::sound_effect::max_volume();

    // adjusts the volume
    sound.set_volume(108);
  }
