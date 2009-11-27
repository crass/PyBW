
#include "helper.h"
#include "AIModuleImpl.h"
using namespace BWAPI;

void AIModuleImpl::onEnd(bool isWinner)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onEnd();
		delete event_dispatcher;
		event_dispatcher = NULL;
	}

	if (analyzingThreadHandle)
	{
		TerminateThread(analyzingThreadHandle, (DWORD)-1);
		CloseHandle(analyzingThreadHandle);
		analyzingThreadHandle = NULL;
	}
}

void AIModuleImpl::onStart()
{
  Broodwar->sendText("starting PyBW...");
  Broodwar->printf("The map is %s, a %d player map",Broodwar->mapName().c_str(),Broodwar->getStartLocations().size());
  // Enable some cheat flags
  Broodwar->enableFlag(Flag::UserInput);
  // Uncomment to enable complete map information
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  //read map information into BWTA so terrain analysis can be done in another thread
  BWTA::readMap();
  analyzed=false;
  analysis_just_finished=false;

  Broodwar->printf("Analyzing map... this may take a minute");
  analyzingThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);

  event_dispatcher = new EventDispatcher();
  if (event_dispatcher != NULL)
  {
	event_dispatcher->onStart();
  }
  else
  {
	  Broodwar->printf("Error! Could not instantiate EventDispatcher");
  }

  if (Broodwar->isReplay())
  {
    /*for(std::set<Unit*>::iterator i=Broodwar->getAllUnits().begin();i!=Broodwar->getAllUnits().end();i++)
    {
      if ((*i)->getType().isBuilding())
      {
        this->buildings.insert(std::make_pair(*i,(*i)->getType()));
      }
    }
    Broodwar->printf("The following players are in this replay:");
    for(std::set<Player*>::iterator p=Broodwar->getPlayers().begin();p!=Broodwar->getPlayers().end();p++)
    {
      if (!(*p)->getUnits().empty() && !(*p)->isNeutral())
      {
        Broodwar->printf("%s, playing as a %s",(*p)->getName().c_str(),(*p)->getRace().getName().c_str());
      }
    }*/
  }
  else
  {
    Broodwar->printf("The match up is %s v %s",
      Broodwar->self()->getRace().getName().c_str(),
      Broodwar->enemy()->getRace().getName().c_str());
  }
}


void AIModuleImpl::onFrame()
{
  if (event_dispatcher)
  {
	  event_dispatcher->onFrame();
  }

  if (!Broodwar->isReplay())
  {
	  drawStats();

	  if (analyzed)
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
		  {
			Broodwar->drawCircle(CoordinateType::Map,c.x(),c.y(),80,Colors::Yellow,false);
		  }
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
  }

  if (analysis_just_finished)
  {
    Broodwar->printf("Finished analyzing map.");
    analysis_just_finished=false;
  }
}

void AIModuleImpl::onUnitCreate(BWAPI::Unit* unit)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitCreate(unit);
	}

  /*if (!Broodwar->isReplay())
    Broodwar->printf("A %s [%x] has been created at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
  else
  {
    / *if we are in a replay, then we will print out the build order
    (just of the buildings, not the units).* /
    if (unit->getType().isBuilding() && unit->getPlayer()->isNeutral()==false)
    {
      int seconds=Broodwar->getFrameCount()/24;
      int minutes=seconds/60;
      seconds%=60;
      Broodwar->printf("%.2d:%.2d: %s creates a %s",minutes,seconds,unit->getPlayer()->getName().c_str(),unit->getType().getName().c_str());
    }
  }*/
}
void AIModuleImpl::onUnitDestroy(BWAPI::Unit* unit)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitDestroy(unit);
	}

  //if (!Broodwar->isReplay())
   // Broodwar->printf("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}
void AIModuleImpl::onUnitMorph(BWAPI::Unit* unit)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitMorph(unit);
	}

  /*if (!Broodwar->isReplay())
    Broodwar->printf("A %s [%x] has been morphed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
  else
  {
    / *if we are in a replay, then we will print out the build order
    (just of the buildings, not the units).* /
    if (unit->getType().isBuilding() && unit->getPlayer()->isNeutral()==false)
    {
      int seconds=Broodwar->getFrameCount()/24;
      int minutes=seconds/60;
      seconds%=60;
      Broodwar->printf("%.2d:%.2d: %s morphs a %s",minutes,seconds,unit->getPlayer()->getName().c_str(),unit->getType().getName().c_str());
    }
  }*/
}
void AIModuleImpl::onUnitShow(BWAPI::Unit* unit)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitShow(unit);
	}

  //if (!Broodwar->isReplay())
  //  Broodwar->printf("A %s [%x] has been spotted at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}
void AIModuleImpl::onUnitHide(BWAPI::Unit* unit)
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitHide(unit);
	}

  //if (!Broodwar->isReplay())
  //  Broodwar->printf("A %s [%x] was last seen at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void AIModuleImpl::onPlayerLeft( Player* player )
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onPlayerLeft(player);
	}
}

void AIModuleImpl::onNukeDetect( Position target )
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onNukeDetect(target);
	}
}

void AIModuleImpl::onUnitRenegade( Unit* unit )
{
	if (event_dispatcher != NULL)
	{
		event_dispatcher->onUnitRenegade(unit);
	}
}

bool AIModuleImpl::onSendText(std::string text)
{
	if (text=="/reload")
	{
		if (event_dispatcher != NULL)
		{
			Broodwar->printf("Reloading event dispatcher...");
			event_dispatcher->reload();
		}
	return false;
	}
  else if (text=="/show players")
  {
    showPlayers();
    return false;
  } else if (text=="/show forces")
  {
    showForces();
    return false;
  } else if (text=="/analyze")
  {
    /*if (analyzed == false)
    {
      Broodwar->printf("Analyzing map... this may take a minute");
      CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
    }
    return false;*/
  } else
  {
	  if (event_dispatcher != NULL)
	  {
		event_dispatcher->onSendText(text);
	  }
  }
  return true;
}

DWORD WINAPI AnalyzeThread()
{
  BWTA::analyze();
  analyzed   = true;
  analysis_just_finished = true;


  BWTA::BaseLocation *startLocation = BWTA::getStartLocation(BWAPI::Broodwar->self());
  home = startLocation? startLocation->getRegion() : NULL; // if this is a replay, you may not have a "start location"

  BWTA::BaseLocation *enemy_location = BWTA::getStartLocation(BWAPI::Broodwar->enemy());
  enemy_base = enemy_location? enemy_location->getRegion() : NULL;
/*
  //enemy start location only available if Complete Map Information is enabled.
  if (BWTA::getStartLocation(BWAPI::Broodwar->enemy())!=NULL)
  {
    enemy_base = BWTA::getStartLocation(BWAPI::Broodwar->enemy())->getRegion();
  }*/
  return 0;
}

void AIModuleImpl::drawStats()
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

void AIModuleImpl::showPlayers()
{
  std::set<Player*> players=Broodwar->getPlayers();
  for(std::set<Player*>::iterator i=players.begin();i!=players.end();i++)
  {
    Broodwar->printf("Player [%d]: %s is in force: %s",(*i)->getID(),(*i)->getName().c_str(), (*i)->getForce()->getName().c_str());
  }
}
void AIModuleImpl::showForces()
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
