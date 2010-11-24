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
	printf("%s", text);
}