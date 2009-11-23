#include "helper.h"


//class BWAPI::Game* BWAPI::Broodwar;
//std::queue<CommandQueueItem> CommandQueue;

BWAPI::Game* getBroodwar()
{
	return BWAPI::Broodwar;
}

/*

void unit_Move(BWAPI::Unit* unit, int x, int y)
{
	BWAPI::Position pos(x,y);
	CommandQueueItem item;

	item.unit = unit;
	item.action = 0;
	item.pos = pos;
	
	CommandQueue.push( item );
}

CommandQueueItem popCommandQueue()
{
	CommandQueueItem item;
	item.unit = NULL;

	if( !CommandQueue.empty() ) {
      item = CommandQueue.front();
      CommandQueue.pop();
    }
	return item;
}*/