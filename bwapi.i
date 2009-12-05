
// Player

%newobject BWAPI::Player::getUnits;

%extend BWAPI::Player {
    SetWrapper<BWAPI::Unit*>* getUnits()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getUnits() );
    }
    BWAPI::PlayerType playerType()
    {
        return self->playerType();
    }
    BWAPI::Race getRace()
    {
        return self->getRace();
    }
    BWAPI::TilePosition getStartLocation()
    {
        return self->getStartLocation();
    }
}
%ignore BWAPI::Player::getUnits;
%ignore BWAPI::Player::playerType;
%ignore BWAPI::Player::getStartLocation;
%ignore BWAPI::Player::getRace;



%newobject BWAPI::Unit::getLoadedUnits;
%newobject BWAPI::Unit::getTrainingQueue;

// Unit
%extend BWAPI::Unit {
    ListWrapper<BWAPI::Unit*>* getLoadedUnits()
    {
        return new ListWrapper<BWAPI::Unit*>( self->getLoadedUnits() );
    }

    ListWrapper_PtrNext<BWAPI::UnitType>* getTrainingQueue()
    {
        return new ListWrapper_PtrNext<BWAPI::UnitType>( self->getTrainingQueue() );
    }
}
%ignore BWAPI::Unit::getLoadedUnits;
%ignore BWAPI::Unit::getTrainingQueue;



// Game


%newobject BWAPI::Game::unitsOnTile;
%newobject BWAPI::Game::getAllUnits;
%newobject BWAPI::Game::getMinerals;
%newobject BWAPI::Game::getGeysers;
%newobject BWAPI::Game::getNeutralUnits;
%newobject BWAPI::Game::getStaticMinerals;
%newobject BWAPI::Game::getStaticGeysers;
%newobject BWAPI::Game::getStaticNeutralUnits;
%newobject BWAPI::Game::getSelectedUnits;
%newobject BWAPI::Game::getPlayers;
%newobject BWAPI::Game::getForces;
%newobject BWAPI::Game::getStartLocations;


%extend BWAPI::Game {
    SetWrapper<BWAPI::Unit*>* getAllUnits()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getAllUnits() );
    }

    SetWrapper<BWAPI::Unit*>* getMinerals()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getMinerals() );
    }

    SetWrapper<BWAPI::Unit*>* getGeysers()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getGeysers() );
    }

    SetWrapper<BWAPI::Unit*>* getNeutralUnits()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getNeutralUnits() );
    }

    SetWrapper<BWAPI::Unit*>* getStaticMinerals()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getStaticMinerals() );
    }

    SetWrapper<BWAPI::Unit*>* getStaticGeysers()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getStaticGeysers() );
    }

    SetWrapper<BWAPI::Unit*>* getStaticNeutralUnits()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getStaticNeutralUnits() );
    }

    SetWrapper<BWAPI::Unit*>* getSelectedUnits()
    {
        return new SetWrapper<BWAPI::Unit*>( self->getSelectedUnits() );
    }

    SetWrapper<BWAPI::Player*>* getPlayers()
    {
        return new SetWrapper<BWAPI::Player*>( self->getPlayers() );
    }

    SetWrapper<BWAPI::Force*>* getForces()
    {
        return new SetWrapper<BWAPI::Force*>( self->getForces() );
    }

    SetWrapper<BWAPI::Unit*>* unitsOnTile(int x, int y) // TODO: deallocate!
    {
        return new SetWrapper<BWAPI::Unit*>( self->unitsOnTile(x, y) );
    }

    SetWrapper_PtrNext<BWAPI::TilePosition>* getStartLocations()
    {
        return new SetWrapper_PtrNext<BWAPI::TilePosition>( self->getStartLocations() );
    }

    bool canBuildHere(BWAPI::Unit* builder, BWAPI::TilePosition position, BWAPI::UnitType type)
    {
        return self->canBuildHere(builder, position, type);
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
%ignore BWAPI::Game::canBuildHere;


// Force


%newobject BWAPI::Force::getPlayers;


%extend BWAPI::Force {
    SetWrapper<BWAPI::Player*>* getPlayers()
    {
        return new SetWrapper<BWAPI::Player*>( self->getPlayers() );
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






%ignore BWAPI::TechType::getRace;   /* TODO: resolve! */


%{
#include "BWAPI.h"

using namespace BWAPI;
%}

%include "BWAPI.h"

%template(PositionVector) std::vector<BWAPI::Position>;

