PyBW - Python wrappings for BWAPI

Summary
===========

PyBW lets users write AI agents in Python to play Starcraft Broodwar, by wrapping BWAPI.

Author: Erez Shinan
Contributor: Glenn Washburn


How to Compile & Run
======================

Get PyBW source code through the SVN/Git
Make sure you have "BWAPI_3.7" (latest release at the moment of writing this)
Make sure you have Python (tested only with 2.6)
Put the PyBW directory inside the BWAPI_3.7 directory
Open solution file in Visual Studio 2008 (currently not working with 2010)
Set build to "release"
Build solution (F7 from Visual Studio)
change bwapi-data\bwapi.ini to accept client connections (set ai_dll to NULL)
Run Release/pybwClient.exe (or press Ctrl+F5 from Visual Studio)
Start a game and enjoy watching as exampleai.py sends your workers to collect money for daddy
