#include "KaleidoRLQPController_RLPos.h"

#include <KaleidoRLQPController.h>

void KaleidoRLQPController_RLPos::configure(const mc_rtc::Configuration &) {}

void KaleidoRLQPController_RLPos::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.rlStateRunner.start(ctl, "RL_State");
  ctl.activateQPControl(true);
  ctl.activateTorqueControl(false);
  ctl.activateFloatingBaseReal(true);
  ctl.activateContactConstraints(false);
  ctl.activateExternalTorqueComputation(true);
  if(ctl.postureTask->inSolver()) ctl.solver().removeTask(ctl.postureTask);
}

bool KaleidoRLQPController_RLPos::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.rlStateRunner.run(ctl);
  ctl.torqueJointTask->setPosTarget(ctl.rlRuntime().q_rl());
  return false;
}

void KaleidoRLQPController_RLPos::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.solver().removeTask(ctl.torqueJointTask);
  ctl.activateExternalTorqueComputation(false);
}

EXPORT_SINGLE_STATE("KaleidoRLQPController_RLPos", KaleidoRLQPController_RLPos)
