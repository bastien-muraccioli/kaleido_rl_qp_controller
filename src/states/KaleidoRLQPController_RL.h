#pragma once

#include <mc_control/fsm/State.h>

/**
 * Robot-agnostic single RL execution state.
 */
struct KaleidoRLQPController_RL : mc_control::fsm::State
{
  void configure(const mc_rtc::Configuration & config) override;
  void start(mc_control::fsm::Controller & ctl) override;
  bool run(mc_control::fsm::Controller & ctl) override;
  void teardown(mc_control::fsm::Controller & ctl) override;
};
