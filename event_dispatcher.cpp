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
	}
}

void EventDispatcher::LoadEventHandler()
{
  PyObject* pybw_module = PyImport_ImportModule("pybw");
  PyErr_Clear();
  if (pybw_module == NULL)
  {
	  MessageBoxA(0, "Error importing pybw module (is pybw.py in path?)", 0,0);
	  return;
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

void python_func_cleanup(PyObject* res)
{
	if (res != NULL)
	{
	  Py_DECREF( res );
	}
	PyErr_Clear();
}


void EventDispatcher::onStart()
{
  if (event_handler != NULL)
  {
	  python_func_cleanup( PyObject_CallMethod(event_handler, "onStart", NULL) );
  }
}

void EventDispatcher::onEnd()
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onEnd", NULL) );
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


void EventDispatcher::onPlayerLeft(Player* player)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onPlayerLeft", "O", _getSwigPlayer(player)) );
	}
}

void EventDispatcher::onNukeDetect(Position target)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onNukeDetect", NULL) );
	}
}

void EventDispatcher::onUnitCreate(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitCreate", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitDestroy(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitDestroy", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitMorph(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitMorph", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitShow(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitShow", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitHide(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitHide", "O", _getSwigUnit(unit)) );
	}
}

void EventDispatcher::onUnitRenegade(Unit* unit)
{
	if (event_handler != NULL)
	{
		python_func_cleanup( PyObject_CallMethod(event_handler, "onUnitRenegade", "O", _getSwigUnit(unit)) );
	}
}

