#ifndef _TEMPLATE_GROUND_ROBOT_H
#define _TEMPLATE_GROUND_ROBOT_H

#include "core/ground_robot.h"
#include "core/robot.h"
#include "display/window.h"
#include "util/registerer.h"

class TemplateGroundRobot : public GroundRobot {
  REGISTER("TemplateGroundRobot", Robot);

 public:
  void Draw(VisualizerWindow* window) override;

 private:
  bool Initialize() override;
  void Execute(double t, double dt) override;

  // You can set the following function to return either true
  // or false. If it returns true, the Execute() function
  // needs to call SetGoal(x, y), the underlying controller
  // will find appropriate forward and rotational controls to reach
  // the specified goal point. If it return false, the Execute()
  // function needs to call SetControlInputs(u, w) directly.
  bool GoalBased() override { return false; }
};

#endif
