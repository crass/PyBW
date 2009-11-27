from pybw_swig import *
import random
import pybw_repl

class EventHandler:
    def __init__(self, broodwar):
        self.broodwar = broodwar

    def onStart(self):
        print "on start"
        try:
            d = dict(globals())
            d['broodwar'] = self.broodwar
            d['bw'] = self.broodwar
            self.console_client = pybw_repl.ConsoleClient(d)
        except Exception, e:
            print "onStart error", e

    def onEnd(self):
        pass

    def onFrame(self):
        #for unit in self.broodwar.getSelectedUnits():
        #    oldpos = unit.getPosition()
        #    new_pos = oldpos + Position(random.randrange(20)-10, random.randrange(20)-10)
        #    unit.rightClick(new_pos)
        try:
            self.console_client.on_frame()
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

    def onUnitDestroy(self, unit):
        print "onUnitDestroy: %r" % unit

    def onUnitMorph(self, unit):
        print "onUnitMorph: %r" % unit

    def onUnitShow(self, unit):
        print "onUnitShow: %r" % unit

    def onUnitHide(self, unit):
        print "onUnitHide: %r" % unit

    def onUnitRenegade(self, unit):
        print "onUnitRenegade: %r" % unit


