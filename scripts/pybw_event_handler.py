import random
import pybw_repl
from pybw_swig import *
import time

#try:
#    console_client = pybw_repl.ConsoleClient()
#except:
#    print "Error loading ConsoleClient"
#    console_client = None

class PyBW_EventHandler:
    def __init__(self, broodwar):
        d = dict(globals())
        d['broodwar'] = broodwar
        d['bw'] = broodwar
        #console_client.start_repl(d)

    def onStart(self):
        print "PyBW is online!"

    def onEnd(self, is_winner):
        #console_client.kill_server()
        pass

    def onFrame(self):
        #try:
        #    if console_client:
        #        console_client.on_frame()
        #except Exception, e:
        #    print "onFrame error", e
        pass


    def onSendText(self, text):
        print "recieved text: %s" % text

    def onPlayerLeft(self, player):
        print "OnPlayerLeft: %r" % player

    def onNukeDetect(self):
        print "onNukeDetect"

    def onUnitCreate(self, unit):
        print "onUnitCreate: %r" % unit

