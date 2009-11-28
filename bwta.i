%template(PositionList) std::vector<BWAPI::Position>;


%rename(TA_getStartLocation) getStartLocation;
%rename(TA_getNearestBaseLocation) getNearestBaseLocation;

BWTA::BaseLocation* getStartLocation(BWAPI::Player* player);
BWTA::BaseLocation* getNearestBaseLocation(BWAPI::TilePosition position);

%ignore BWTA::getStartLocation;
%ignore BWTA::getNearestBaseLocation;




%newobject TA_getRegions;
%newobject TA_getChokepoints;
%newobject TA_getBaseLocations;
%newobject TA_getStartLocations;
%{
    RegionSet* TA_getRegions()
    {
        return new RegionSet( BWTA::getRegions() );
    }
    ChokepointSet* TA_getChokepoints()
    {
        return new ChokepointSet( BWTA::getChokepoints() );
    }
    BaseLocationSet* TA_getBaseLocations()
    {
        return new BaseLocationSet( BWTA::getBaseLocations() );
    }
    BaseLocationSet* TA_getStartLocations()
    {
        return new BaseLocationSet( BWTA::getStartLocations() );
    }    
%}
RegionSet* TA_getRegions();
ChokepointSet* TA_getChokepoints();
BaseLocationSet* TA_getBaseLocations();
BaseLocationSet* TA_getStartLocations();

%ignore BWTA::getRegions;
%ignore BWTA::getChokepoints;
%ignore BWTA::getBaseLocations;
%ignore BWTA::getStartLocations;




%newobject BWTA::Region::getChokepoints;
%newobject BWTA::Region::getBaseLocations;

%extend BWTA::Region {
    ChokepointSet* getChokepoints()
    {
        return new ChokepointSet( self->getChokepoints() );
    }

    BaseLocationSet* getBaseLocations()
    {
        return new BaseLocationSet( self->getBaseLocations() );
    }
}
%ignore BWTA::Region::getChokepoints;
%ignore BWTA::Region::getBaseLocations;





%{
#include "BWTA.h"
%}
%include "BWTA.h"


%{
using namespace BWTA;
%}
