from pybw_swig import *
import random
import pybw_repl

from pybw_event_handler import PyBW_EventHandler

class EventHandler(PyBW_EventHandler):

    def onFrame(self):
        PyBW_EventHandler.onFrame(self)
        #for unit in self.broodwar.getSelectedUnits():
        #    oldpos = unit.getPosition()
        #    new_pos = oldpos + Position(random.randrange(20)-10, random.randrange(20)-10)
        #    unit.rightClick(new_pos)


