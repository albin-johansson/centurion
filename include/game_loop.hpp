#ifndef CENTURION_GAME_LOOP_HEADER
#define CENTURION_GAME_LOOP_HEADER

#include <cassert>
#include <entt.hpp>
#include <type_traits>

#include "centurion_api.hpp"
#include "counter.hpp"
#include "renderer.hpp"
#include "screen.hpp"
#include "window.hpp"

namespace centurion::experimental {

template <class Input, class Logic, class Render>
class basic_loop {
 public:
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

  template <auto Candidate>
  void connect_input() noexcept
  {
    m_input.template connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_input(T& valueOrInstance) noexcept
  {
    m_input.template connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate, class T>
  void connect_input(T* valueOrInstance) noexcept
  {
    m_input.template connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate>
  void connect_logic() noexcept
  {
    m_logic.template connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_logic(T& valueOrInstance) noexcept
  {
    m_logic.template connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate, class T>
  void connect_logic(T* valueOrInstance) noexcept
  {
    m_logic.template connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate>
  void connect_render() noexcept
  {
    m_render.template connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_render(T& valueOrInstance) noexcept
  {
    m_render.template connect<Candidate>(valueOrInstance);
  }

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
 * @class basic_variable_timestep_loop
 *
 * @brief Represents a variable-timestep loop.
 *
 * @details Physics updates are passed a "time elapsed since last update"
 * argument and are hence framerate-dependent. This may mean doing calculations
 * as position += (distancePerSecond * timeElapsed).
 *
 * Pros: smooth, easier to to code
 * Cons: non-deterministic, unpredictable at very small or large steps
 *
 * @tparam delta the delta time type.
 *
 * @since 5.0.0
 *
 * @headerfile game_loop.hpp
 */
class basic_variable_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void()> {
 public:
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

class basic_semi_fixed_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void()> {
 public:
  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    constexpr seconds<double> fixedDelta{1.0 / 60.0};

    auto currentTime = counter::now_sec<double>();

    bool running = true;
    while (running) {
      const auto newTime = counter::now_sec<double>();
      auto frameTime = newTime - currentTime;

      currentTime = newTime;

      auto nSteps = 0;
      while (frameTime.count() > 0.0) {
        if (nSteps > m_maxSteps) {
          break;  // avoids spiral-of-death by limiting maximum amount of steps
        }

        const auto deltaTime = std::min(frameTime, fixedDelta);

        running = m_input();
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

class basic_fixed_timestep_loop final
    : public basic_loop<bool(), void(seconds<double>), void(double)> {
 public:
  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    const seconds<double> delta{1.0 / 60.0};
    const seconds<double> spiralOfDeathCap{0.25};

    auto currentTime = counter::now_sec<double>();
    seconds<double> accumulator{0};

    bool running = true;
    while (running) {
      const auto newTime = counter::now_sec<double>();

      counter::now_sec<double>();

      auto frameTime = newTime - currentTime;
      if (frameTime > spiralOfDeathCap) {
        frameTime = spiralOfDeathCap;
      }

      currentTime = newTime;

      accumulator += frameTime;

      while (accumulator >= delta) {
        //        previousState = currentState;
        //        integrate( currentState, t, dt );
        running = m_input();
        m_logic(delta);

        //        time += dt;
        accumulator -= delta;
      }

      // State state = currentState * alpha + previousState * (1.0 - alpha);
      m_render(accumulator / delta);
    }
  }
};

using fixed_timestep_loop = basic_fixed_timestep_loop;
using semi_fixed_timestep_loop = basic_semi_fixed_timestep_loop;
using variable_timestep_loop = basic_variable_timestep_loop;

}  // namespace centurion::experimental

#endif  // CENTURION_GAME_LOOP_HEADER
