from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


# Cannot use Robot(object) as it interferes with PyInstance_New.
# TODO: Fix this.
class Robot():

  def __init__(self):
    print('Initialize...')

  def execute(t, dt):
    pass
