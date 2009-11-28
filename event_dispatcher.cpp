#include <windows.h>

#include "event_dispatcher.h"

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
		MessageBoxA(0, "Error importing pybw module (is pybw.py in path?)", 0,0);
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

void EventDispatcher::onStart()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onStart", NULL) );
  }
}

void EventDispatcher::onEnd(bool isWinner)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onEnd", "i", isWinner) );
	}
}

void EventDispatcher::onFrame()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onFrame", NULL) );
  }
}

void EventDispatcher::onSendText(std::string text)
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onSendText", "s", text.c_str()) );
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

