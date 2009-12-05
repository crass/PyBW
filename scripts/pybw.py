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


def Force_repr(self):
    return "<Force: %s, players=%s>" % (self.name, list(self.players))
pybw_swig.Force.__repr__ = Force_repr

def Player_repr(self):
    return "<Player: %s, race=%s>" % (self.name, self.race)
pybw_swig.Player.__repr__ = Player_repr

def repr_by_class_and_name(self):
    return "<%s: %s>" % (self.__class__.__name__, self.name)

pybw_swig.UnitType.__repr__ = repr_by_class_and_name
pybw_swig.PlayerType.__repr__ = repr_by_class_and_name
pybw_swig.TechType.__repr__ = repr_by_class_and_name
pybw_swig.UpgradeType.__repr__ = repr_by_class_and_name
pybw_swig.WeaponType.__repr__ = repr_by_class_and_name
pybw_swig.DamageType.__repr__ = repr_by_class_and_name
pybw_swig.ExplosionType.__repr__ = repr_by_class_and_name
pybw_swig.Race.__repr__ = repr_by_class_and_name
pybw_swig.Order.__repr__ = repr_by_class_and_name
pybw_swig.UnitSizeType.__repr__ = repr_by_class_and_name

def Unit_repr(self):
    return "<Unit: %s, player=%s>" % (self.type.name, self.player.name)
pybw_swig.Unit.__repr__ = Unit_repr

def Error_repr(self):
    return "<Error: %s>" % self.toString()
pybw_swig.Error.__repr__ = Error_repr

# ToDo ?
# * BaseLocation
# * Chokepoint
# * Region
# * Polygon


print "Fixing __eq__ and __hash__ methods in classes"



def eq_by_id(self, other):
    return self.id == other.id
def ne_by_id(self, other):
    return self.id != other.id
def hash_by_id(self):
    return hash(self.id)


pybw_swig.Player.__hash__ = hash_by_id
pybw_swig.Player.__eq__ = eq_by_id
pybw_swig.Player.__ne__ = ne_by_id

pybw_swig.UnitType.__hash__ = hash_by_id
pybw_swig.UnitType.__eq__ = eq_by_id
pybw_swig.UnitType.__ne__ = ne_by_id

pybw_swig.PlayerType.__hash__ = hash_by_id
pybw_swig.PlayerType.__eq__ = eq_by_id
pybw_swig.PlayerType.__ne__ = ne_by_id

pybw_swig.TechType.__hash__ = hash_by_id
pybw_swig.TechType.__eq__ = eq_by_id
pybw_swig.TechType.__ne__ = ne_by_id

pybw_swig.UpgradeType.__hash__ = hash_by_id
pybw_swig.UpgradeType.__eq__ = eq_by_id
pybw_swig.UpgradeType.__ne__ = ne_by_id

pybw_swig.WeaponType.__hash__ = hash_by_id
pybw_swig.WeaponType.__eq__ = eq_by_id
pybw_swig.WeaponType.__ne__ = ne_by_id

pybw_swig.DamageType.__hash__ = hash_by_id
pybw_swig.DamageType.__eq__ = eq_by_id
pybw_swig.DamageType.__ne__ = ne_by_id

pybw_swig.ExplosionType.__hash__ = hash_by_id
pybw_swig.ExplosionType.__eq__ = eq_by_id
pybw_swig.ExplosionType.__ne__ = ne_by_id

pybw_swig.Race.__hash__ = hash_by_id
pybw_swig.Race.__eq__ = eq_by_id
pybw_swig.Race.__ne__ = ne_by_id

pybw_swig.Order.__hash__ = hash_by_id
pybw_swig.Order.__eq__ = eq_by_id
pybw_swig.Order.__ne__ = ne_by_id

pybw_swig.UnitSizeType.__hash__ = hash_by_id
pybw_swig.UnitSizeType.__eq__ = eq_by_id
pybw_swig.UnitSizeType.__ne__ = ne_by_id

pybw_swig.Error.__hash__ = hash_by_id
pybw_swig.Error.__eq__ = eq_by_id
pybw_swig.Error.__ne__ = ne_by_id



def Force_eq(self, other):
    raise NotImplementedError("Cannot compare forces. Compare force.name instead")
def Force_hash(self):
    raise NotImplementedError("Cannot calculate hash for force")
pybw_swig.Force.__hash__ = Force_hash
pybw_swig.Force.__eq__ = Force_eq
pybw_swig.Force.__ne__ = Force_eq


def Position_hash(self):
    return hash((self.x, self.y))
pybw_swig.Position.__hash__ = Position_hash

def TilePosition_hash(self):
    return hash((self.x, self.y))
pybw_swig.TilePosition.__hash__ = TilePosition_hash

# ToDo ?
# * BaseLocation
# * Chokepoint
# * Region
# * Polygon

print "Adding some utility methods"
def Pos_iter(self):
    yield self.x
    yield self.y
pybw_swig.Position.__iter__ = Pos_iter
pybw_swig.TilePosition.__iter__ = Pos_iter

def TilePosition_toWalkable(self):
    return self.__class__( self.x*4, self.y*4 )
def TilePosition_fromWalkable(self):
    return self.__class__( self.x/4, self.y/4 )

pybw_swig.TilePosition.toWalkable = TilePosition_toWalkable
pybw_swig.TilePosition.fromWalkable = TilePosition_fromWalkable

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


