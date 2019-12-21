#ifndef ALL_HEADERS
#define ALL_HEADERS

#define PY_SSIZE_T_CLEAN

/*
Header files to contain references to all the 
other header files. Add all header file dependences 
here, and then reference this header file in 
the 'main.cpp' file
*/

// Include all header files
#include <bits/stdc++.h>

// Include libraries required to build the project
#include "../../packages/cpr_x64-linux/include/cpr.h"                       // For sending URL requests

#include "/usr/include/python2.7/Python.h"                                  // Library for C API for Python

// Include all the algorithm related files for the project that relate to data structures
#include "../algorithms/algorithmFileHandle.h"

// Include all the header files that have been used in the folder '/api'
#include "../api/apiFileHandle.h"

// Include the header file which is the container for all the header files present in folder '/container'
#include "../container/containerFileHandle.h"              

// Include all the header files for the project that relate to data structures
#include "../dataStructures/dataStructuresFileHandle.h"

// Include the dependency for the JSON header file 
#include "../../packages/nlohmann-json_x64-linux/include/nlohmann/json.hpp"        

#endif