//%newobject BWAPI::Player::getUnits;

%extend BWAPI::Player {
    UnitSet* getUnits()
    {
        return new UnitSet( self->getUnits() );
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
    UnitSet* getAllUnits()
    {
        return new UnitSet( self->getAllUnits() );
    }

    UnitSet* getMinerals()
    {
        return new UnitSet( self->getMinerals() );
    }

    UnitSet* getGeysers()
    {
        return new UnitSet( self->getGeysers() );
    }

    UnitSet* getNeutralUnits()
    {
        return new UnitSet( self->getNeutralUnits() );
    }

    UnitSet* getStaticMinerals()
    {
        return new UnitSet( self->getStaticMinerals() );
    }

    UnitSet* getStaticGeysers()
    {
        return new UnitSet( self->getStaticGeysers() );
    }

    UnitSet* getStaticNeutralUnits()
    {
        return new UnitSet( self->getStaticNeutralUnits() );
    }

    UnitSet* getSelectedUnits()
    {
        return new UnitSet( self->getSelectedUnits() );
    }

    PlayerSet* getPlayers()
    {
        return new PlayerSet( self->getPlayers() );
    }

    ForceSet* getForces()
    {
        return new ForceSet( self->getForces() );
    }

    UnitSet* unitsOnTile(int x, int y) // TODO: deallocate!
    {
        return new UnitSet( self->unitsOnTile(x, y) );
    }

    TilePositionSet* getStartLocations()
    {
        return new TilePositionSet( self->getStartLocations() );
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
    PlayerSet* getPlayers()
    {
        return new PlayerSet( self->getPlayers() );
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
using namespace BWAPI;
%}
