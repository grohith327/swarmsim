from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import collections


# Motion controls that are returned to the C++ code.
Controls = collections.namedtuple('Controls', ['u', 'w'])


# Cannot use Robot(object) as it interferes with PyInstance_New.
# TODO: Fix this.
class GroundRobot:

  def __init__(self):
    pass

  def execute(self, t, dt):
    return Controls(0.5, 1.)
