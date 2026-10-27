#include "KaleidoRLQPController_Initial.h"

#include <KaleidoRLQPController.h>

void KaleidoRLQPController_Initial::configure(const mc_rtc::Configuration &) {}

void KaleidoRLQPController_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.activateQPControl(true);
  ctl.activateTorqueControl(false);
  ctl.activateContactConstraints(true);
  std::map<std::string, std::vector<double>> defaultPostureTarget;
  int i = 0;
  for (const auto & joint_name : ctl.robot().refJointOrder()) {
    defaultPostureTarget[joint_name] = {ctl.rlRuntime().q_zero()(i)};
    i++;
  }
  ctl.postureTask->target(defaultPostureTarget);
  ctl.solver().addTask(ctl.postureTask);
}

bool KaleidoRLQPController_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  return false;
}

void KaleidoRLQPController_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoRLQPController &>(ctl_);
  ctl.solver().removeTask(ctl.postureTask);
}

EXPORT_SINGLE_STATE("KaleidoRLQPController_Initial", KaleidoRLQPController_Initial)
