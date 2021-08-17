#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

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
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
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
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
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

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
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

/*void MultiTable() {
	int num;

	cout << "Please enter a number: ";
	cin >> num;
	callIntFunc("MultiplicationTable", num);
}*/

/*void DoubleValue() {
	int num;

	cout << "Please enter a number: ";
	cin >> num;
	cout << callIntFunc("SquareValue", num) << endl;

}*/
//for our first option in the switch statement


void DisplayFrequencies() {
	CallProcedure("displayFreq");
}

//created display menu 
void DisplayMenu() {

	cout << "1: Calculate how many times each item is listed" << endl;
	cout << "2: Calculate the frequency of the item chosen" << endl;
	cout << "3: Create a histogram based on the number of times each item is listed" << endl;
	cout << "4: Exit" << endl;
	cout << "Please choose from the options" << endl;
	
}


int main(void)
{
	// initilazations
	int choice = -1;
	int itemCounts = 0;
	int veggieCount = 0;
	string itemSearch;
	ifstream myFile;
	string veggieName;
	string hist;
	

	while (choice != 4) {
		const std::string red("\033[0;31m");
		const std::string green("\033[0;32m");
		const std::string reset("\033[0m");

		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1: //Displays the list from a function in python that displays the entire list with the amount on .txt list
			DisplayFrequencies();
			break;

		case 2: // this option callIntFunc to show the list of items with the number of occurences the item is on list
			cout << "What item are you looking for?" << endl;
			cin >> itemSearch;
			itemCounts = callIntFunc("DisplayInstance", itemSearch);
			cout << itemSearch << ":" << itemCounts << endl;
			break;

		case 3:
			
			myFile.open("frequency.dat");//Opening frequency.dat from python
			
			while (myFile >> veggieName) // this loop is basically calling the histogram and formatting it
			{
				
				cout << red << setw(20) << right << veggieName << " ";
				myFile >> hist;
				cout << green << setw(50) << left << hist;
				cout << endl;
				
			}
			myFile.close();
			break;
		case 4: //quits program
			cout << "Nooooooo come bacckkkkkkkkk" << endl;
			break;

		default:// if they dont choose an option between 1-4 this messages shows
			cout << "Please make a selection between 1-4" << endl;
			break;
		}
	}
}


