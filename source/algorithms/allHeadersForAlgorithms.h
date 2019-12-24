#ifndef ALL_HEADERS_FOR_ALGORITHMS
#define ALL_HEADERS_FOR_ALGORITHMS

#define PY_SSIZE_T_CLEAN

/*
Header files to contain references to all the 
other header files. Add all header file dependences 
here, and then reference this header file in 
the 'main.cpp' file
*/

// ? Include all header files
#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/types.h>

// ? Include libraries required to build the project
#include "../../packages/cpr_x64-linux/include/cpr.h"                           // For sending URL requests

// ? Include the Python library / C API 
#include "/usr/include/python2.7/Python.h"                                   

// ? Include library that gives the nlohmann::json class
#include "../../packages/nlohmann-json_x64-linux/include/nlohmann/json.hpp"        

// ? Add the header for the all the algorithms that are to be used
#include "../container/containerFileHandle.h"

// ? Add the header for the functions from /api/
#include "../api/apiFileHandle.h"

#endif