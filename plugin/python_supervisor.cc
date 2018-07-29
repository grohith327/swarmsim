#include "python_supervisor.h"
#include "python_ground_robot.h"

#include <iostream>
#include <sstream>
#include <Python.h>

#include "gflags/gflags.h"
#include "util/utils.h"

DECLARE_int32(nthreads);
DEFINE_int32(python_supervisor_nrobots, 4, "Number of robots to initialize.");
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
         << "imp.load_source('robot', r'" << FLAGS_python_supervisor_script << "')";
  PyRun_SimpleString(buffer.str().c_str());

  PyObject* module = PyImport_ImportModule("robot");
  if (!module) {
    std::cerr << "Unable to load module at \"" << FLAGS_python_supervisor_script << "\"" << std::endl;
    return false;
  }

  PyObject* robot_class = PyObject_GetAttrString(module, "GroundRobot");
  if (!robot_class) {
    std::cerr << "Unable to find class \"Robot\"" << std::endl;
    return false;
  }
  Py_DECREF(module);

  for (int i = 0; i < FLAGS_python_supervisor_nrobots; ++i) {
    Robot* robot;
    robot = CreateRobot("PythonGroundRobot");

    PyObject* instance = PyInstance_New(robot_class, NULL, NULL);
    if (!instance) {
      std::cerr << "Unable to call \"Robot\".__init__()" << std::endl;
      PyErr_Print();
      return false;
    }
    static_cast<PythonGroundRobot*>(robot)->SetInstance(instance);

    // Random positions.
    robot->SetPosition(RandomUniform() * kArenaSize - kArenaSize / 2.0,
                       RandomUniform() * kArenaSize - kArenaSize / 2.0,
                       RandomUniform() * M_PI * 2.0);
    // Assign type. Robots of different types appear in different colors.
    robot->SetType(i);
  }

  Py_DECREF(robot_class);
  return true;
}

void PythonSupervisor::Destroy() {
  Py_Finalize();
}
