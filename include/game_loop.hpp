#ifndef CENTURON_APP_HEADER
#define CENTURON_APP_HEADER

#include "centurion_api.hpp"
#include "counter.hpp"
#include "renderer.hpp"
#include "screen.hpp"
#include "window.hpp"

namespace centurion::experimental {

// class default_make_window {
// public:
//  auto operator()() const -> window { return window{}; }
//};
//
// class default_make_renderer {
// public:
//  auto operator()(const window& window) const -> renderer
//  {
//    return renderer{window};
//  }
//};
//
// template <class derived,
//          class delta,
//          class make_window = default_make_window,
//          class make_renderer = default_make_renderer>
// class loop {
// public:
//  //  loop() : m_window{make_window{}()},
//  m_renderer{make_renderer{}(m_window)}
//  //  {}
//
//  //  void run(
//
//  //  [[nodiscard]] auto get_window() -> window& { return m_window; }
//  //
//  //  [[nodiscard]] auto get_window() const -> const window& { return
//  m_window;
//  //  }
//  //
//  //  [[nodiscard]] auto get_renderer() -> renderer& { return m_renderer; }
//  //
//  //  [[nodiscard]] auto get_renderer() const -> const renderer&
//  //  {
//  //    return m_renderer;
//  //  }
//  //
//  // private:
//  //  window m_window;
//  //  renderer m_renderer;
//};

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
template <typename delta>
class basic_variable_timestep_loop final {
 public:
//  using input_fun = bool();
//  using logic_fun = void(milliseconds<float>);
//  using render_fun = void();

  template <typename Input, typename Logic, typename Render>
  void run(Input input, Logic logic, Render render)
  {
    bool running = true;

    m_prev = counter::now_ms();
    m_curr = counter::now_ms();
    while (running) {
      m_prev = m_curr;
      m_curr = counter::now_ms();

      running = input();

      const auto diff = m_curr - m_prev;
      logic(diff);

      render();
    }
  }

 private:
  milliseconds<float> m_curr{};
  milliseconds<float> m_prev{};
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
using variable_timestep_loop = basic_variable_timestep_loop<float>;

inline void foo()
{
  {
    // fixed timestep
    //    auto input = [] { return false; };
    //
    //    auto logic = [](float delta) {};
    //
    //    auto render = [](renderer& renderer, float alpha) {};
    //
    fixed_timestep_loop loop;
  }

  {
      // variable timestep
      //    auto input = [] { return false; };
      //
      ////    auto logic = [](milliseconds<float> delta) {
      //////      auto delta_sec =
      ///std::chrono::duration_cast<seconds<float>>(delta);
      ////
      ////    };
      //
      //    auto render = []() {};
      //
      //    variable_timestep_loop loop;
      //
      //    loop.update(input, logic, render);
  }

  {
    semi_fixed_timestep_loop loop;
  }
}

}  // namespace centurion::experimental

#endif  // CENTURON_APP_HEADER
