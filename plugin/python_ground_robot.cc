#include "python_ground_robot.h"

#include <iostream>
#include <sstream>

#include <Python.h>

#include "gflags/gflags.h"

DEFINE_string(python_ground_robot_script, "", "Python script filename.");

bool PythonGroundRobot::Initialize() {
  if (FLAGS_python_ground_robot_script.empty()) {
    std::cerr << "Python script driving the robots must be set with --python_ground_robot_script" << std::endl;
    return false;
  }
  // TODO: Start Python script.
  std::ostringstream buffer;
  buffer << "import imp\n"
         << "imp.load_source('robot', r'" << FLAGS_python_ground_robot_script << "')";
  PyRun_SimpleString(buffer.str().c_str());

  PyObject* module = PyImport_ImportModule("robot");
  if (!module) {
    std::cerr << "Unable to load module at \"" << FLAGS_python_ground_robot_script << "\"" << std::endl;
    return false;
  }

  PyObject* robot_class = PyObject_GetAttrString(module, "Robot");
  if (!robot_class) {
    std::cerr << "Unable to find class \"Robot\"" << std::endl;
    return false;
  }
  Py_DECREF(module);

  PyObject* instance = PyInstance_New(robot_class, NULL, NULL);
  if (!instance) {
    std::cerr << "Unable to call \"Robot\".__init__()" << std::endl;
    PyErr_Print();
    return false;
  }



  return true;
}

void PythonGroundRobot::Execute(double t, double dt) {
  // TODO: Call Python.
  // SetControlInputs(double u, double w)
}
