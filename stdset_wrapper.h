#include <set>

#include <python.h>

#include "BWAPI/Unit.h"
#include "BWAPI/Player.h"
#include "BWAPI/Force.h"
#include "BWAPI/TilePosition.h"

//for( theIterator = charList.begin(); theIterator != charList.end(); theIterator++ ) {
//		cout << *theIterator;


class UnitSet
{
	std::set<BWAPI::Unit*>& units;
	std::set<BWAPI::Unit*>::iterator iterator;

public:
	UnitSet(std::set<BWAPI::Unit*>& _units)
		: units(_units)
	{
		__iter__();
	}

	UnitSet* __iter__()	// XXX not thread-safe
	{
		iterator = units.begin();
		return this;
	}

	int __len__()
	{
		return units.size();
	}

	BWAPI::Unit* next()
	{
		if (iterator == units.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};

class PlayerSet
{
	std::set<BWAPI::Player*>& players;
	std::set<BWAPI::Player*>::iterator iterator;

public:
	PlayerSet(std::set<BWAPI::Player*>& _players)
		: players(_players)
	{
		__iter__();
	}

	PlayerSet* __iter__()	// XXX not thread-safe
	{
		iterator = players.begin();
		return this;
	}

	int __len__()
	{
		return players.size();
	}

	BWAPI::Player* next()
	{
		if (iterator == players.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};


class ForceSet
{
	std::set<BWAPI::Force*>& forces;
	std::set<BWAPI::Force*>::iterator iterator;

public:
	ForceSet(std::set<BWAPI::Force*>& _forces)
		: forces(_forces)
	{
		__iter__();
	}

	ForceSet* __iter__()	// XXX not thread-safe
	{
		iterator = forces.begin();
		return this;
	}

	int __len__()
	{
		return forces.size();
	}

	BWAPI::Force* next()
	{
		if (iterator == forces.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};



class TilePositionSet
{
	std::set<BWAPI::TilePosition>& tilepositions;
	std::set<BWAPI::TilePosition>::iterator iterator;

public:
	TilePositionSet(std::set<BWAPI::TilePosition>& _tilepositions)
		: tilepositions(_tilepositions)
	{
		__iter__();
	}

	TilePositionSet* __iter__()	// XXX not thread-safe
	{
		iterator = tilepositions.begin();
		return this;
	}

	int __len__()
	{
		return tilepositions.size();
	}

	BWAPI::TilePosition* next()
	{
		if (iterator == tilepositions.end())
		{
			return NULL;
		}

		return &*(iterator++);
	}
};


