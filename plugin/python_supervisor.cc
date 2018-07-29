#include "python_supervisor.h"

#include <Python.h>

#include "gflags/gflags.h"
#include "util/utils.h"

DEFINE_int32(python_supervisor_nrobots, 4, "Number of robots to initialize.");

namespace {
// Control constants.
constexpr double kArenaSize = 3.0;
}  // namespace

bool PythonSupervisor::Initialize() {
  Py_Initialize();

  for (int i = 0; i < FLAGS_python_supervisor_nrobots; ++i) {
    Robot* robot;
    robot = CreateRobot("PythonGroundRobot");
    // Random positions.
    robot->SetPosition(RandomUniform() * kArenaSize - kArenaSize / 2.0,
                       RandomUniform() * kArenaSize - kArenaSize / 2.0,
                       RandomUniform() * M_PI * 2.0);
    // Assign type. Robots of different types appear in different colors.
    robot->SetType(i);
  }
  return true;
}

void PythonSupervisor::Destroy() {
  Py_Finalize();
}
