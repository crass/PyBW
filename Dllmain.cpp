#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <Python.h>

#include <BWAPI.h>

void python_wrap_init();

void add_module_path_to_pythonpath(HMODULE module)
{
	char filename[MAX_PATH];
	char python_command[MAX_PATH + 100];
	GetModuleFileNameA( module, filename, MAX_PATH);
	_snprintf_s(python_command, MAX_PATH+100, MAX_PATH+100, "module_filename = r'''%s'''", filename);
	PyRun_SimpleString(python_command);
	PyRun_SimpleString("import sys; sys.path.insert(0, module_filename.rsplit('\\\\', 1)[0])");
}

#include "AIModuleImpl.h"
namespace BWAPI { Game* Broodwar = NULL; }
BOOL APIENTRY DllMain( HMODULE module, 
                       DWORD  reason_for_call, 
                       LPVOID reserved
					 )
{

	UNREFERENCED_PARAMETER( reserved );
	UNREFERENCED_PARAMETER( module );
    
	switch (reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        BWAPI::BWAPI_init();
		Py_Initialize();
		python_wrap_init();
		add_module_path_to_pythonpath( module );
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
  return new AIModuleImpl();
}
