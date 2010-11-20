#include <string>

#include <Python.h>

#include <BWAPI.h>

//#include "helper.h"

class EventDispatcher
{

public:

	EventDispatcher();
	~EventDispatcher();

	void dispatchEvent(BWAPI::Event* e);

	void onMatchStart();
	void onMatchEnd(bool isWinner);
	void onMatchFrame();
	void onMenuFrame();
	void onSendText(std::string text);
    void onReceiveText(BWAPI::Player* player, std::string text);
    void onPlayerLeft(BWAPI::Player* player);
    void onNukeDetect(BWAPI::Position target);
    void onUnitDiscover(BWAPI::Unit* unit);
    void onUnitEvade(BWAPI::Unit* unit);
    void onUnitShow(BWAPI::Unit* unit);
    void onUnitHide(BWAPI::Unit* unit);
    void onUnitCreate(BWAPI::Unit* unit);
    void onUnitDestroy(BWAPI::Unit* unit);
    void onUnitMorph(BWAPI::Unit* unit);
    void onUnitRenegade(BWAPI::Unit* unit);
    void onSaveGame(std::string gameName);

	void onConnect(BWAPI::Game* game);
	void onDisconnect();

	void reload();

private:

	PyObject* event_handler;
	void LoadEventHandler(bool call_reload = false);
};

