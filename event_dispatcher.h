#include <string>

#include <Python.h>

#include <BWAPI.h>

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

	void onPlayerLeft(BWAPI::Player* player);
	void onNukeDetect(BWAPI::Position target);
	void onUnitCreate(BWAPI::Unit* unit);
	void onUnitDestroy(BWAPI::Unit* unit);
	void onUnitMorph(BWAPI::Unit* unit);
	void onUnitShow(BWAPI::Unit* unit);
	void onUnitHide(BWAPI::Unit* unit);
	void onUnitRenegade(BWAPI::Unit* unit);

	void reload();

private:

	PyObject* event_handler;
	void LoadEventHandler(bool call_reload = false);
};

