#include <set>

#include <python.h>

#include "BWAPI/Unit.h"
#include "BWAPI/Player.h"
#include "BWAPI/Force.h"
#include "BWAPI/TilePosition.h"

#include "BWTA.h"

#pragma warning(disable: 4512)

class UnitSet
{
	std::set<BWAPI::Unit*> units;
	std::set<BWAPI::Unit*>::iterator iterator;

public:

	UnitSet(std::set<BWAPI::Unit*>& _units)
		: units(_units)
	{
		__iter__();
	}

	UnitSet& __iter__()	// XXX not thread-safe
	{
		iterator = units.begin();
		return *this;
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
	std::set<BWAPI::Player*> players;
	std::set<BWAPI::Player*>::iterator iterator;

public:
	PlayerSet(std::set<BWAPI::Player*>& _players)
		: players(_players)
	{
		__iter__();
	}

	PlayerSet& __iter__()	// XXX not thread-safe
	{
		iterator = players.begin();
		return *this;
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
	std::set<BWAPI::Force*> forces;
	std::set<BWAPI::Force*>::iterator iterator;

public:
	ForceSet(std::set<BWAPI::Force*>& _forces)
		: forces(_forces)
	{
		__iter__();
	}

	ForceSet& __iter__()	// XXX not thread-safe
	{
		iterator = forces.begin();
		return *this;
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
	std::set<BWAPI::TilePosition> tilepositions;
	std::set<BWAPI::TilePosition>::iterator iterator;

public:
	TilePositionSet(std::set<BWAPI::TilePosition>& _tilepositions)
		: tilepositions(_tilepositions)
	{
		__iter__();
	}

	TilePositionSet& __iter__()	// XXX not thread-safe
	{
		iterator = tilepositions.begin();
		return *this;
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


// BWTA

class RegionSet
{
	const std::set<BWTA::Region*> regions;
	std::set<BWTA::Region*>::const_iterator iterator;

public:

	RegionSet(const std::set<BWTA::Region*>& _regions)
		: regions(_regions)
	{
		__iter__();
	}

	RegionSet& __iter__()	// XXX not thread-safe
	{
		iterator = regions.begin();
		return *this;
	}

	int __len__()
	{
		return regions.size();
	}

	BWTA::Region* next()
	{
		if (iterator == regions.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};

class ChokepointSet
{
	const std::set<BWTA::Chokepoint*> set;
	std::set<BWTA::Chokepoint*>::const_iterator iterator;

public:

	ChokepointSet(const std::set<BWTA::Chokepoint*>& _set)
		: set(_set)
	{
		__iter__();
	}

	ChokepointSet& __iter__()	// XXX not thread-safe
	{
		iterator = set.begin();
		return *this;
	}

	int __len__()
	{
		return set.size();
	}

	BWTA::Chokepoint* next()
	{
		if (iterator == set.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};

class BaseLocationSet
{
	const std::set<BWTA::BaseLocation*> set;
	std::set<BWTA::BaseLocation*>::const_iterator iterator;

public:

	BaseLocationSet(const std::set<BWTA::BaseLocation*>& _set)
		: set(_set)
	{
		__iter__();
	}

	BaseLocationSet& __iter__()	// XXX not thread-safe
	{
		iterator = set.begin();
		return *this;
	}

	int __len__()
	{
		return set.size();
	}

	BWTA::BaseLocation* next()
	{
		if (iterator == set.end())
		{
			return NULL;
		}

		return *(iterator++);
	}
};


#pragma warning(default: 4512)
