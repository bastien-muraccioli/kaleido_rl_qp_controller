#include "KaleidoRLQPController_RL.h"

#include <KaleidoRLQPController.h>

void KaleidoRLQPController_RL::configure(const mc_rtc::Configuration &) {}

void KaleidoRLQPController_RL::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.activateTorqueControl(true);
  ctl.activateContactConstraints(false);
  ctl.activateExternalTorqueComputation(true);
  ctl.solver().addTask(ctl.torqueJointTask);
  ctl.rlStateRunner.start(ctl, "RL_State");
}

bool KaleidoRLQPController_RL::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.rlStateRunner.run(ctl);
  ctl.torqueJointTask->setPosTarget(ctl.rlRuntime().q_rl());
  return false;
}

void KaleidoRLQPController_RL::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.solver().removeTask(ctl.torqueJointTask);
  ctl.activateExternalTorqueComputation(false);
}

EXPORT_SINGLE_STATE("KaleidoRLQPController_RL", KaleidoRLQPController_RL)
