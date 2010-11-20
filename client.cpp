#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

#include <BWAPI.h>
#include <BWAPI\Client.h>
#include <BWTA.h>

#include <windows.h>

#include <string>

#include <Python.h>

#include "event_dispatcher.h"

using namespace BWAPI;

void drawStats();
void drawBullets();
void drawVisibilityData();
void drawTerrainData();
void showPlayers();
void showForces();
bool show_bullets;
bool show_visibility_data;

bool analyzed;
bool analysis_just_finished;
BWTA::Region* home;
BWTA::Region* enemy_base;
DWORD WINAPI AnalyzeThread();

void reconnect()
{
  while(!BWAPIClient.connect())
  {
    Sleep(1000);
  }
}


void add_workdir_to_pythonpath()
{
	PyRun_SimpleString("import sys; import os; sys.path.insert(0, os.getcwd()); import pybw;");
}


void python_wrap_init();
void init()
{
	BWAPI::BWAPI_init();
	if (Py_IsInitialized())
	{
		MessageBoxA(0, "Python already initialized on init!", 0, 0);
	}
	else
	{
		Py_Initialize();
		python_wrap_init();
		// Import pybw (before event-listener), get any error message on console
		PyRun_SimpleString("import pybw");
	}
}
void uninit()
{
	if (Py_IsInitialized())
	{
		Py_Finalize();
	}
	else
	{
		MessageBoxA(0, "Python not initialized on uninit!", 0, 0);
	}
}


int main(int argc, const char* argv[])
{
  init();
  EventDispatcher event_dispatcher;

  printf("Connecting...");
  reconnect();
  event_dispatcher.onConnect(BWAPI::Broodwar);
  while(true)
  {
    printf("waiting to enter match\n");
    while (!Broodwar->isInGame())
    {
      BWAPI::BWAPIClient.update();
      if (!BWAPI::BWAPIClient.isConnected())
      {
		event_dispatcher.onDisconnect();
        printf("Reconnecting...\n");
        reconnect();
		event_dispatcher.onConnect(BWAPI::Broodwar);
      }
    }
    // Enable some cheat flags
    Broodwar->enableFlag(Flag::UserInput);
    // Uncomment to enable complete map information
    //Broodwar->enableFlag(Flag::CompleteMapInformation);

    //read map information into BWTA so terrain analysis can be done in another thread
    BWTA::readMap();
    analyzed=false;
    analysis_just_finished=false;

    show_bullets=false;
    show_visibility_data=false;

    while(Broodwar->isInGame())
    {
      for(std::list<Event>::iterator e=Broodwar->getEvents().begin();e!=Broodwar->getEvents().end();e++)
      {
	    event_dispatcher.dispatchEvent(&*e);

        switch(e->type)
        {
          case EventType::SendText:
            if (e->text=="/show bullets")
            {
              show_bullets=!show_bullets;
            } else if (e->text=="/show players")
            {
              showPlayers();
            } else if (e->text=="/show forces")
            {
              showForces();
            } else if (e->text=="/show visibility")
            {
              show_visibility_data=!show_visibility_data;
            } else if (e->text=="/analyze")
            {
              if (analyzed == false)
              {
                Broodwar->printf("Analyzing map... this may take a minute");
                CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
              }
            }
			else
			{
				Broodwar->sendText("%s", e->text);
			}
            break;
        }
      }

      if (show_bullets)
        drawBullets();

      if (show_visibility_data)
        drawVisibilityData();

      if (!Broodwar->isReplay())
      {
        drawStats();

        if (analysis_just_finished)
        {
          Broodwar->printf("Finished analyzing map.");
          analysis_just_finished=false;
        }
        if (analyzed)
          drawTerrainData();
      }

      BWAPI::BWAPIClient.update();
      if (!BWAPI::BWAPIClient.isConnected())
      {
		event_dispatcher.onDisconnect();
        printf("Reconnecting...\n");
        reconnect();
		event_dispatcher.onConnect(BWAPI::Broodwar);
      }
    }
  }

  uninit();
  return 0;
}

DWORD WINAPI AnalyzeThread()
{
  BWTA::analyze();

  //self start location only available if the map has base locations
  if (BWTA::getStartLocation(BWAPI::Broodwar->self())!=NULL)
  {
    home       = BWTA::getStartLocation(BWAPI::Broodwar->self())->getRegion();
  }
  //enemy start location only available if Complete Map Information is enabled.
  if (BWTA::getStartLocation(BWAPI::Broodwar->enemy())!=NULL)
  {
    enemy_base = BWTA::getStartLocation(BWAPI::Broodwar->enemy())->getRegion();
  }
  analyzed   = true;
  analysis_just_finished = true;
  return 0;
}

void drawStats()
{
  std::set<Unit*> myUnits = Broodwar->self()->getUnits();
  Broodwar->drawTextScreen(5,0,"I have %d units:",myUnits.size());
  std::map<UnitType, int> unitTypeCounts;
  for(std::set<Unit*>::iterator i=myUnits.begin();i!=myUnits.end();i++)
  {
    if (unitTypeCounts.find((*i)->getType())==unitTypeCounts.end())
    {
      unitTypeCounts.insert(std::make_pair((*i)->getType(),0));
    }
    unitTypeCounts.find((*i)->getType())->second++;
  }
  int line=1;
  for(std::map<UnitType,int>::iterator i=unitTypeCounts.begin();i!=unitTypeCounts.end();i++)
  {
    Broodwar->drawTextScreen(5,16*line,"- %d %ss",(*i).second, (*i).first.getName().c_str());
    line++;
  }
}

void drawBullets()
{
  std::set<Bullet*> bullets = Broodwar->getBullets();
  for(std::set<Bullet*>::iterator i=bullets.begin();i!=bullets.end();i++)
  {
    Position p=(*i)->getPosition();
    double velocityX = (*i)->getVelocityX();
    double velocityY = (*i)->getVelocityY();
    if ((*i)->getPlayer()==Broodwar->self())
    {
      Broodwar->drawLineMap(p.x(),p.y(),p.x()+(int)velocityX,p.y()+(int)velocityY,Colors::Green);
      Broodwar->drawTextMap(p.x(),p.y(),"\x07%s",(*i)->getType().getName().c_str());
    }
    else
    {
      Broodwar->drawLineMap(p.x(),p.y(),p.x()+(int)velocityX,p.y()+(int)velocityY,Colors::Red);
      Broodwar->drawTextMap(p.x(),p.y(),"\x06%s",(*i)->getType().getName().c_str());
    }
  }
}

void drawVisibilityData()
{
  for(int x=0;x<Broodwar->mapWidth();x++)
  {
    for(int y=0;y<Broodwar->mapHeight();y++)
    {
      if (Broodwar->isExplored(x,y))
      {
        if (Broodwar->isVisible(x,y))
          Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Green);
        else
          Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Blue);
      }
      else
        Broodwar->drawDotMap(x*32+16,y*32+16,Colors::Red);
    }
  }
}

void drawTerrainData()
{
  //we will iterate through all the base locations, and draw their outlines.
  for(std::set<BWTA::BaseLocation*>::const_iterator i=BWTA::getBaseLocations().begin();i!=BWTA::getBaseLocations().end();i++)
  {
    TilePosition p=(*i)->getTilePosition();
    Position c=(*i)->getPosition();

    //draw outline of center location
    Broodwar->drawBox(CoordinateType::Map,p.x()*32,p.y()*32,p.x()*32+4*32,p.y()*32+3*32,Colors::Blue,false);

    //draw a circle at each mineral patch
    for(std::set<BWAPI::Unit*>::const_iterator j=(*i)->getStaticMinerals().begin();j!=(*i)->getStaticMinerals().end();j++)
    {
      Position q=(*j)->getInitialPosition();
      Broodwar->drawCircle(CoordinateType::Map,q.x(),q.y(),30,Colors::Cyan,false);
    }

    //draw the outlines of vespene geysers
    for(std::set<BWAPI::Unit*>::const_iterator j=(*i)->getGeysers().begin();j!=(*i)->getGeysers().end();j++)
    {
      TilePosition q=(*j)->getInitialTilePosition();
      Broodwar->drawBox(CoordinateType::Map,q.x()*32,q.y()*32,q.x()*32+4*32,q.y()*32+2*32,Colors::Orange,false);
    }

    //if this is an island expansion, draw a yellow circle around the base location
    if ((*i)->isIsland())
      Broodwar->drawCircle(CoordinateType::Map,c.x(),c.y(),80,Colors::Yellow,false);
  }

  //we will iterate through all the regions and draw the polygon outline of it in green.
  for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
  {
    BWTA::Polygon p=(*r)->getPolygon();
    for(int j=0;j<(int)p.size();j++)
    {
      Position point1=p[j];
      Position point2=p[(j+1) % p.size()];
      Broodwar->drawLine(CoordinateType::Map,point1.x(),point1.y(),point2.x(),point2.y(),Colors::Green);
    }
  }

  //we will visualize the chokepoints with red lines
  for(std::set<BWTA::Region*>::const_iterator r=BWTA::getRegions().begin();r!=BWTA::getRegions().end();r++)
  {
    for(std::set<BWTA::Chokepoint*>::const_iterator c=(*r)->getChokepoints().begin();c!=(*r)->getChokepoints().end();c++)
    {
      Position point1=(*c)->getSides().first;
      Position point2=(*c)->getSides().second;
      Broodwar->drawLine(CoordinateType::Map,point1.x(),point1.y(),point2.x(),point2.y(),Colors::Red);
    }
  }
}

void showPlayers()
{
  std::set<Player*> players=Broodwar->getPlayers();
  for(std::set<Player*>::iterator i=players.begin();i!=players.end();i++)
  {
    Broodwar->printf("Player [%d]: %s is in force: %s",(*i)->getID(),(*i)->getName().c_str(), (*i)->getForce()->getName().c_str());
  }
}

void showForces()
{
  std::set<Force*> forces=Broodwar->getForces();
  for(std::set<Force*>::iterator i=forces.begin();i!=forces.end();i++)
  {
    std::set<Player*> players=(*i)->getPlayers();
    Broodwar->printf("Force %s has the following players:",(*i)->getName().c_str());
    for(std::set<Player*>::iterator j=players.begin();j!=players.end();j++)
    {
      Broodwar->printf("  - Player [%d]: %s",(*j)->getID(),(*j)->getName().c_str());
    }
  }
}
