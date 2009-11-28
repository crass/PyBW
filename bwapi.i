%extend BWAPI::Player {
    UnitSet* getUnits()
    {
        static UnitSet us( self->getUnits() );
        return &us;
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






%ignore BWAPI::TechType::getRace;   /* TODO: resolve! */


%{
using namespace BWAPI;
%}
