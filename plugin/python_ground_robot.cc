#include "python_ground_robot.h"

#include <iostream>

bool PythonGroundRobot::Initialize() {
  return true;
}

void PythonGroundRobot::SetInstance(PyObject* instance) {
  instance_ = instance;
}

void PythonGroundRobot::Execute(double t, double dt) {
  // TODO: Call Python.
  PyObject* result = PyObject_CallMethod(instance_, "execute", "(ff)", t, dt);
  if (!result) {
    std::cerr << "Unable to call \"Robot.execute()\"" << std::endl;
    return;
  }

  double u, w;
  PyArg_ParseTuple(result, "dd", &u, &w);
  Py_DECREF(result);

  SetControlInputs(u, w);
}
