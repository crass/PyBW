

%rename(TA_getStartLocation) getStartLocation;
%rename(TA_getNearestBaseLocation) getNearestBaseLocation;

BWTA::BaseLocation* getStartLocation(BWAPI::Player* player);
BWTA::BaseLocation* getNearestBaseLocation(BWAPI::TilePosition position);

%ignore BWTA::getStartLocation;
%ignore BWTA::getNearestBaseLocation;


%rename(BWTA_Polygon) BWTA::Polygon;
const std::set<BWTA::Polygon*>& BWTA::getUnwalkablePolygons();  // TODO: SetWrapper
BWTA::Polygon* BWTA::getNearestUnwalkablePolygon(int x, int y);
BWTA::Polygon* BWTA::getNearestUnwalkablePolygon(BWAPI::TilePosition tileposition);
%ignore BWTA::getNearestUnwalkablePolygon;
%ignore BWTA::getUnwalkablePolygons;


%{
#include "BWTA.h"

using namespace BWTA;

%}
%include "BWTA.h"




%newobject TA_getRegions;
%newobject TA_getChokepoints;
%newobject TA_getBaseLocations;
%newobject TA_getStartLocations;
%{
    SetWrapper<BWTA::Region*>* TA_getRegions()
    {
        return new SetWrapper<BWTA::Region*>( BWTA::getRegions() );
    }
    SetWrapper<BWTA::Chokepoint*>* TA_getChokepoints()
    {
        return new SetWrapper<BWTA::Chokepoint*>( BWTA::getChokepoints() );
    }
    SetWrapper<BWTA::BaseLocation*>* TA_getBaseLocations()
    {
        return new SetWrapper<BWTA::BaseLocation*>( BWTA::getBaseLocations() );
    }
    SetWrapper<BWTA::BaseLocation*>* TA_getStartLocations()
    {
        return new SetWrapper<BWTA::BaseLocation*>( BWTA::getStartLocations() );
    }

%}
SetWrapper<BWTA::Region*>* TA_getRegions();
SetWrapper<BWTA::Chokepoint*>* TA_getChokepoints();
SetWrapper<BWTA::BaseLocation*>* TA_getBaseLocations();
SetWrapper<BWTA::BaseLocation*>* TA_getStartLocations();

%ignore BWTA::getRegions;
%ignore BWTA::getChokepoints;
%ignore BWTA::getBaseLocations;
%ignore BWTA::getStartLocations;




%newobject BWTA::Region::getChokepoints;
%newobject BWTA::Region::getBaseLocations;

%extend BWTA::Region {
    SetWrapper<BWTA::Chokepoint*>* getChokepoints()
    {
        return new SetWrapper<BWTA::Chokepoint*>( self->getChokepoints() );
    }

    SetWrapper<BWTA::BaseLocation*>* getBaseLocations()
    {
        return new SetWrapper<BWTA::BaseLocation*>( self->getBaseLocations() );
    }
}
%ignore BWTA::Region::getChokepoints;
%ignore BWTA::Region::getBaseLocations;



%newobject BWTA::BaseLocation::getMinerals;
%newobject BWTA::BaseLocation::getStaticMinerals;
%newobject BWTA::BaseLocation::getGeysers;

%extend BWTA::BaseLocation {
    SetWrapper<BWAPI::Unit*>* getMinerals()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getMinerals() );
    }

    SetWrapper<BWAPI::Unit*>* getStaticMinerals()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getStaticMinerals() );
    }

    SetWrapper<BWAPI::Unit*>* getGeysers()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getGeysers() );
    }
}
%ignore BWTA::BaseLocation::getMinerals;
%ignore BWTA::BaseLocation::getStaticMinerals;
%ignore BWTA::BaseLocation::getGeysers;

