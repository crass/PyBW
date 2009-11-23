PyBW - Python wrappings for BWAPI

Summary
===========

PyBW lets users write AI agents in Python to play Starcraft Broodwar, by wrapping BWAPI.

Author: Erez Shinan


How to Compile & Run
======================
These instructions assume you 

1. Make sure you have "BWAPI_Beta_2.3" (latest release at the moment of writing this)
2. Make sure you have Python (tested only with 2.6)
3. Put PyBW in the same directory as BWAPI_Beta_2.3
4. Open solution file in Visual Studio
5. Set build to "release"
6. Build solution
7. Copy Release/pybw.dll to bwapi-data\AI, and change bwapi-data\bwapi.ini to use this dll
8. Copy pybw.py, basicai.py AND Release/pybw_swig.py to somewhere on the PYTHONPATH or your starcraft directory
9. Start a game and enjoy watching units you select go mental (if you didn't change basicai.py)
10. Now you can edit basicai.py to do anything you want!

