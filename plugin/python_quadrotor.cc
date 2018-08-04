#include "python_quadrotor.h"

#include <iostream>

bool PythonQuadrotor::Initialize() {
  return true;
}

void PythonQuadrotor::Execute(double t, double dt) {
  PyObject* result = ExecutePython(t, dt);
  if (!result) {
    return;
  }
  double up_force, roll_torque, pitch_torque, yaw_torque;
  PyArg_ParseTuple(result, "dddd", &up_force, &roll_torque, &pitch_torque, &yaw_torque);
  Py_DECREF(result);
  SetControlInputs(up_force, roll_torque, pitch_torque, yaw_torque);
}

bool PythonQuadrotor::GoalBased() {
  return false;
}
