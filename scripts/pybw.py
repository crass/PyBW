import sys
import types
import inspect

class FileFlusher:
    def __init__(self, *args):
        self.f = file(*args)
    def write(self, *args):
        self.f.write(*args)
        self.f.flush()
    def writelines(self, *args):
        self.f.write(*args)
        self.f.flush()

sys.stdout = FileFlusher("c:\\pybw_out.txt",'w')
sys.stderr = FileFlusher("c:\\pybw_err.txt",'w')


print "Importing built-in module (provided by DLL, needed for debugging only)"
import _pybw_swig


print "Importing swig module (python file)"
import pybw_swig

print "Converting all 'getSomething' into 'something'..."
def deget_class(c):
    for name in c.__dict__.keys():
        obj = getattr(c, name)
        if not inspect.ismethod(obj):
            continue
        argspec = inspect.getargspec(obj)
        if len(argspec.args) != 1:  # not really get?
            continue
        if argspec.varargs != None or argspec.keywords != None: # not really get?
            continue
        if name.startswith('_') or name == 'next':  # kinda hackish..
            continue
        if name == 'getID':
            prop_name = 'id'
        elif name.startswith('get'):            
            prop_name = name[3].lower() + name[4:]
        else:
            prop_name = name

        if prop_name!=name and hasattr(c, prop_name):
            print "Cannot deget property %s->%s of class %s: Already exists" % (name, prop_name, c)
            continue    # don't overwrite existing... In the future combine somehow?

        setattr(c, prop_name, property(obj) )
            

        
def get_all_classes(m):
    for name in m.__dict__.keys():
        obj = getattr(m, name)
        if inspect.isclass(obj) and not name.startswith('_'):
            yield obj

for c in get_all_classes(pybw_swig):
    deget_class(c)
    


print "Creating a broodwar instance (of Game)"

#old_Game = pybw_swig.Game
#class Game(old_Game):
#    def __init__(self):
#        self.this = pybw_swig.getBroodwar()

broodwar = pybw_swig.getBroodwar()

print "Adding __repr__ method to classes"

def Position_repr(self):
    return "Position(%s, %s)" % (self.x, self.y)
pybw_swig.Position.__repr__ = Position_repr

def TilePosition_repr(self):
    return "TilePosition(%s, %s)" % (self.x, self.y)
pybw_swig.TilePosition.__repr__ = TilePosition_repr

def UnitType_repr(self):
    return "<UnitType: %s>" % self.name
pybw_swig.UnitType.__repr__ = UnitType_repr

def Player_repr(self):
    return "<Player: %s, race=%s>" % (self.name, self.race)
pybw_swig.Player.__repr__ = Player_repr

def Unit_repr(self):
    return "<Unit: %s, player=%s>" % (self.type.name, self.player.name)
pybw_swig.Unit.__repr__ = Unit_repr

def Race_repr(self):
    return "<Race: %s>" % (self.name)
pybw_swig.Race.__repr__ = Race_repr

def Order_repr(self):
    return "<Order: %s>" % (self.name)
pybw_swig.Order.__repr__ = Order_repr


print "Fixing __eq__ methods in classes"
def Player_eq(self, other):
    return self.id == other.id
pybw_swig.Player.__eq__ = Player_eq

def Force_eq(self, other):
    raise NotImplementedError("Cannot compare forces. Compare force.name instead")
pybw_swig.Force.__eq__ = Force_eq


print "Redirecting output to broodwar console"

class PrintToBroodwar(object):
    def __init__(self, broodwar, prefix, next_stream = None):
        self.broodwar = broodwar
        self.prefix = prefix
        self.next_stream = next_stream
    def write(self, s):
        s = str(s)
        if s.strip():
            self.broodwar.sendText(self.prefix + s )
        if self.next_stream:
            self.next_stream.write(s)
    def writelines(self, l):
        self.write( ('\n'+self.prefix).join(lines))
        if self.next_stream:
            self.next_stream.writelines(l)

    softspace = 0

sys.stdout = PrintToBroodwar(broodwar, '> ', sys.stdout)
sys.stderr = PrintToBroodwar(broodwar, '! ', sys.stderr)


print "Creating event handler"

try:
    import basicai
    event_handler = basicai.EventHandler(broodwar)
except Exception, e:
    print "error", e

def reload_event_handler():
    global event_handler
    try:
        event_handler = None
        import basicai
        reload(basicai)
        event_handler = basicai.EventHandler(broodwar)
    except Exception, e:
        print "error", e


print "PyBW module Initialization complete"


