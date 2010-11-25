#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "helper.h"
#include <BWTA.h>
#include <BWAPI.h>


BWAPI::Game* getGame()
{
	return BWAPI::Broodwar;
}

extern bool analyzed;	// XXX
extern bool analysis_just_finished; // XXX
void analyzeMap()
{
	BWTA::analyze();
    analyzed   = true;
    analysis_just_finished = true;
}

DWORD WINAPI analyzeMapThreaded_routine()
{
  analyzeMap();
  return 0;
}

void analyzeMapThreaded()
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)analyzeMapThreaded_routine, NULL, 0, NULL);
}

bool isAnalyzed()
{
	return analyzed;
}

void sendText(const char* text)
{
	//BWAPI::Broodwar->sendText("%s", text);
	if (!BWAPI::Broodwar)
	{
		printf("Error: Trying to sendText when game not initialized yet!\n[%s]\n", text);
		return;
	}
	if (strlen(text) >= 80)
	{
		printf("Error: Trying to print text longer than 80 characters (this will crash revisions 3208 or less)\n[%s]\n", text);
		return;
	}

	BWAPI::Broodwar->sendText("%s", text);
	//MessageBoxA(0, "*Match started, <Player: Erez, race=<Race: Protoss>> vs <Player: Auriga Tribe, race=<Race: Protoss>>", 0,0);
  //BWAPI::Broodwar->sendText("%s", "*Match started, <Player: Erez, race=<Race: Protoss>> vs <Player: Auriga Tribe, race=<Race: Protoss>>");
  //BWAPI::Broodwar->sendText("%s", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB");
  //BWAPI::Broodwar->sendText("%s", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB");
	                                 
}