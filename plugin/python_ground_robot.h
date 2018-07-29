#ifndef _PYTHON_GROUND_ROBOT_H
#define _PYTHON_GROUND_ROBOT_H

#include <Python.h>

#include "core/ground_robot.h"
#include "core/robot.h"
#include "display/window.h"
#include "util/registerer.h"

class PythonGroundRobot : public GroundRobot {
  REGISTER("PythonGroundRobot", Robot);

 public:
  void SetInstance(PyObject* instance);

 private:
  bool Initialize() override;
  void Execute(double t, double dt) override;
  bool GoalBased() override { return false; }

  // Python object.
  PyObject* instance_;
};

#endif
