import pybw_swig
import random
import time

class VerboseEventHandler(object):
    def onConnect(self):
        self.game = pybw_swig.getGame() 
        print "Connected to broodwar!"
    def onDisconnect(self):
        print "Disconnected from broodwar!"
    
    def onMatchStart(self):
        print "Match started!"
    def onMatchEnd(self, is_winner):
        print "Match ended, I %s!" % ( ['lost', 'won'][is_winner] )
    def onSendText(self, text):
        print "I said: '%s'" % text
    def onReceiveText(self, player, text):
        print "%s said: '%s'" % (player.name, text)
    def onPlayerLeft(self, player):
        print "OnPlayerLeft: %r" % player
    def onUnitCreate(self, unit):
        if self.game.getFrameCount() > 1:
            print "onUnitCreate: %r" % unit
    def onUnitDestroy(self, unit):
        print "onUnitDestroy: %r" % unit
    def onSaveGame(self, gameName):
        print "onSaveGame to", gameName


class PyBW_EventHandler(object):
    def __init__(self, broodwar):
        self.broodwar = broodwar
        self.listeners = []

    def _dispatchEvent(self, event, *args):
        for listener in self.listeners:
            if hasattr(listener, event):
                try:
                    getattr(listener, event)(*args)
                except Exception, e:
                    print "Error dispatching event %s to %s: %s"%( event, listener, e)

    def onConnect(self):
        self._dispatchEvent("onConnect")
    def onDisconnect(self):
        self._dispatchEvent("onDisconnect")

    def onMatchStart(self):
        self._dispatchEvent("onMatchStart")
    def onMatchEnd(self, is_winner):
        self._dispatchEvent("onMatchEnd", is_winner)
    def onMatchFrame(self):
        self._dispatchEvent("onMatchFrame")
    def onMenuFrame(self):
        self._dispatchEvent("onMenuFrame")
    def onSendText(self, text):
        self._dispatchEvent("onSendText", text)
    def onReceiveText(self, player, text):
        self._dispatchEvent("onReceiveText", text)
    def onPlayerLeft(self, player):
        self._dispatchEvent("onPlayerLeft", player)
    def onNukeDetect(self, target):
        self._dispatchEvent("onNukeDetect", target)
    def onUnitDiscover(self, unit):
        self._dispatchEvent("onUnitDiscover", unit)
    def onUnitEvade(self, unit):
        self._dispatchEvent("onUnitEvade", unit)
    def onUnitShow(self, unit):
        self._dispatchEvent("onUnitShow", unit)
    def onUnitHide(self, unit):
        self._dispatchEvent("onUnitHide", unit)
    def onUnitCreate(self, unit):
        self._dispatchEvent("onUnitCreate", unit)
    def onUnitDestroy(self, unit):
        self._dispatchEvent("onUnitDestroy", unit)
    def onUnitMorph(self, unit):
        self._dispatchEvent("onUnitMorph", unit)
    def onUnitRenegade(self, unit):
        self._dispatchEvent("onUnitRenegade", unit)
    def onSaveGame(self, gameName):
        self._dispatchEvent("onSaveGame", gameName)

