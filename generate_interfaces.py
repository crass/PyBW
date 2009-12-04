bwapi_modules = [
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

bwta_modules = [
    "BaseLocation",
    "Chokepoint",
    "Polygon",
    "Region",
]

collision_names = ['None', 'Normal', 'Unknown', 'Irradiate', 'Corrosive_Acid', 'Lockdown', 'Invalid', 'Stasis_Field', 'Optical_Flare', 'Mind_Control', 'Nuclear_Strike', 'Independent', 'Neutral', 'Spider_Mines', 'Yamato_Gun', 'Restoration', 'Plague', 'EMP_Shockwave', 'Parasite', 'Maelstrom', 'Spawn_Broodlings', 'Feedback', 'Dark_Swarm', 'Consume', 'Ensnare', 'Psionic_Storm', 'Disruption_Web']
        
def module_include_filename(module_name):
    return 'Temp/%s.i' % module_name

l1 = ["Player", "Unit", "Force"]
l2 = ["Position", "TilePosition"]
l3 = ["Region", "Chokepoint", "BaseLocation"]
templates1 = '\n'.join("%%template (%sSet) SetWrapper<BWAPI::%s*>;"%(x,x) for x in l1)
templates2 = '\n'.join("%%template (%sSet) SetWrapper_PtrNext<BWAPI::%s>;"%(x,x) for x in l2)
templates3 = '\n'.join("%%template (%sSet) SetWrapper<BWTA::%s*>;"%(x,x) for x in l3)
templates = templates1 + templates2 + templates3



for m in bwapi_modules:
    f = file(module_include_filename(m), 'w')

    for cn in collision_names:
        f.write("%%rename(%(name)ss_%(collname)s) BWAPI::%(name)ss::%(collname)s;\n" % dict(name=m, collname=cn))

    f.write("""
    
%%ignore BWAPI::%(name)ss::init;

%%{
#include "BWAPI/%(name)s.h"
%%}
%%include "BWAPI/%(name)s.h"
""" % dict(name=m)
    )


for m in bwta_modules:
    f = file(module_include_filename(m), 'w')

    f.write("""
%%{
#include "BWTA/%(name)s.h"
%%}
%%include "BWTA/%(name)s.h"
""" % dict(name=m)
    )



f = open('pybw.i','w')
f.write("""
%module pybw_swig

%include "std_string.i"
%include "std_vector.i"
//%include "std_pair.i"
//%include "std_map.i"

%include "std_wrappers.i"
""" + templates +
"""

%include "bwapi.i"
%include "bwta.i"


%{

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

#include "helper.h"

// Used for callbacks
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
%include "helper.h"




""")        

for m in bwapi_modules:
    f.write("""%%include "%s"\n"""% (module_include_filename(m)) )

for m in bwta_modules:
    f.write("""%%include "%s"\n"""% (module_include_filename(m)) )



f.close()

