import inspect

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

print "Adding __repr__ and __str__ method to classes"

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
    return "<Player: %s, race=%s>" % (self.name, self.race.name)
def Player_str(self):
    return "P:%s(%s)" % (self.name, self.race.name)
pybw_swig.Player.__repr__ = Player_repr
pybw_swig.Player.__str__ = Player_str

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
    if self is None or other is None:
        return self is other
    return self.id == other.id
def ne_by_id(self, other):
    if self is None or other is None:
        return self is not other
    return self.id != other.id
def hash_by_id(self):
    assert self is not None
    return hash(self.id)


pybw_swig.Player.__hash__ = hash_by_id
pybw_swig.Player.__eq__ = eq_by_id
pybw_swig.Player.__ne__ = ne_by_id

pybw_swig.PlayerType.__hash__ = hash_by_id
pybw_swig.PlayerType.__eq__ = eq_by_id
pybw_swig.PlayerType.__ne__ = ne_by_id

pybw_swig.Unit.__hash__ = hash_by_id
pybw_swig.Unit.__eq__ = eq_by_id
pybw_swig.Unit.__ne__ = ne_by_id

pybw_swig.UnitType.__hash__ = hash_by_id
pybw_swig.UnitType.__eq__ = eq_by_id
pybw_swig.UnitType.__ne__ = ne_by_id

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

for c in set(get_all_classes(pybw_swig)):
    deget_class(c)



print "Creating event handler"

import pybw_event_handler
event_handler = pybw_event_handler.PyBW_EventHandler(0)
event_handler.listeners.append( pybw_event_handler.VerboseEventHandler() )

def reload_event_handler():
    global event_handler
    try:
        event_handler = None
        import pybw_event_handler
        reload(pybw_event_handler)
        pybw_event_handler._reload()
        event_handler = pybw_event_handler.PyBW_EventHandler(0)
    except Exception, e:
        print "error", e


print "Creating console"

import pybw_repl


class consoleManager(object):
    def onConnect(self):
        game = pybw_swig.getGame()
        self.consoleClient = pybw_repl.ConsoleClient()
        self.consoleClient.start_repl(dict(game=game, swig=pybw_swig))
    def onMatchFrame(self):
        self.consoleClient.on_frame()

consoleManager = consoleManager()
event_handler.listeners.append( consoleManager )

try:
    import exampleai
    event_handler.listeners.append( exampleai.ExampleAI() )
    #import erezai
    #event_handler.listeners.append( erezai.ErezAI() )
except ImportError, e:
    print "Error importing AI:", e
except Exception, e:
    print "Error running AI:", e

print "PyBW module Initialization complete"


