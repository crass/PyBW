#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>

#include "event_dispatcher.h"

static bool analyzed;
static bool analysis_just_finished;
static BWTA::Region* home;
static BWTA::Region* enemy_base;
DWORD WINAPI AnalyzeThread();

class ExampleAIModule : public BWAPI::AIModule
{
  EventDispatcher* event_dispatcher;

public:

  virtual void onStart();
  virtual void onEnd();
  virtual void onFrame();
  virtual bool onSendText(std::string text);
  virtual void onUnitCreate(Unit* unit);
  virtual void onUnitDestroy(Unit* unit);
  virtual void onUnitMorph(Unit* unit);
  virtual void onUnitShow(Unit* unit);
  virtual void onUnitHide(Unit* unit);

  virtual void onPlayerLeft(Player* player);
  virtual void onNukeDetect(Position target);
  virtual void onUnitRenegade(Unit* unit);


  void drawStats(); //not part of BWAPI::AIModule
  void showPlayers();
  void showForces();
  std::map<BWAPI::Unit*,BWAPI::UnitType> buildings;
};