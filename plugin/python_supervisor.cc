#include "python_supervisor.h"
#include "python_unicycle.h"

#include <Python.h>

#include <iostream>
#include <sstream>

#include "gflags/gflags.h"
#include "util/utils.h"

DECLARE_int32(nthreads);
DEFINE_string(python_supervisor_arg, "", "String argument passed to the start() method.");
DEFINE_string(python_supervisor_script, "", "Python script filename.");

namespace {
// Control constants.
constexpr double kArenaSize = 3.0;
}  // namespace

bool PythonSupervisor::Initialize() {
  FLAGS_nthreads = 1;  // Because of the GIL.
  Py_Initialize();

  if (FLAGS_python_supervisor_script.empty()) {
    std::cerr << "Python script driving the robots must be set with --python_supervisor_script" << std::endl;
    return false;
  }
  // TODO: Start Python script.
  std::ostringstream buffer;
  buffer << "import imp\n"
         << "imp.load_source('swarmsim', r'./plugin/swarmsim.py')\n"
         << "imp.load_source('robot', r'" << FLAGS_python_supervisor_script << "')";
  PyRun_SimpleString(buffer.str().c_str());

  PyObject* module = PyImport_ImportModule("robot");
  if (!module) {
    std::cerr << "Unable to load module at \"" << FLAGS_python_supervisor_script << "\"" << std::endl;
    return false;
  }

  PyObject* start_function = PyObject_GetAttrString(module, "start");
  if (!start_function) {
    std::cerr << "Unable to find \"start\" function" << std::endl;
    return false;
  }
  PyObject* start_arg = PyString_FromString(FLAGS_python_supervisor_arg.c_str());
  if (!start_arg) {
    PyErr_Print();
    return false;
  }
  PyObject* args = PyTuple_Pack(1, start_arg);
  if (!args) {
    PyErr_Print();
    return false;
  }
  Py_DECREF(start_arg);
  PyObject* robot_list = PyObject_CallObject(start_function, args);
  if (!robot_list) {
    PyErr_Print();
    return false;
  }
  Py_DECREF(args);
  Py_XDECREF(start_function);

  // Go through the robot list.
  const int n = PyList_Size(robot_list);
  for (int i = 0; i < n; ++i) {
    PyObject* instance = PyList_GetItem(robot_list, i);
    if (!instance) {
      PyErr_Print();
      return false;
    }
    PyObject* result = PyObject_CallMethod(instance, "type", nullptr);
    if (!result) {
      PyErr_Print();
      return false;
    }
    Robot* robot = CreateRobot(PyString_AsString(result));
    Py_DECREF(result);

    PyObject* x = PyObject_GetAttrString(instance, "x");
    PyObject* y = PyObject_GetAttrString(instance, "y");
    PyObject* z = PyObject_GetAttrString(instance, "z");
    PyObject* yaw = PyObject_GetAttrString(instance, "yaw");
    PyObject* pitch = PyObject_GetAttrString(instance, "pitch");
    PyObject* roll = PyObject_GetAttrString(instance, "roll");
    PyObject* type = PyObject_GetAttrString(instance, "identifier");
    if (!(x && y && z && yaw && pitch && roll && type)) {
      PyErr_Print();
      return false;
    }
    if (PyObject_SetAttrString(instance, "flying", PyBool_FromLong(robot->IsFlying())) != 0) {
      PyErr_Print();
      return false;
    }

    robot->SetPosition(PyFloat_AsDouble(x),
                       PyFloat_AsDouble(y),
                       PyFloat_AsDouble(z),
                       PyFloat_AsDouble(roll),
                       PyFloat_AsDouble(pitch),
                       PyFloat_AsDouble(yaw));
    robot->SetType(PyLong_AsLong(type));
    robot->SetPythonInstance(instance);
    Py_DECREF(x);
    Py_DECREF(y);
    Py_DECREF(z);
    Py_DECREF(yaw);
    Py_DECREF(pitch);
    Py_DECREF(roll);
    Py_DECREF(type);

    // Call initialize method.
    result = PyObject_CallMethod(instance, "initialize", nullptr);
    if (!result) {
      std::cerr << "Unable to call \"Robot.initialize()\"" << std::endl;
      PyErr_Print();
      return false;
    }
    Py_DECREF(result);
  }
  return true;
}

void PythonSupervisor::Destroy() {
  Py_Finalize();
}
