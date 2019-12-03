#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "/usr/include/python2.7/Python.h"
using namespace std;

int main(int argc, char** argv) {

    // Initialize the Python interpreter.

    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    // Create some Python objects that will later be assigned values.

    PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;

    // Convert the file name to a Python string.

    pName = PyBytes_FromString("HelloWorld");

    // Import the file as a Python module.

    pModule = PyImport_Import(pName);

    // Create a dictionary for the contents of the module.

    pDict = PyModule_GetDict(pModule);

    // Get the add method from the dictionary.

    pFunc = PyDict_GetItemString(pDict, "printHello");

    // Create a Python tuple to hold the arguments to the method.

    pArgs = PyTuple_New(2);

    // Convert 2 to a Python integer.

    pValue = PyLong_FromLong(2);

    // Set the Python int as the first and second arguments to the method.

    PyTuple_SetItem(pArgs, 0, pValue);

    PyTuple_SetItem(pArgs, 1, pValue);

    // Call the function with the arguments.

    PyObject* pResult = PyObject_CallObject(pFunc, pArgs);

    return 0;
}