#include <Python.h>

#include <BWAPI.h>

BWAPI::Game* getBroodwar();


// Used for callbacks
PyObject* _getSwigUnit(BWAPI::Unit* unit);
PyObject* _getSwigPlayer(BWAPI::Player* player);
PyObject* _getSwigPosition(BWAPI::Position* position);

//void setBroodwarPtr(unsigned int ptr);

/*typedef struct CommandQueueItem
{
	BWAPI::Unit* unit;
	int action;
	BWAPI::Position pos;
} CommandQueueItem;*/

//void unit_Move(BWAPI::Unit* unit, int x, int y);

//CommandQueueItem popCommandQueue();
