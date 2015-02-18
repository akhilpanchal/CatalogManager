#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////////////
// Display.h -	Displays the contents of the File Catalogue as requested   //
//				by the user												   //
// version 1.0                                                             //
// ----------------------------------------------------------------------- //
// Copyright © Akhil Panchal, 2015                                         //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013 Ultimate                    //
// Platform:    Dell Inspiron 17R 5721, Core i5, Windows 8.1			   //
// Application: CSE 687 Project #1, Spring 2015                            //
// Author:      Akhil Panchal, Syracuse University			               //
//              (408) 921-0731, ahpancha@syr.edu	                       //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides a Display class that displays the File Catalogue.
* This package accepts a DataStore object and displays the information as
* requested by the user.
*
* Public Interface:
* =================
* void genericDisplay(bool valid, bool dup, bool search, string key, list<string> foundLocations)
* Accepts command line attributes as arguments and displays the information
* on the console accordingly.
*
* Required Files:
* ===============
* DataStore.h, DataStore.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_DISPLAY Display.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 29 January 2015
* - first release
*/
#include "../DataStore/DataStore.h"
#include <iostream>
#include <string>

using namespace std;
class Display
{
public:
	Display(DataStore& ds);
	void summary();
	void duplicates();
	void searchInfo(string key, list<string> foundLocations);
	void genericDisplay(bool valid, bool dup, bool search, string key, list<string> foundLocations);
	void displayCatalogue();
private:
	DataStore& catalogue;
};

#endif