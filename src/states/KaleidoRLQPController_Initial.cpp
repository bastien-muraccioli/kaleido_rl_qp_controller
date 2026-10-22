#include "KaleidoRLQPController_Initial.h"

#include <KaleidoRLQPController.h>

void KaleidoRLQPController_Initial::configure(const mc_rtc::Configuration &) {}

void KaleidoRLQPController_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.rlStateRunner.start(ctl, "RL_State");
}

bool KaleidoRLQPController_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.rlStateRunner.run(ctl);
  ctl.torqueJointTask->setPosTarget(ctl.rlRuntime().q_rl());
  return false;
}

void KaleidoRLQPController_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
}

EXPORT_SINGLE_STATE("KaleidoRLQPController_Initial", KaleidoRLQPController_Initial)
