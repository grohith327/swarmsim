#ifndef _PYTHON_GROUND_ROBOT_H
#define _PYTHON_GROUND_ROBOT_H

#include "core/ground_robot.h"
#include "core/robot.h"
#include "display/window.h"
#include "util/registerer.h"

class PythonGroundRobot : public GroundRobot {
  REGISTER("PythonGroundRobot", Robot);

 private:
  bool Initialize() override;
  void Execute(double t, double dt) override;
  bool GoalBased() override { return false; }
};

#endif
