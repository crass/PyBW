//#include <Python.h>
#include <BWAPI.h>

BWAPI::Game* getGame();
void analyzeMap();
void analyzeMapThreaded();
bool isAnalyzed();
void sendText(const char* text);

// Used for callbacks
/*PyObject* _getSwigUnit(BWAPI::Unit* unit);
PyObject* _getSwigPlayer(BWAPI::Player* player);
PyObject* _getSwigPosition(BWAPI::Position* position);*/

