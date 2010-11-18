#include <windows.h>

#include "event_dispatcher.h"


PyObject* _getSwigUnit(BWAPI::Unit* unit);
PyObject* _getSwigPlayer(BWAPI::Player* player);
PyObject* _getSwigPosition(BWAPI::Position* position);


EventDispatcher::EventDispatcher()
	:event_handler(NULL)
{
	LoadEventHandler();
}

EventDispatcher::~EventDispatcher()
{
	if (event_handler != NULL)
	{
		Py_DECREF( event_handler );
		event_handler = NULL;
	}
}


static void python_func_cleanup(PyObject* res)
{
	if (res != NULL)
	{
	  Py_DECREF( res );
	}
	PyErr_Clear();
}

void EventDispatcher::LoadEventHandler(bool call_reload)
{
	PyObject* pybw_module = PyImport_ImportModule("pybw");
	PyErr_Clear();
	if (pybw_module == NULL)
	{
		printf("Error importing pybw module\n");
		return;
	}

	if (event_handler != NULL)
	{
		Py_DECREF(event_handler);
		event_handler = NULL;
	}

	if (call_reload)
	{
		PyObject* reload_event_handler = PyObject_GetAttrString(pybw_module, "reload_event_handler");
		PyErr_Clear();
		if (reload_event_handler == NULL)
		{
			MessageBoxA(0, "Error getting reload_event_handler from pybw module", 0,0);
			return;
		}

		python_func_cleanup( PyObject_CallFunction(reload_event_handler, NULL) );
		Py_DECREF(reload_event_handler);
	}

	event_handler = PyObject_GetAttrString(pybw_module, "event_handler");
	PyErr_Clear();
	Py_DECREF( pybw_module );

	if (event_handler == NULL)
	{
		MessageBoxA(0, "Error getting event_handler from pybw module", 0,0);
		return;
	}

}
void EventDispatcher::reload()
{
	LoadEventHandler(true);
}

void EventDispatcher::onMatchStart()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onMatchStart", NULL) );
  }
}

void EventDispatcher::onMatchEnd(bool isWinner)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onMatchEnd", "i", isWinner) );
	}
}

void EventDispatcher::onMatchFrame()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onMatchFrame", NULL) );
  }
}

void EventDispatcher::onMenuFrame()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onMenuFrame", NULL) );
  }
}

void EventDispatcher::onSendText(std::string text)
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onSendText", "s", text.c_str()) );
  }
}

void EventDispatcher::onReceiveText(BWAPI::Player* player, std::string text)
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onReceiveText", "Os", _getSwigPlayer(player), text.c_str()) );
  }
}

void EventDispatcher::onSaveGame(std::string gameName)
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onSaveGame", "s", gameName.c_str()) );
  }
}

void EventDispatcher::onPlayerLeft(BWAPI::Player* player)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onPlayerLeft", "O", _getSwigPlayer(player)) );
	}
}

void EventDispatcher::onNukeDetect(BWAPI::Position target)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onNukeDetect", NULL) );
	}
}

void EventDispatcher::onUnitCreate(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitCreate", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitDestroy(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitDestroy", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitEvade(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitEvade", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitDiscover(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitDiscover", "O", _getSwigUnit(unit)) );
	}
}


void EventDispatcher::onUnitMorph(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitMorph", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitShow(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitShow", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitHide(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitHide", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitRenegade(BWAPI::Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitRenegade", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onConnect(BWAPI::Game* game)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onConnect", NULL) );	// TODO !
	}
}

void EventDispatcher::onDisconnect()
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onDisconnect", NULL) );
	}
}
