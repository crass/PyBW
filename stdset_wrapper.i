%exception UnitSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception PlayerSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception ForceSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception TilePositionSet::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%{
#include "stdset_wrapper.h"

PyObject* _getSwigUnit(BWAPI::Unit* unit)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(unit), SWIGTYPE_p_BWAPI__Unit, 0 );
}

PyObject* _getSwigPlayer(BWAPI::Player* player)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(player), SWIGTYPE_p_BWAPI__Player, 0 );
}

PyObject* _getSwigPosition(BWAPI::Position* position)
{
  return SWIG_NewPointerObj(SWIG_as_voidptr(position), SWIGTYPE_p_BWAPI__Position, 0 );
}


%}
%include "stdset_wrapper.h"


