#ifndef CENTURION_GAME_LOOP_HEADER
#define CENTURION_GAME_LOOP_HEADER

#include <cassert>
#include <entt.hpp>

#include "centurion_api.hpp"
#include "counter.hpp"
#include "renderer.hpp"
#include "screen.hpp"
#include "window.hpp"

namespace centurion::experimental {

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
class basic_variable_timestep_loop final {
 public:
  using input_handler = bool();
  using logic_handler = void(milliseconds<float>);
  using render_handler = void();

  void run()
  {
    assert(m_input);
    assert(m_logic);
    assert(m_render);

    bool running = true;
    milliseconds<float> m_prev = counter::now_ms();
    milliseconds<float> m_curr = counter::now_ms();
    while (running) {
      m_prev = m_curr;
      m_curr = counter::now_ms();

      running = m_input();

      const auto diff = m_curr - m_prev;
      m_logic(diff);

      m_render();
    }
  }

  template <auto Candidate>
  void connect_input() noexcept
  {
    m_input.connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_input(T& valueOrInstance) noexcept
  {
    m_input.connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate, class T>
  void connect_input(T* valueOrInstance) noexcept
  {
    m_input.connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate>
  void connect_logic() noexcept
  {
    m_logic.connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_logic(T& valueOrInstance) noexcept
  {
    m_logic.connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate, class T>
  void connect_logic(T* valueOrInstance) noexcept
  {
    m_logic.connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate>
  void connect_render() noexcept
  {
    m_render.connect<Candidate>();
  }

  template <auto Candidate, class T>
  void connect_render(T& valueOrInstance) noexcept
  {
    m_render.connect<Candidate>(valueOrInstance);
  }

  template <auto Candidate, class T>
  void connect_render(T* valueOrInstance) noexcept
  {
    m_render.connect<Candidate>(valueOrInstance);
  }

 private:
  entt::delegate<logic_handler> m_logic{};
  entt::delegate<render_handler> m_render{};
  entt::delegate<input_handler> m_input{};
};

template <typename delta>
class basic_semi_fixed_timestep_loop final {
 public:
  using input_fun = bool();
  using logic_fun = void(milliseconds<float>);
  using render_fun = void();

  void update(input_fun input, logic_fun logic, render_fun render)
  {
    //    float time = 0;
    const auto fixedDelta = 1.0f / 60.0f;

    auto currentTime = time_now();

    bool running = true;
    while (running) {
      const auto newTime = time_now();
      auto frameTime = newTime - currentTime;

      currentTime = newTime;

      auto nSteps = 0;
      while (frameTime > 0.0f) {
        if (nSteps > m_maxSteps) {
          break;  // avoids spiral-of-death by limiting maximum amount of steps
        }

        const auto deltaTime = std::min(frameTime, fixedDelta);

        running = input();
        logic(deltaTime);

        frameTime -= deltaTime;
        //        time += deltaTime;

        ++nSteps;
      }

      render();
    }
  }

  [[nodiscard]] auto time_now() const -> milliseconds<float>
  {
    return std::chrono::duration_cast<milliseconds<float>>(counter::now_ms());
  }

 private:
  //  u64 m_curr{};
  //  u64 m_prev{};

  inline constexpr static int m_maxSteps = 5;

  //  input_fun* m_input{};
};

template <typename delta, typename alpha>
class basic_fixed_timestep_loop final {
 public:
  using logic = void(delta);
  using render = void(renderer&, alpha);

  basic_fixed_timestep_loop()
      : m_vsyncRate{static_cast<float>(screen::refresh_rate())},
        m_timeStep{1 / m_vsyncRate},
        m_counterFreq{static_cast<float>(counter::high_res_freq())}
  {}

  void tick()
  {
    //    bool running = true;
    //    while (running) {
    //      while (counter::now() >
    //
    //
    //    }

    //    while( game_is_running ) {
    //      while( GetTickCount() > next_game_tick ) {
    //        update();
    //        next_game_tick += SKIP_TICKS;
    //      }
    //      interpolation = float( GetTickCount() + SKIP_TICKS - next_game_tick
    //      )
    //          / float( SKIP_TICKS );
    //      render( interpolation );
    //    }
  }

 private:
  u64 m_now{};
  u64 m_then{};
  delta m_delta{};
  delta m_accumulator{};
  delta m_deltaBuffer{};

  const float m_vsyncRate;
  const delta m_timeStep;
  const float m_counterFreq;
};

using fixed_timestep_loop = basic_fixed_timestep_loop<float, float>;
using semi_fixed_timestep_loop = basic_semi_fixed_timestep_loop<float>;
using variable_timestep_loop = basic_variable_timestep_loop;

}  // namespace centurion::experimental

#endif  // CENTURION_GAME_LOOP_HEADER
