import random
import pybw_repl
from pybw_swig import *

d = dict(globals())
console_client = pybw_repl.ConsoleClient()

class PyBW_EventHandler:
    def __init__(self, broodwar):
        self.broodwar = broodwar

        d['broodwar'] = self.broodwar
        d['bw'] = self.broodwar
        console_client.start_repl(d)


    def onStart(self):
        print "PyBW is online!"

    def onEnd(self, is_winner):
        print "Match ended. I " + (['lost','won'][is_winner])

    def onFrame(self):
        #for unit in self.broodwar.getSelectedUnits():
        #    oldpos = unit.getPosition()
        #    new_pos = oldpos + Position(random.randrange(20)-10, random.randrange(20)-10)
        #    unit.rightClick(new_pos)
        try:
            console_client.on_frame()
        except AttributeError:
            pass
        except Exception, e:
            print "onFrame error", e


    def onSendText(self, text):
        print "recieved text: %s" % text

    def onPlayerLeft(self, player):
        print "OnPlayerLeft: %r" % player

    def onNukeDetect(self):
        print "onNukeDetect"

    def onUnitCreate(self, unit):
        print "onUnitCreate: %r" % unit

