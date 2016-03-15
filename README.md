# Swarmsim

Swarmsim is a lightweight simulator of robotic swarms.
It is flexible and it allows anyone to change the behavior of both robots and supervisor agents.

Currently, Swarmsim support both differential robots (based on the Khepera III) and quadrotors (based on the AscTec Hummingbird).
Swarmsim offers a nice GUI that shows in 3D the behavior of the swarm.

To keep things lightweight, robots perform simple collision avoidance (to get trajectories closer to reality) using the 4 nearest neighbor per default. Communication is not included per se, but one can easily create a new robot type that offers basic broadcast mechanism.

# Install

To compile Swarmsim, FLTK and OpenGL (e.g., freeglut) libraries are needed. It should successfully compile as is on Mac and Linux.

# Performance.

Swarmsim provides around a 30-50x speedup when simulating 1000 robots without the GUI, and about 4-6x speedup when showing the GUI.

# Get started.

```bash
make
./swarmsim --help

./swarmsim --timestep=0.05 --nogui --duration=60
./swarmsim --default_supervisor_nrobots=20
```
