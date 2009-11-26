#include <string>

#include <Python.h>

#include <BWAPI.h>
using namespace BWAPI;

#include "helper.h"

class EventDispatcher
{

public:

	EventDispatcher();
	~EventDispatcher();

	void onStart();
	void onEnd();
	void onFrame();
	void onSendText(std::string text);

	void onPlayerLeft(Player* player);
	void onNukeDetect(Position target);
	void onUnitCreate(Unit* unit);
	void onUnitDestroy(Unit* unit);
	void onUnitMorph(Unit* unit);
	void onUnitShow(Unit* unit);
	void onUnitHide(Unit* unit);
	void onUnitRenegade(Unit* unit);

private:

	PyObject* event_handler;
	void LoadEventHandler();
};

