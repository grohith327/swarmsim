from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import collections

# Motion controls that are returned to the C++ code.
UnicycleControls = collections.namedtuple('UnicycleControls', ['u', 'w'])
QuadrotorControls = collections.namedtuple('QuadrotorControls', ['up_force', 'roll_torque', 'pitch_torque', 'yaw_torque'])


# Base Robot class.
class Robot(object):
  def __init__(self, x, y, z, yaw, pitch, roll, identifier):
    self.x = x
    self.y = y
    self.z = z
    self.yaw = yaw
    self.pitch = pitch
    self.roll = roll
    self.identifier = identifier
    self.flying = None
    self.neighbors = []

  def __repr__(self):
    return 'Robot[x={}, y={}, z={}, yaw={}, pitch={}, roll={}, identifier={}, flying={}]'.format(
        self.x, self.y, self.z, self.yaw, self.pitch, self.roll, self.identifier, self.flying)

  def type(self):
    raise NotImplementedError()

  def initialize(self):
    pass

  def execute(self, t, dt):
    pass


# Derive from this class to build a unicycle robot.
class Unicycle(Robot):

  def __init__(self, x, y, yaw, identifier):
    super(Unicycle, self).__init__(x, y, 0., yaw, 0., 0., identifier)

  def type(self):
    return 'PythonUnicycle'


# Derive from this class to build a unicycle robot.
class Quadrotor(Robot):

  def type(self):
    return 'PythonQuadrotor'
