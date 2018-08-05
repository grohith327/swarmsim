from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import math
import swarmsim
import swarmui
import random


from OpenGL.GL import *
from OpenGL.GLU import *

_ARENA_SIZE = 3.


class Supervisor(swarmsim.Supervisor):

  def initialize(self, arg_string):
    if not arg_string:
      arg_string = '2,2,2'
    num_unicycles, num_quadrotors, num_bicycles = [int(v) for v in arg_string.split(',')]

    self._robots = []
    for i in range(num_unicycles):
      x = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      y = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      a = random.random() * 2. * math.pi
      self._robots.append(MyUnicycle(0, .20, 0., i))

    for i in range(num_quadrotors):
      x = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      y = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      z = random.random() * _ARENA_SIZE / 2.
      a = random.random() * 2. * math.pi
      self._robots.append(MyQuadrotor(x, y, z, a, 0., 0., i + num_unicycles))

    for i in range(num_bicycles):
      x = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      y = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
      a = random.random() * 2. * math.pi
      self._robots.append(MyBicycle(0., 0., 0., i + num_unicycles + num_quadrotors))

    return self._robots

  def execute(self, t, dt):
    # We can modify the state of the different robots.
    if t > 5.:
      self._robots[0].x = 0.

  def draw(self, t):
    # We can draw things in OpenGL.
    # PyOpenGL generally works but has issues for some commands.
    swarmui.glColor3f(0.4, 0., 0.)
    swarmui.glLineWidth(2)
    swarmui.glBegin(GL_LINES)
    glVertex3f(0., 0., 0.)
    glVertex3f(1., 0., 0.)
    swarmui.glEnd()


class MyUnicycle(swarmsim.Unicycle):

  def initialize(self):
    print('initialize():', self)

  def execute(self, t, dt):
    return swarmsim.UnicycleControls(u=0.2, w=0.5)


class MyBicycle(swarmsim.Bicycle):

  def initialize(self):
    print('initialize():', self)

  def execute(self, t, dt):
    return swarmsim.BicycleControls(v=.5, phi=math.pi / 3.)


class MyQuadrotor(swarmsim.Quadrotor):

  def initialize(self):
    print('initialize():', self)

  def execute(self, t, dt):
    return swarmsim.QuadrotorControls(up_force=9.81 * .5, roll_torque=0., pitch_torque=0., yaw_torque=0.)
