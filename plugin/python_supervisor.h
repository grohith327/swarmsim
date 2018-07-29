#ifndef _PYTHON_SUPERVISOR_H
#define _PYTHON_SUPERVISOR_H

#include "core/supervisor.h"
#include "util/registerer.h"

class PythonSupervisor : public Supervisor {
  REGISTER("PythonSupervisor", Supervisor);

 private:
  bool Initialize() override;
  void Destroy() override;
};

#endif
