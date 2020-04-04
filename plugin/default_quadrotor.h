#ifndef _DEFAULT_QUADROTOR_H
#define _DEFAULT_QUADROTOR_H

#include <iostream>
#include "core/quadrotor.h"
#include "core/robot.h"
#include "display/window.h"
#include "util/registerer.h"

class DefaultQuadrotor : public Quadrotor {
  REGISTER("DefaultQuadrotor", Robot);

 public:
  DefaultQuadrotor();
  void Draw(VisualizerWindow* window) override;

  double positions[121][2];
  int count;

 private:
  bool Initialize() override;
  void Execute(double t, double dt) override;
  bool GoalBased() override { return true; }

  double goal_x_;
  double goal_y_;
  double goal_z_;

};

#endif
