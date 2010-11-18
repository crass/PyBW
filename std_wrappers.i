%exception SetWrapper::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of set");
     return NULL;
  }
}

%exception SetWrapper_PtrNext::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of set");
     return NULL;
  }
}

%exception ListWrapper::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception ListWrapper_PtrNext::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of list");
     return NULL;
  }
}

%exception MapIterator::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of iterator");
     return NULL;
  }
}

%exception MapIterator_PtrNext::next {
  $action
  if (!result) {
     PyErr_SetString(PyExc_StopIteration,"End of iterator");
     return NULL;
  }
}


%{
#include "stdpair_wrapper.h"
#include "stdmap_wrapper.h"
#include "stdset_wrapper.h"
#include "stdlist_wrapper.h"
//#include "vector_wrapper.h"


%}
%include "stdpair_wrapper.h"
%include "stdmap_wrapper.h"
%include "stdset_wrapper.h"
%include "stdlist_wrapper.h"
//%include "vector_wrapper.h"

%newobject SetWrapper::__iter__;
%newobject SetWrapper_PtrNext::__iter__;
%newobject SetWrapper::ThisShouldFail;

%newobject ListWrapper::__iter__;
%newobject ListWrapper_PtrNext::__iter__;

%newobject MapWrapper::__iter__;
%newobject MapIterator::__iter__;
%newobject MapWrapper_PtrNext::__iter__;
%newobject MapIterator_PtrNext::__iter__;


