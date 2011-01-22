bwapi_modules = [
    "AIModule",
#    "Bitmap",
    "Bullet",
    "BulletType",
    "Client",
    "Color",
    "Constants",
    "CoordinateType",
    "DamageType",
    "Error",
    "Event",
    "EventType",
    "ExplosionType",
    "Flag",
    "Force",
    "Game",
    "GameType",
    "Input",
    "Latency",
    "Order",
    "Player",
    "PlayerType",
    "Position",
    "Race",
    "TechType",
    "TilePosition",
    "Unit",
    "UnitCommand",
    "UnitCommandType",
    "UnitSizeType",
    "UnitType",
    "UpgradeType",
    "WeaponType",
]

bwta_modules = [
    "BaseLocation",
    "Chokepoint",
    "Polygon",
    "RectangleArray",
    "Region",
]

bwapi_collision_names = set(['None', 'Normal', 'Unknown', 'Irradiate', 'Corrosive_Acid', 'Lockdown', 'Invalid', 'Stasis_Field', 'Optical_Flare', 'Mind_Control', 'Nuclear_Strike', 'Independent', 'Neutral', 'Spider_Mines', 'Yamato_Gun', 'Restoration', 'Plague', 'EMP_Shockwave', 'Parasite', 'Maelstrom', 'Spawn_Broodlings', 'Feedback', 'Dark_Swarm', 'Consume', 'Ensnare', 'Psionic_Storm', 'Disruption_Web', 'Melee', 'Attack_Move', 'Attack_Unit', 'Build', 'Build_Addon', 'Train', 'Morph', 'Research', 'Upgrade', 'Set_Rally_Position', 'Set_Rally_Unit', 'Move', 'Patrol', 'Hold_Position', 'Stop', 'Follow', 'Gather', 'Return_Cargo', 'Repair', 'Burrow', 'Unburrow', 'Cloak', 'Decloak', 'Siege', 'Unsiege', 'Lift', 'Land', 'Load', 'Unload', 'Unload_All', 'Unload_All_Position', 'Right_Click_Position', 'Right_Click_Unit', 'Halt_Construction', 'Cancel_Construction', 'Cancel_Addon', 'Cancel_Train', 'Cancel_Train_Slot', 'Cancel_Morph', 'Cancel_Research', 'Cancel_Upgrade', 'Use_Tech', 'Use_Tech_Position', 'Use_Tech_Unit', 'Gemini_Missiles', 'Burst_Lasers', 'Longbolt_Missile', 'Acid_Spore', 'Glave_Wurm', 'Seeker_Spores', 'Phase_Disruptor', 'Pulse_Cannon', 'Neutron_Flare', 'Halo_Rockets', 'Subterranean_Spines', 'Fragmentation_Grenade', 'Player', 'RescuePassive', 'PlayerLeft', 'Burrowing'])


def get_templates():
    wrapper_modules = {'BWAPI': ["Player", "Unit", "Force"], 'BWTA': ["Region", "Chokepoint", "BaseLocation"]}
    wrapper_ptrnext_modules = {'BWAPI': ["Position", "TilePosition", "UnitType"]}

    templates = []
    for wrapper_type in ('Set', 'List'):
        for (namespace, modules) in wrapper_modules.items():
            templates += ["%%template (%(module)s%(wrapper_type)s) %(wrapper_type)sWrapper<%(namespace)s::%(module)s*>;"%locals() for module in modules]
        for (namespace, modules) in wrapper_ptrnext_modules.items():
            templates += ["%%template (%(module)s%(wrapper_type)s) %(wrapper_type)sWrapper_PtrNext<%(namespace)s::%(module)s>;"%locals() for module in modules]
    return '\n'.join(templates)

templates = get_templates()





f = open('pybw.i','w')
f.write("""
%module pybw_swig

%include "std_string.i"
%include "std_vector.i"
//%include "std_pair.i"
//%include "std_map.i"
//%include "std_set.i"

%include "std_wrappers.i"
""" + templates + """
%include "bwapi.i"
%include "bwta.i"


%{
#include "helper.h"
#include "heatmap.h"

using namespace BWTA;
%}
%include "helper.h"
%include "heatmap.h"


%{

// Define our own init function, with a simple declaration.
// Declare SWIG_init because it's not declared yet.
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


// Used for event-dispatcher callbacks
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
""")

f.write( "\n//renames\n" )
for m in bwapi_modules:
    f.write("%%ignore BWAPI::%(name)ss::init;\n" % dict(name=m) )

    for cn in bwapi_collision_names:
        f.write("%%rename(%(name)ss_%(collname)s) BWAPI::%(name)ss::%(collname)s;\n" % dict(name=m, collname=cn))


event_types = ['MatchStart', 'MatchEnd', 'MatchFrame', 'MenuFrame', 'SendText', 
    'ReceiveText', 'PlayerLeft', 'NukeDetect', 'UnitDiscover', 'UnitEvade', 'UnitShow', 'UnitHide', 'UnitCreate', 'UnitDestroy', 'UnitMorph', 'UnitRenegade', 'SaveGame', 'None']
for et in event_types:
    f.write("%%rename(EventTypes_%s) BWAPI::EventType::%s;\n" % (et,et))


f.write( "\n// includes\n%{\n" )
for m in bwapi_modules:
    
    f.write("""\t#include "BWAPI/%s.h"\n"""% ( m ) )

for m in bwta_modules:
    f.write("""\t#include "BWTA/%s.h"\n"""% ( m ) )
f.write( "%}\n" )

for m in bwapi_modules:
    f.write("""\t%%include "BWAPI/%s.h"\n"""% ( m ) )

for m in bwta_modules:
    f.write("""\t%%include "BWTA/%s.h"\n"""% ( m ) )

f.close()

