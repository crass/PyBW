from pybw_swig import *
import random

class EventHandler:
    def __init__(self, broodwar):
        self.broodwar = broodwar

    def onStart(self):
        print "on start"

    def onFrame(self):
        #self_player = self.broodwar.self()
        for unit in self.broodwar.getSelectedUnits():
            oldpos = unit.getPosition()
            #new_pos = Position( oldpos.x() + 10, oldpos.y() + 10)
            new_pos = oldpos + Position(random.randrange(20)-10, random.randrange(20)-10)
            unit.rightClick(new_pos)

    def onSendText(self, text):
        print "recieved text: %s" % text

#event_handler = EventHandler()

def go():
    
    try:
        self = broodwar.self()
        units = self.getUnits2()
        l = []
        units.startIter()
        while not units.isIterEnd():
            x = units.iter()
            l.append(x)

        #import sys
        #sys.argv = [""]
        #from idlelib import idle
        print "ErezAI!!"

        for x in l:
            #print x
            oldpos = x.getPosition()
            pos_x = oldpos.x2()
            pos_y = oldpos.y2()
            #print (pos_x, pos_y)
            new_pos = pybw.Position( pos_x + 1, pos_y + 1)
            #print x.orderSelect
            #print pybw.unit_Move(x, pos_x+10, pos_y)
            #print x.attackMove(new_pos)
            #print new_pos
            #pybw.attackMove3(x, pos_x+1, pos_y+1)
            break
        
        #file('c:\\tempai.txt','w').write( str( dir(broodwar.getAllUnits())))
        #print units.getUnits()[4]
        #raise Exception("Yo")
    except Exception, e:
        print "Error:" + str(e)

