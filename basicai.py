from pybw_swig import *
import random

class EventHandler:
    def __init__(self, broodwar):
        self.broodwar = broodwar

    def onStart(self):
        print "on start"

    def onFrame(self):
        for unit in self.broodwar.getSelectedUnits():
            oldpos = unit.getPosition()
            new_pos = oldpos + Position(random.randrange(20)-10, random.randrange(20)-10)
            unit.rightClick(new_pos)

    def onSendText(self, text):
        print "recieved text: %s" % text

