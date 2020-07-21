#ifndef CENTURON_GAME_LOOP_HEADER
#define CENTURON_GAME_LOOP_HEADER

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
  using input_fun = bool();
  using logic_fun = void(milliseconds<float>);
  using render_fun = void();

  template <typename Input, typename Logic, typename Render>
  static void run(Input input, Logic logic, Render render)
  {
    bool running = true;
    milliseconds<float> m_prev = counter::now_ms();
    milliseconds<float> m_curr = counter::now_ms();
    while (running) {
      m_prev = m_curr;
      m_curr = counter::now_ms();

      running = input();

      const auto diff = m_curr - m_prev;
      logic(diff);

      render();
    }
  }

  void run() { run(m_input, m_logic, m_render); }

  void set_logic(logic_fun logic) { m_logic = logic; }

  void set_render(render_fun render) { m_render = render; }

  void set_input(input_fun input) { m_input = input; }

 private:
  logic_fun* m_logic{};
  render_fun* m_render{};
  input_fun* m_input{};
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

#endif  // CENTURON_GAME_LOOP_HEADER
