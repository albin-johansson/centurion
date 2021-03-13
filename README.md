# centurion

[![version](https://img.shields.io/badge/version-5.3.0-blue.svg)](https://semver.org)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![CI: Windows](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml) 
[![CI: Ubuntu](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml) 
[![CI: macOS](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml)
[![Documentation Status](https://readthedocs.org/projects/centurion/badge/?version=latest)](https://centurion.readthedocs.io/en/latest/?badge=latest)
[![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion)

Centurion is a multimedia-library built on top of SDL2, written in modern C++, which provides abstractions for window-management, hardware-accelerated rendering, sound effects, music, game controllers, keyboard and mouse input, multi-threading, system information, etc. The aim of Centurion is to serve as an easy-to-use and intuitive alternative to raw SDL2, that provides much improved type- and memory-safety.

The following table shows the supported versions of SDL2 and its extension libraries.

| Dependency | Supported versions     |
| ---------- | ---------------------- |
| SDL2       | 2.0.10, 2.0.12, 2.0.14 |
| SDL2_image | 2.0.5                  |
| SDL2_mixer | 2.0.4                  |
| SDL2_ttf   | 2.0.4                  |

## Why Centurion?

Centurion is written in C++17, enabling far more expressive and intuitive APIs compared to plain C. For instance, Centurion performs automatic memory management and provides type safe APIs, which are designed to be hard to use incorrectly. However, Centurion is not just a wrapper library that mirrors the underlying SDL APIs. Instead, a lot of effort has been put into improving the APIs by making them utilise idiomatic modern C++. Additionally, the library is continuously tested for correctness on Windows, Ubuntu and macOS, using unit tests, a mocked test suite and code coverage.

## Documentation

The library features rich in-source documentation using Doxygen, which provides detailed information about the different APIs. The Doxygen documentation for the latest stable release is hosted [here](https://albin-johansson.github.io/centurion/). Furthermore, there's a Read-the-Docs site aimed to provide an overview of the library, with examples and some tips for using Centurion, which you can find [here](https://centurion.readthedocs.io/en/latest/).

## Installation

The library is distributed as a *single* header file, located in the `include` folder. Download the `centurion.hpp` header and include it in your project, and it's ready to be used! You will of course also need to install SDL2.

## Examples

The Centurion library can be used in different styles, depending on what suits your project. Below are some examples of minimal Centurion programs that illustrate some possible approaches.

### Minimal Centurion program

The following is the smallest example of a Centurion program. All that is required to initialize the library is to create an instance of the `library` class, which must outlive the rest of your program, so it should be the first thing created in your `main` function.

```C++
#include <centurion.hpp>

int main(int argc, char** argv)
{
  cen::library library;

  // The Centurion library is now ready to be used!

  return 0;
}
```

### Event-driven program

The easiest approach to creating a responsive program is to utilise an event-driven approach. This should be familiar to you if you have ever used SDL2 before, where we use a nested `while` loop that handles all queued events each frame.

```C++
#include <centurion.hpp>

namespace {

void run() 
{
  cen::window window;              // Our OS window
  cen::renderer renderer{window};  // The hardware-accelerated renderer
  cen::event event;                // The event handler
  
  window.show();

  cen::irect rectangle{{10, 10}, {150, 100}};
  bool running{true};

  while (running) {
    while (event.poll()) {               // Go through all currently queued events
      if (event.is<cen::quit_event>()) { // Quit upon receive a quit event, e.g. when the user closes the window 
        running = false;
        break;
      } else if (const auto* kbe = event.try_get<cen::keyboard_event>()) {
        if (kbe->pressed() && kbe->is_active(cen::keycodes::d)) {
          rectangle.set_x(rectangle.x() + 10);
        }
      }
    }
    
    renderer.clear_with(cen::colors::black); // Clear the current rendering target
    
    renderer.set_color(cen::colors::red);
    renderer.fill_rect(rectangle);
    
    renderer.present(); // Apply our rendering commands to our rendering target
  }

  window.hide();  // Make our window invisible again
}

}  // namespace

int main(int argc, char** argv)
{
  cen::library library;

  run();

  return 0;
}}
```

#### Using an event dispatcher

Another event-driven approach consists of utilizing the `event_dispatcher` class. This allows us to explicitly specify which events we are interested in handling, and subsequently designate the associated event handlers that can be lambdas, free functions or member functions. However, this approach works best with member functions, since we can avoid passing around too much data.

```C++
#include <centurion.hpp>

namespace {

// Alias for our custom event dispatcher, we subscribe to quit and keyboard events
using custom_dispatcher = cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

class Game final {
 public:
  Game()
    : m_window{}
    , m_renderer{m_window}
  {
    // Register our event handlers
    m_dispatcher.bind<cen::quit_event>().to<&Game::on_quit_event>(this);
    m_dispatcher.bind<cen::keyboard_event>().to<&Game::on_keyboard_event>(this);
  }
  
  auto run() -> int
  {
    m_window.show();
    
    while (m_running) {
      m_dispatcher.poll();  // Handle currently queued events that we have subscribed to
      render();
    }
    
    m_window.hide();
    return 0;
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  custom_dispatcher m_dispatcher;
  cen::irect m_rectangle{{10, 10}, {150, 100}};
  bool m_running{true};

  void render() 
  {
    m_renderer.clear_with(cen::colors::black); // Clear the current rendering target
      
    m_renderer.set_color(cen::colors::red);
    m_renderer.fill_rect(m_rectangle);
    
    m_renderer.present(); // Apply our rendering commands to our rendering target
  }
  
  // Invoked for each quit event
  void on_quit_event(const cen::quit_event& event) 
  {
    m_running = false;
  }

  // Invoked for each keyboard event
  void on_keyboard_event(const cen::keyboard_event& event) 
  {
    if (event.pressed() && event.is_active(cen::keycodes::d)) {
      m_rectangle.set_x(m_rectangle.x() + 10);
    }
  }
};

}  // namespace

int main(int argc, char** argv)
{
  cen::library library;

  Game game;
  return game.run();
}
```

## Program using the keyboard and mouse state directly

It is also possible to create applications that are not event-driven at all. Instead of relying on events, we can instead access the current input state through the `key_state` and `mouse_state` classes. We can still query the event API for some extra information, such as if the user has requested the application to quit by closing the window.

```C++
#include <centurion.hpp>

namespace {

auto run() -> int
{
  cen::window window;
  cen::renderer renderer{window};
  cen::key_state keyState;      // Our view onto the keyboard state 
  cen::mouse_state mouseState;  // Our view onto the mouse state

  window.show();

  cen::irect rectangle{{10, 10}, {150, 100}};
  bool running{true};

  while (running) {
    keyState.update();                         // Updates the keyboard state
    mouseState.update(renderer.output_size()); // Updates the mouse state
    cen::event::refresh();                     // Manually refreshes the event queue

    // Check if there's a quit event in the event queue
    if (cen::event::queue_count(cen::event_type::quit) > 0) {
      running = false;
      break;
    }

    // Query the key state directly
    if (keyState.is_pressed(cen::keycodes::d)) {
      rectangle.set_x(rectangle.x() + 10);
    }

    renderer.clear_with(cen::colors::black);

    renderer.set_color(cen::colors::red);
    renderer.fill_rect(rectangle);

    renderer.present();
  }

  window.hide();
  return 0;
}

}  // namespace

int main(int argc, char** argv)
{
  cen::library library;
  return run();
}
```
