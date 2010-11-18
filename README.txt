PyBW - Python wrappings for BWAPI

Summary
===========

PyBW lets users write AI agents in Python to play Starcraft Broodwar, by wrapping BWAPI.

Author: Erez Shinan


How to Compile & Run
======================

Get PyBW source code through the SVN
Make sure you have "BWAPI_Beta_3.2" (latest release at the moment of writing this)
Make sure you have Python (tested only with 2.6)
Put the PyBW inside the BWAPI_Beta_3.2 directory
Open solution file in Visual Studio
Set build to "release"
Build solution
change bwapi-data\bwapi.ini to accept client connections (set ai_dll to NULL)
Start a game and enjoy watching as exampleai.py sends your workers to collect money for daddy
