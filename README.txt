PyBW - Python wrappings for BWAPI

Summary
===========

PyBW lets users write AI agents in Python to play Starcraft Broodwar, by wrapping BWAPI.

Author: Erez Shinan


How to Compile & Run
======================

Get PyBW source code through the SVN
Make sure you have "BWAPI_Beta_2.4" (latest release at the moment of writing this)
Make sure you have Python (tested only with 2.6)
Put PyBW in the same parent directory as BWAPI_Beta_2.4 (so they are right next to each other), unless you want to edit the paths on the PyBW project settings.
Open solution file in Visual Studio
Set build to "release"
Build solution
Copy Release/pybw.dll to bwapi-data\AI, and change bwapi-data\bwapi.ini to use this dll
Add the scripts directory to your PYTHONPATH, or copy the files inside it to somewhere else on your PYTHONPATH
Start a game and enjoy typing away the at the console, OR edit basicai.py to do anything you want!
