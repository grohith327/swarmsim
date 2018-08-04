from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import math
import swarmsim
import random

_ARENA_SIZE = 3.


def start(config_string):
  if not config_string:
    config_string = '2,2'
  num_unicycles, num_quadrotors = [int(v) for v in config_string.split(',')]

  robots = []
  for i in range(num_unicycles):
    x = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
    y = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
    a = random.random() * 2. * math.pi
    robots.append(MyUnicycle(x, y, a, i))

  for i in range(num_unicycles):
    x = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
    y = random.random() * _ARENA_SIZE - _ARENA_SIZE / 2.
    z = random.random() * _ARENA_SIZE / 2.
    a = random.random() * 2. * math.pi
    robots.append(MyQuadrotor(x, y, z, a, 0., 0., i + num_unicycles))

  return robots


class MyUnicycle(swarmsim.Unicycle):

  def initialize(self):
    print('initialize()')
    print(self)

  def execute(self, t, dt):
    print('execute()')
    print(self)
    print(self.neighbors)
    return swarmsim.UnicycleControls(u=0.5, w=1.)


class MyQuadrotor(swarmsim.Quadrotor):

  def initialize(self):
    print('initialize()')
    print(self)

  def execute(self, t, dt):
    print('execute()')
    print(self)
    print(self.neighbors)
    return swarmsim.QuadrotorControls(up_force=9.81 * .5, roll_torque=0., pitch_torque=0., yaw_torque=0.)
