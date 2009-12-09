from pybw_swig import *
import random
import pybw_repl
import math

from pybw_event_handler import PyBW_EventHandler

class EventHandler(PyBW_EventHandler):
    def __init__(self, broodwar):
        PyBW_EventHandler.__init__(self, broodwar)
        self.broodwar = broodwar

        bw = self.broodwar
        self.minerals = list(bw.minerals)
        self.player = self.broodwar.self
        self.race = self.player.race

        self.main_centers = [u for u in self.player.units if u.type == self.race.center]
        if self.main_centers:
            self.main_center = self.main_centers[0]

            self.mineral_queue = []
            for mineral in self.minerals:
                distance_to_center = mineral.position.getDistance( self.main_center.position )
                self.mineral_queue.append(( distance_to_center, mineral ))
            self.mineral_queue.sort()

        else:
            self.main_center = None


    def onStart(self):
        try:
            PyBW_EventHandler.onStart(self)

        except Exception, e:
            print "onStart error", e
                        

    def onFrame(self):
        try:
            PyBW_EventHandler.onFrame(self)
            bw = self.broodwar

            if self.main_center:
                self.main_center.train( self.race.worker )    # doesn't work for zerg

                inactive_probes = [u for u in bw.self.units if u.type.isWorker and u.order == PlayerGuard]

                for probe in inactive_probes:
                    mineral = self.mineral_queue.pop(0)
                    probe.rightClick( mineral[1] )
                    self.mineral_queue.append( mineral ) 

        except Exception, e:
            print "onFrame error: %s", e
