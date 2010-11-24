import pybw_swig
import random
import time
import traceback

class VerboseEventHandler(object):
    def _announce(self, text):
        #pybw_swig.sendText(text)
        print '>',text
    def onConnect(self):
        self.game = pybw_swig.getGame() 
        print "Connected to broodwar!"
    def onDisconnect(self):
        print "Disconnected from broodwar!"
    
    def onMatchStart(self):
        self._announce("The map is %s, a %d player map"%(self.game.mapName, len(list(self.game.startLocations))) )
        if self.game.isReplay:
            self._announce("List of players in this replay:")
            for p in self.game.players:
                if not p.isNeutral and not len(list(p.units)) == 0:
                    self._announce("* %s, playing %s"%(p.name, p.race.name))
        else:
            self._announce("*Match started, %r vs %r"%(self.game.self, self.game.enemy))
    def onMatchEnd(self, is_winner):
        print "Match ended%s" % ( ['.', ', I won!'][is_winner] )
    def onSendText(self, text):
        print "I said: '%s'" % text
    def onReceiveText(self, player, text):
        print "%s said: '%s'" % (player.name, text)
    def onPlayerLeft(self, player):
        print "OnPlayerLeft: %r" % player
    def onUnitCreate(self, unit):
        if self.game.getFrameCount() > 1:
            # if we are in a replay, then we will print out the build order
            if self.game.isReplay:
                if (unit.type.isBuilding and unit.player.isNeutral == False):
                    seconds = self.game.frameCount / 24
                    self._announce("%.2d:%.2d: %s builds a %s"%(seconds/60, seconds%60, unit.player.name, unit.type.name))
            else:
                self._announce("onUnitCreate: %r" % unit)
    def onUnitDestroy(self, unit):
        self._announce("onUnitDestroy: %r" % unit)
    def onSaveGame(self, gameName):
        print "onSaveGame to", gameName
    def onUnitMorph(self, unit):
        # if we are in a replay, then we will print out the build order
        if self.game.isReplay:
            if (unit.type.isBuilding and unit.player.isNeutral == False):
                seconds = self.game.frameCount / 24
                self._announce("%.2d:%.2d: %s builds a %s"%(seconds/60, seconds%60, unit.player.name, unit.type.name))


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
                    print "Error dispatching event %s to %s:"%( event, listener )
                    traceback.print_exc()

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

