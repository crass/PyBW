#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>

#include "event_dispatcher.h"

static bool terrainAnalyzed;
static bool analysisJustFinished;
static BWTA::Region* home;
static BWTA::Region* enemyBase;
DWORD WINAPI AnalyzeThread();

class AIModuleImpl : public BWAPI::AIModule
{
  EventDispatcher* event_dispatcher;
  HANDLE analyzingThreadHandle;

public:

  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();

  virtual bool onSendText(std::string text);
  virtual void onUnitCreate(BWAPI::Unit* unit);
  virtual void onUnitDestroy(BWAPI::Unit* unit);
  virtual void onUnitMorph(BWAPI::Unit* unit);
  virtual void onUnitShow(BWAPI::Unit* unit);
  virtual void onUnitHide(BWAPI::Unit* unit);

  virtual void onPlayerLeft(BWAPI::Player* player);
  virtual void onNukeDetect(BWAPI::Position target);
  virtual void onUnitRenegade(BWAPI::Unit* unit);


  //not part of BWAPI::AIModule
  void drawTerrainAnalysis();
  void drawStats();
  void printPlayers();
  void printForces();
};