# PathFinder

PathFinder was downloaded from 
```
https://svnsrv.desy.de/websvn/wsvn/General.pathfinder/trunk
```

The only prerequisite is to have CERN ROOT installed (which should be installed with Fairsoft installation if you are using EsbRoot).
Create a folder and execute 
```
$cmake PATH_TO_PATHFINDERSOURCES
$make
```
After the build is successdull two enviormental variables have to be defined, so that it can be used by EsbRoot.
This is not required if Pathfinder will be used seperatelly.

The two environmental variables are to the include directory and the sources.
The include directory which is the located 'include' folder of the downloaded Pathdinder repository 
directory, and the second environemntal variable is to the 'lib' folder in the Pathfinder build directory (the used cmake folder).
```
export PATHFINDER_INC=/** PATHFINDER_SOURCES **/include
export PATHFINDER_LIB=/** PATHFINDER_BUILD_DIR **/lib
```

