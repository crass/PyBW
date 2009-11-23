#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <Python.h>

#include <BWAPI.h>

void python_wrap_init();

#include "ExampleAIModule.h"
namespace BWAPI { Game* Broodwar = NULL; }
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        BWAPI::BWAPI_init();
		Py_Initialize();
		python_wrap_init();
		break;
	case DLL_PROCESS_DETACH:
		Py_Finalize();
		break;
	}


	return TRUE;
}

 extern "C" __declspec(dllexport) BWAPI::AIModule* newAIModule(BWAPI::Game* game)
{
  BWAPI::Broodwar=game;
  return new ExampleAIModule();
}
