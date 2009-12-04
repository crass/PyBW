%exception SetWrapper::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}


%{
//#include "map_wrapper.h"
#include "stdset_wrapper.h"
//#include "vector_wrapper.h"
//#include "list_wrapper.h"


%}
//%include "map_wrapper.h"
%include "stdset_wrapper.h"
//%include "vector_wrapper.h"
//%include "list_wrapper.h"

%newobject SetWrapper::__iter__;
%newobject SetWrapper_PtrNext::__iter__;
%newobject SetWrapper::ThisShouldFail;

/*
%template (DamageTypeSet) SetWrapper<BWAPI::DamageType>;
%template (DamageTypeSetIterator) SetIterator<BWAPI::DamageType>;
%template (ErrorSet) SetWrapper<BWAPI::Error>;
%template (ErrorSetIterator) SetIterator<BWAPI::Error>;
%template (ExplosionTypeSet) SetWrapper<BWAPI::ExplosionType>;
%template (ExplosionTypeSetIterator) SetIterator<BWAPI::ExplosionType>;
%template (ForceSet) SetWrapper<BWAPI::Force*>;
%template (ForceSetIterator) SetIterator<BWAPI::Force*>;
%template (OrderSet) SetWrapper<BWAPI::Order>;
%template (OrderSetIterator) SetIterator<BWAPI::Order>;
%template (PlayerSet) SetWrapper<BWAPI::Player*>;
%template (PlayerSetIterator) SetIterator<BWAPI::Player*>;
%template (PlayerTypeSet) SetWrapper<BWAPI::PlayerType>;
%template (PlayerTypeSetIterator) SetIterator<BWAPI::PlayerType>;
%template (RaceSet) SetWrapper<BWAPI::Race>;
%template (RaceSetIterator) SetIterator<BWAPI::Race>;
%template (TechTypeConstantSet) SetWrapper<const BWAPI::TechType*>;
%template (TechTypeConstantSetIterator) SetIterator<const BWAPI::TechType*>;
%template (TechTypeSet) SetWrapper<BWAPI::TechType>;
%template (TechTypeSetIterator) SetIterator<BWAPI::TechType>;
%template (UnitList) ListWrapper<BWAPI::Unit*>;
%template (UnitListIterator) ListIterator<BWAPI::Unit*>;
%template (UnitSet) SetWrapper<BWAPI::Unit*>;
%template (UnitSetIterator) SetIterator<BWAPI::Unit*>;
%template (UnitSizeTypeSet) SetWrapper<BWAPI::UnitSizeType>;
%template (UnitSizeTypeSetIterator) SetIterator<BWAPI::UnitSizeType>;
%template (UnitTypeConstantSet) SetWrapper<const BWAPI::UnitType*>;
%template (UnitTypeConstantSetIterator) SetIterator<const BWAPI::UnitType*>;
%template (UnitTypeSet) SetWrapper<BWAPI::UnitType>;
%template (UnitTypeSetIterator) SetIterator<BWAPI::UnitType>;
//%template (UnitTypeWhatBuildsPair) std::pair<const BWAPI::UnitType*,int>; // TODO
%template (UnitTypeMap) MapWrapper<const UnitType*, int>;
%template (UnitTypeMapIterator) MapIterator<const UnitType*, int>;
%template (UnitTypeList) ListWrapper<BWAPI::UnitType>;
%template (UnitTypeListIterator) ListIterator<BWAPI::UnitType>;
%template (UpgradeTypeSet) SetWrapper<BWAPI::UpgradeType>;
%template (UpgradeTypeSetIterator) SetIterator<BWAPI::UpgradeType>;
%template (WeaponTypeSet) SetWrapper<BWAPI::WeaponType>;
%template (WeaponTypeSetIterator) SetIterator<BWAPI::WeaponType>;
%template (TilePositionSet) SetWrapper<BWAPI::TilePosition>;
%template (TilePositionSetIterator) SetIterator<BWAPI::TilePosition>;

%template (PositionList) std::vector<BWAPI::Position>;
*/
