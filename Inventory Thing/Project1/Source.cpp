#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName, string param)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("pyScript"), *pValue = nullptr;
	PyErr_Print();
	pValue = Py_BuildValue("(z)", paramval);
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, pValue);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param, string param2)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	char* paramval2 = new char[param2.length() + 1];
	std::strcpy(paramval2, param2.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pyScript");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z,z)", paramval,paramval2);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pyScript");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main(int argc, char* argv[])
{
	int iCinInput = 0;                                           //variable to accept menu input
	string sCinInput = "";										 //accept string input
	string line = "";											 //line iterator
	ifstream frequency_file;									 //file handle 
	string sFileName = "CS210_Project_Three_Input_File.txt";	 //default file name to load

	//if a filename was supplied set the file to be read to it
	if (argc == 2) {
		sFileName = argv[1];
	}

	//application loop
	while (iCinInput != 4) {
		//display menu
		cout << "   1. Purchased Items" << endl;
		cout << "   2. Item Purchase Count" << endl;
		cout << "   3. Purchases Histogram" << endl;
		cout << "   4. Exit" << endl << endl;
		cout << "   Slection: ";

		cin >> iCinInput; //get selection input

		//process selection
		switch (iCinInput)
		{
		case 1:
			//clear screen, call python method with filename to open and process
			system("cls");
			CallProcedure("PrintPurchasedItems", sFileName);
			cout << endl;
			break;
		case 2:
			//clear screen, prompt for item name, call python function with name and return result.
			system("cls");
			cout << "Enter Item name: ";
			cin >> sCinInput;
			//check for valid input
			if (sCinInput.length() > 0) {
				system("cls");
				cout << sCinInput << ": " << callIntFunc("ItemLookup", sCinInput, sFileName) << endl;
			}
			else {
				system("cls");
				cout << "Invalid Item" << endl << endl;
			}
			break;
		case 3:
			//clear screen, read frequency.dat and output histogram
			system("cls");
			CallProcedure("loadFile", sFileName); //ensure file is generated
			frequency_file.open("frequency.dat");
			if (frequency_file.is_open())
			{
				while (getline(frequency_file, line))
				{
					int delimInd = line.find_last_of(" "); // locate index of last ' ' from frequecy file
					string stars = string(stoi(line.substr(delimInd)), '*'); // extract number and convert to * 
					cout << line.substr(0,delimInd) << " " << stars << '\n'; //output beginning of string and stars
				}
				frequency_file.close();
			} else cout << "Unable to open file";
			
			cout << endl;
			break;
		case 4:
			break;
		default:
			system("cls");  // not platform independant
			cout << "Invalid Selection" << endl << endl;
		}
	}

}