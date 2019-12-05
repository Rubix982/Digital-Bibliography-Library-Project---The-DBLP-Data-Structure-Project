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
// #include "/usr/include/python2.7/Python.h"                                  // Library for C API for Python
#include "../container/csvReader.h"            
#include "../../packages/nlohmann-json_x64-linux/include/nlohmann/json.hpp"        
#include "../container/containerHeaderFiles.h"                       

#endif