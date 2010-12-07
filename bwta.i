/*
TODO
-bwta::getRegion
-bwta::getNearestChokepoint
bwta::getShortestPath

Chokepoint
	-> regions
	-> sides
*/

%{
#include "BWTA.h"

using namespace BWTA;

%}

%rename(TA_Polygon) BWTA::Polygon;

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


%extend BWTA::Chokepoint
{
    BWTA::Region* getRegionA()
    {
        return self->getRegions().first;
    }
    BWTA::Region* getRegionB()
    {
        return self->getRegions().second;
    }
    BWAPI::Position getSideA()
    {
        return self->getSides().first;
    }
    BWAPI::Position getSideB()
    {
        return self->getSides().second;
    }
}
%ignore BWTA::Chokepoint::getRegions;
%ignore BWTA::Chokepoint::getSides;


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





%newobject TA_getRegions;
%newobject TA_getChokepoints;
%newobject TA_getBaseLocations;
%newobject TA_getStartLocations;
%newobject TA_getUnwalkablePolygons;
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

    SetWrapper<BWTA::Polygon*>* TA_getUnwalkablePolygons()
    {
        return new SetWrapper<BWTA::Polygon*>( BWTA::getUnwalkablePolygons() );
    }

    BWTA::Region* TA_getRegion(int x, int y)
    {
        return BWTA::getRegion(x, y);
    }
    BWTA::Region* TA_getRegion(BWAPI::TilePosition tileposition)
    {
        return BWTA::getRegion(tileposition);
    }

    BWTA::Chokepoint* TA_getNearestChokepoint(int x, int y)
    {
        return BWTA::getNearestChokepoint(x, y);
    }

    BWTA::Chokepoint* TA_getNearestChokepoint(BWAPI::TilePosition tileposition)
    {
        return BWTA::getNearestChokepoint(tileposition);
    }

    BWTA::Chokepoint* TA_getNearestChokepoint(BWAPI::Position position)
    {
        return BWTA::getNearestChokepoint(position);
    }
        
    BWTA::BaseLocation* TA_getStartLocation(BWAPI::Player* player)
    {
        return BWTA::getStartLocation(player);
    }
    BWTA::BaseLocation* TA_getNearestBaseLocation(BWAPI::TilePosition position)
    {
        return BWTA::getNearestBaseLocation(position);
    }

    BWTA::Polygon* TA_getNearestUnwalkablePolygon(int x, int y)
    {
        return BWTA::getNearestUnwalkablePolygon(x,y);
    }
    BWTA::Polygon* TA_getNearestUnwalkablePolygon(BWAPI::TilePosition tileposition)
    {
        return BWTA::getNearestUnwalkablePolygon(tileposition);
    }


%}
SetWrapper<BWTA::Region*>* TA_getRegions();
SetWrapper<BWTA::Chokepoint*>* TA_getChokepoints();
SetWrapper<BWTA::BaseLocation*>* TA_getBaseLocations();
SetWrapper<BWTA::BaseLocation*>* TA_getStartLocations();
BWTA::Region* TA_getRegion(int x, int y);
BWTA::Region* TA_getRegion(BWAPI::TilePosition tileposition);
BWTA::Chokepoint* TA_getNearestChokepoint(int x, int y);
BWTA::Chokepoint* TA_getNearestChokepoint(BWAPI::TilePosition tileposition);
BWTA::Chokepoint* TA_getNearestChokepoint(BWAPI::Position position);
BWTA::BaseLocation* TA_getStartLocation(BWAPI::Player* player);
BWTA::BaseLocation* TA_getNearestBaseLocation(BWAPI::TilePosition position);
BWTA::Polygon* TA_getNearestUnwalkablePolygon(int x, int y);
BWTA::Polygon* TA_getNearestUnwalkablePolygon(BWAPI::TilePosition tileposition);

%ignore BWTA::getRegions;
%ignore BWTA::getChokepoints;
%ignore BWTA::getBaseLocations;
%ignore BWTA::getStartLocations;
%ignore BWTA::getRegion;
%ignore BWTA::getNearestChokepoint;
%ignore BWTA::getStartLocation;
%ignore BWTA::getNearestBaseLocation;
%ignore BWTA::getNearestUnwalkablePolygon;
%ignore BWTA::getUnwalkablePolygons;


%include "BWTA.h"

