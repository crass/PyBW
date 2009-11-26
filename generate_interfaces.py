modules = [
    "AIModule",
    "Color",
    "Constants",
    "CoordinateType",
    "DamageType",
    "Error",
    "ExplosionType",
    "Flag",
    "Force",
    "Game",
    "Latency",
    "Order",
    "Player",
    "PlayerType",
    "Position",
    "Race",
    "TechType",
    "TilePosition",
    "Unit",
    "UnitSizeType",
    "UnitType",
    "UpgradeType",
    "WeaponType",
]

collision_names = ['None', 'Normal', 'Unknown', 'Irradiate', 'Corrosive_Acid', 'Lockdown', 'Invalid', 'Stasis_Field', 'Optical_Flare', 'Mind_Control', 'Nuclear_Strike', 'Independent', 'Neutral', 'Spider_Mines', 'Yamato_Gun', 'Restoration', 'Plague', 'EMP_Shockwave', 'Parasite', 'Maelstrom', 'Spawn_Broodlings', 'Feedback', 'Dark_Swarm', 'Consume', 'Ensnare', 'Psionic_Storm', 'Disruption_Web']
        



for m in modules:
    f = file(m + '.i', 'w')

    for cn in collision_names:
        f.write("%%rename(%(name)ss_%(collname)s) BWAPI::%(name)ss::%(collname)s;\n" % dict(name=m, collname=cn))

    f.write("""
%%ignore BWAPI::%(name)ss::init;

%%{
#include "BWAPI/%(name)s.h"
%%}
%%include "../BWAPI_Beta_2.3/include/BWAPI/%(name)s.h"
""" % dict(name=m)
    )


f = open("pybw.i",'w')
f.write("""
%module pybw_swig

%include "std_string.i"

%exception UnitSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception PlayerSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception ForceSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception TilePositionSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}


%extend BWAPI::Player {
    UnitSet* getUnits()
    {
        static UnitSet us( self->getUnits() );
        return &us;
    }
}
%ignore BWAPI::Player::getUnits;

%extend BWAPI::Game {
    UnitSet* getAllUnits()
    {
        static UnitSet us( self->getAllUnits() );
        return &us;
    }

    UnitSet* getMinerals()
    {
        static UnitSet us( self->getMinerals() );
        return &us;
    }

    UnitSet* getGeysers()
    {
        static UnitSet us( self->getGeysers() );
        return &us;
    }

    UnitSet* getNeutralUnits()
    {
        static UnitSet us( self->getNeutralUnits() );
        return &us;
    }

    UnitSet* getStaticMinerals()
    {
        static UnitSet us( self->getStaticMinerals() );
        return &us;
    }

    UnitSet* getStaticGeysers()
    {
        static UnitSet us( self->getStaticGeysers() );
        return &us;
    }

    UnitSet* getStaticNeutralUnits()
    {
        static UnitSet us( self->getStaticNeutralUnits() );
        return &us;
    }

    UnitSet* getSelectedUnits()
    {
        static UnitSet us( self->getSelectedUnits() );
        return &us;
    }

    PlayerSet* getPlayers()
    {
        static PlayerSet us( self->getPlayers() );
        return &us;
    }

    ForceSet* getForces()
    {
        static ForceSet us( self->getForces() );
        return &us;
    }

    UnitSet* unitsOnTile(int x, int y) // TODO: deallocate!
    {
        UnitSet* us = new UnitSet( self->unitsOnTile(x, y) );
        return us;
    }

    TilePositionSet* getStartLocations()
    {
        static TilePositionSet us( self->getStartLocations() );
        return &us;
    }

}
%ignore BWAPI::Game::getAllUnits;
%ignore BWAPI::Game::getMinerals;
%ignore BWAPI::Game::getGeysers;
%ignore BWAPI::Game::getNeutralUnits;
%ignore BWAPI::Game::getStaticMinerals;
%ignore BWAPI::Game::getStaticGeysers;
%ignore BWAPI::Game::getStaticNeutralUnits;
%ignore BWAPI::Game::getSelectedUnits;
%ignore BWAPI::Game::getPlayers;
%ignore BWAPI::Game::getForces;
%ignore BWAPI::Game::unitsOnTile;
%ignore BWAPI::Game::getStartLocations;

%extend BWAPI::Force {
    PlayerSet* getPlayers()
    {
        static PlayerSet us( self->getPlayers() );
        return &us;
    }
}
%ignore BWAPI::Force::getPlayers;

%extend BWAPI::Position {
    int getX()
    {
        return self->x();
    }
    int getY()
    {
        return self->y();
    }
}
%ignore BWAPI::Position::x;
%ignore BWAPI::Position::y;

%extend BWAPI::TilePosition {
    int getX()
    {
        return self->x();
    }
    int getY()
    {
        return self->y();
    }
}
%ignore BWAPI::TilePosition::x;
%ignore BWAPI::TilePosition::y;




%{
#include "stdset_wrapper.h"

PyObject* _getSwigUnit(BWAPI::Unit* unit)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(unit), SWIGTYPE_p_BWAPI__Unit, 0 );
}

PyObject* _getSwigPlayer(BWAPI::Player* player)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(player), SWIGTYPE_p_BWAPI__Player, 0 );
}

PyObject* _getSwigPosition(BWAPI::Position* position)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(position), SWIGTYPE_p_BWAPI__Position, 0 );
}


%}
%include "stdset_wrapper.h"


%ignore BWAPI::TechType::getRace;   /* TODO: resolve! */
""")
for m in modules:
    f.write("""%%include "%s"\n"""% (m+'.i') )

f.write("""
%{
using namespace BWAPI;

#ifdef __cplusplus
extern "C"
#endif

SWIGEXPORT 
#if PY_VERSION_HEX >= 0x03000000
PyObject*
#else
void
#endif
SWIG_init(void);

void python_wrap_init()
{
	SWIG_init();
}

Unit* _getUnitFromPtr(long ptr)
{
    return (Unit*)ptr;
}

#include "helper.h"
%}
%include "helper.h"




""")        

f.close()

