/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file game_loop.hpp
 *
 * @brief Provides various different game loop implementations.
 *
 * @since 5.0.0
 *
 * @see `variable_timestep_loop`
 * @see `semi_fixed_timestep_loop`
 * @see `fixed_timestep_loop`
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_GAME_LOOP_HEADER
#define CENTURION_GAME_LOOP_HEADER

#include <cassert>
#include <entt.hpp>

#include "centurion_api.hpp"
#include "counter.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion::experimental {

/**
 * @brief Provides the basic interface for game loops.
 *
 * @tparam Input the signature of the input handler function.
 * @tparam Logic the signature of the logic handler function.
 * @tparam Render the signature of the render handler function.
 *
 * @since 5.0.0
 *
 * @headerfile game_loop.hpp
 */
template <class Input, class Logic, class Render>
class basic_loop {
 public:
  /**
   * @brief Disconnects the associated delegates.
   *
   * @since 5.0.0
   */
  ~basic_loop() noexcept
  {
    if (m_input) {
      m_input.reset();
    }

    if (m_logic) {
      m_logic.reset();
    }

    if (m_render) {
      m_render.reset();
    }
  }

  /**
   * @brief Registers a free function or an unbound member as the input handler.
   *
   * @tparam Candidate the function or member that will handle input.
   *
   * @since 5.0.0
   */
  template <auto Candidate>
  void connect_input() noexcept
  {
    m_input.template connect<Candidate>();
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * input handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a reference to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_input(T& valueOrInstance) noexcept
  {
    m_input.template connect<Candidate>(valueOrInstance);
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * input handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a pointer to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_input(T* valueOrInstance) noexcept
  {
    m_input.template connect<Candidate>(valueOrInstance);
  }

  /**
   * @brief Registers a free function or an unbound member as the logic handler.
   *
   * @tparam Candidate the function or member that will handle logic.
   *
   * @since 5.0.0
   */
  template <auto Candidate>
  void connect_logic() noexcept
  {
    m_logic.template connect<Candidate>();
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * logic handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a reference to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_logic(T& valueOrInstance) noexcept
  {
    m_logic.template connect<Candidate>(valueOrInstance);
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * logic handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a pointer to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_logic(T* valueOrInstance) noexcept
  {
    m_logic.template connect<Candidate>(valueOrInstance);
  }

  /**
   * @brief Registers a free function or an unbound member as the render
   * handler.
   *
   * @tparam Candidate the function or member that will handle rendering.
   *
   * @since 5.0.0
   */
  template <auto Candidate>
  void connect_render() noexcept
  {
    m_render.template connect<Candidate>();
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * render handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a reference to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_render(T& valueOrInstance) noexcept
  {
    m_render.template connect<Candidate>(valueOrInstance);
  }

  /**
   * @brief Registers a free function with payload or a bound member as the
   * render handler.
   *
   * @tparam Candidate free function with payload or a bound member.
   * @tparam T the type of the payload.
   *
   * @param valueOrInstance a pointer to the payload.
   *
   * @since 5.0.0
   */
  template <auto Candidate, class T>
  void connect_render(T* valueOrInstance) noexcept
  {
    m_render.template connect<Candidate>(valueOrInstance);
  }

 protected:
  entt::delegate<Logic> m_logic{};
  entt::delegate<Render> m_render{};
  entt::delegate<Input> m_input{};
};

/**
 * @class variable_timestep_loop
 *
 * @brief Represents a variable timestep loop.
 *
 * @details This is by far the simplest game loop. The delta time is
 * dynamically adjusted based on the duration of the previous frame. However,
 * the problem with this loop is that, since the delta time isn't fixed, the
 * physics/logic will be non-deterministic. In extreme cases, this can cause
 * objects warping through walls, etc.
 *
 * @details The signature of the input, logic and render delegates are as
 * follows: `bool()`, `void(seconds<double>)` and `void()` respectively.
 *
 * @details If you're interested, detailed explanations of the various game
 * loops can be found <a
 * href="https://gafferongames.com/post/fix_your_timestep/">here!</a>
 *
 * @details The following example demonstrates a possible setup for how you
 * could use this class as the game loop in your game. Note, it also works
 * with free functions!
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <game_loop.hpp>
 *
 *   class Game {
 *    public:
 *     bool handle_input() { ... }
 *     void handle_logic(ctn::seconds<double> delta) { ... }
 *     void handle_render(double alpha) { ... }
 *   };
 *
 *   void setup()
 *   {
 *     // setup of window and renderer...
 *
 *     Game game;
 *
 *     ctn::variable_timestep_loop loop;
 *     loop.connect_input<&Game::handle_input>(game);
 *     loop.connect_logic<&Game::handle_logic>(game);
 *     loop.connect_render<&Game::handle_render>(game);
 *
 *     // ...
 *
 *     loop.run();
 *   }
 * @endcode
 *
 * @since 5.0.0
 *
 * @see `fixed_timestep_loop`
 * @see `variable_timestep_loop`
 * @see `semi_fixed_timestep_loop`
 *
 * @headerfile game_loop.hpp
 */
class variable_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void()> {
 public:
  /**
   * @brief Runs the game loop.
   *
   * @pre The input delegate **must** have been set.
   * @pre The logic delegate **must** have been set.
   * @pre The render delegate **must** have been set.
   *
   * @note This method doesn't return until the input delegate returns `false`.
   *
   * @since 5.0.0
   */
  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    bool running = true;

    auto then = counter::now_sec<double>();
    auto now = counter::now_sec<double>();
    while (running) {
      then = now;
      now = counter::now_sec<double>();

      running = m_input();
      m_logic(now - then);
      m_render();
    }
  }
};

/**
 * @class basic_semi_fixed_timestep_loop
 *
 * @brief Represents a semi-fixed timestep loop.
 *
 * @details This loop is similar to the variable timestep loop, but utilizes
 * a few tricks to minimize the unpredictability of a completely variable
 * timestep. It ensures that the delta time is never greater than the maximum
 * value, while still running at the correct speed on different machines.
 *
 * @details The signature of the input, logic and render delegates are as
 * follows: `bool()`, `void(seconds<double>)` and `void()` respectively.
 *
 * @details If you're interested, detailed explanations of the various game
 * loops can be found <a
 * href="https://gafferongames.com/post/fix_your_timestep/">here!</a>
 *
 * @details The following example demonstrates a possible setup for how you
 * could use this class as the game loop in your game. Note, it also works
 * with free functions!
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <game_loop.hpp>
 *
 *   class Game {
 *    public:
 *     bool handle_input() { ... }
 *     void handle_logic(ctn::seconds<double> delta) { ... }
 *     void handle_render(double alpha) { ... }
 *   };
 *
 *   void setup()
 *   {
 *     // setup of window and renderer...
 *
 *     Game game;
 *
 *     ctn::semi_fixed_timestep_loop loop;
 *     loop.connect_input<&Game::handle_input>(game);
 *     loop.connect_logic<&Game::handle_logic>(game);
 *     loop.connect_render<&Game::handle_render>(game);
 *
 *     // ...
 *
 *     loop.run();
 *   }
 * @endcode
 *
 * @tparam tickRate the amount of ticks per frame, e.g. 60.
 *
 * @since 5.0.0
 *
 * @see `fixed_timestep_loop`
 * @see `variable_timestep_loop`
 * @see `semi_fixed_timestep_loop`
 *
 * @headerfile game_loop.hpp
 */
template <int tickRate>
class basic_semi_fixed_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void()> {
 public:
  /**
   * @brief Runs the game loop.
   *
   * @pre The input delegate **must** have been set.
   * @pre The logic delegate **must** have been set.
   * @pre The render delegate **must** have been set.
   *
   * @note This method doesn't return until the input delegate returns `false`.
   *
   * @since 5.0.0
   */
  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    constexpr seconds<double> fixedDelta{1.0 / static_cast<double>(tickRate)};

    auto currentTime = counter::now_sec<double>();

    bool running = true;
    while (running) {
      const auto newTime = counter::now_sec<double>();
      auto frameTime = newTime - currentTime;
      currentTime = newTime;

      auto nSteps = 0;
      while (frameTime > seconds<double>::zero()) {
        if (nSteps > m_maxSteps) {
          break;  // avoids spiral-of-death by limiting maximum amount of steps
        }

        const auto deltaTime = std::min(frameTime, fixedDelta);

        running = m_input();
        if (!running) {
          break;
        }

        m_logic(deltaTime);

        frameTime -= deltaTime;

        ++nSteps;
      }

      m_render();
    }
  }

 private:
  inline constexpr static int m_maxSteps = 5;
};

/**
 * @class basic_fixed_timestep_loop
 *
 * @brief Represents a fixed timestep loop.
 *
 * @details Unlike the semi-fixed timestep loop, this loop only does updates
 * with a fixed delta value. Usually, there are some "unsimulated" time left
 * every frame, which this loop passes on to the next frame via an accumulator
 * and the "unsimulated" time isn't lost.
 *
 * @details When using this loop, you should use interpolation to determine
 * where to render your game objects. This is done via the alpha value
 * supplied to the render delegate. The formula for determining the
 * x-coordinate to use for rendering is as follows,
 * `(currentX * alpha) + previousX * (1.0 - alpha);`, the same is used for
 * y-coordinates. As a result, you need to keep track of the previous
 * position of game objects in your game.
 *
 * @details The signature of the input, logic and render delegates are as
 * follows: `bool()`, `void(seconds<double>)` and `void(double)` respectively.
 *
 * @details If you're interested, detailed explanations of the various game
 * loops can be found <a
 * href="https://gafferongames.com/post/fix_your_timestep/">here!</a>
 *
 * @details The following example demonstrates a possible setup for how you
 * could use this class as the game loop in your game. Note, it also works
 * with free functions!
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <game_loop.hpp>
 *
 *   class Game {
 *    public:
 *     bool handle_input() { ... }
 *     void handle_logic(ctn::seconds<double> delta) { ... }
 *     void handle_render(double alpha) { ... }
 *   };
 *
 *   void setup()
 *   {
 *     // setup of window and renderer...
 *
 *     Game game;
 *
 *     ctn::fixed_timestep_loop loop;
 *     loop.connect_input<&Game::handle_input>(game);
 *     loop.connect_logic<&Game::handle_logic>(game);
 *     loop.connect_render<&Game::handle_render>(game);
 *
 *     // ...
 *
 *     loop.run();
 *   }
 * @endcode
 *
 * @tparam tickRate the amount of ticks per frame, e.g. 60.
 *
 * @since 5.0.0
 *
 * @see `fixed_timestep_loop`
 * @see `variable_timestep_loop`
 * @see `semi_fixed_timestep_loop`
 *
 * @headerfile game_loop.hpp
 */
template <int tickRate>
class basic_fixed_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void(double)> {
 public:
  /**
   * @brief Runs the game loop.
   *
   * @pre The input delegate **must** have been set.
   * @pre The logic delegate **must** have been set.
   * @pre The render delegate **must** have been set.
   *
   * @note This method doesn't return until the input delegate returns `false`.
   *
   * @since 5.0.0
   */
  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    constexpr seconds<double> delta{1.0 / static_cast<double>(tickRate)};
    constexpr seconds<double> spiralOfDeathCap{0.25};

    auto currentTime = counter::now_sec<double>();
    seconds<double> accumulator{0};

    bool running = true;
    while (running) {
      const auto newTime = counter::now_sec<double>();

      auto frameTime = newTime - currentTime;
      if (frameTime > spiralOfDeathCap) {
        frameTime = spiralOfDeathCap;
      }

      currentTime = newTime;

      accumulator += frameTime;

      while (accumulator >= delta) {
        running = m_input();
        if (!running) {
          break;
        }

        m_logic(delta);

        accumulator -= delta;
      }

      m_render(accumulator / delta);
    }
  }
};

/**
 * @typedef semi_fixed_timestep_loop
 *
 * @brief Alias for a semi-fixed timestep loop that uses a 60 Hz tick-rate.
 *
 * @since 5.0.0
 */
using semi_fixed_timestep_loop = basic_semi_fixed_timestep_loop<60>;

/**
 * @typedef fixed_timestep_loop
 *
 * @brief Alias for a fixed timestep loop that uses a 60 Hz tick-rate.
 *
 * @since 5.0.0
 */
using fixed_timestep_loop = basic_fixed_timestep_loop<60>;

}  // namespace centurion::experimental

#endif  // CENTURION_GAME_LOOP_HEADER
