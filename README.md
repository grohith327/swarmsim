# Swarmsim

Swarmsim is a lightweight simulator of robotic swarms.
It is flexible and it allows anyone to change the behavior of both robots and supervisor agents.

Currently, Swarmsim support both differential robots (based on the Khepera III) and quadrotors (based on the AscTec Hummingbird).
Swarmsim offers a nice GUI that shows in 3D the behavior of the swarm.

To keep things lightweight, robots perform simple collision avoidance (to get trajectories closer to reality) using the 4 nearest neighbor per default. Communication is not included per se, but one can easily create a new robot type that offers basic broadcast mechanism.

# Install

To compile Swarmsim, FLTK and OpenGL (e.g., freeglut) libraries are needed. It should successfully compile as is on Mac and Linux.

```bash
# For MacOSX: Install XCode and Homebrew.
xcode-select --install
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# Install FLTK (OpenGL should be installed with XCode).
brew install fltk --devel

# For Linux.
sudo apt-get install libfltk1.3-dev freeglut3-dev
sudo apt-get install build-essentials  # For make.
```

# Performance.

Swarmsim provides around a 30-50x speedup w.r.t. realtime when simulating 1000 robots without the GUI, and about 4-6x speedup when showing the GUI (on MacBook Pro 2011 2.6 GHz Intel Core i7 with an NVIDIA GeForce GT 650M).

# Get started.

```bash
make
./swarmsim --help

./swarmsim --timestep=0.05 --nogui --duration=60
./swarmsim --default_supervisor_nrobots=20
```
