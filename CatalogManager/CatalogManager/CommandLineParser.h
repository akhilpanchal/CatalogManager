#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H
/////////////////////////////////////////////////////////////////////////////
// CommandLineParser.h - Parses the Command Line Arguments				   //
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
* This module provides CommandLineParser class that parses the commands
* entered by the user and splits them into the required attributes required
* for further processing by the other packages.
*
* Public Interface:
* =================
* Constructor:
* CommandLineParser(const char *args, int count)
* Accepts command line arguments and the count of the argument parameters.
*
* void parseUserRequest(string request)
* Parses the user request for retriving catalogue information after the
* creation of the catalogue.
*
* string getPath()
* Gets the path for which the File Catalogue is to be generated.
*
* vector<string> getCataloguePatterns()
* Returns a vector of strings consisting of the file patterns that
* the user widhes to store in the catalogue.
*
* vector<string> getSearchPatterns()
* Return a vector of strings consisting of patterns that the user wishes
* to retrive from the generated catalogue.
*
* bool getRecurse()
* returns true if the user wishes to generate a Catalogue for files rooted
* at the path specified. Returns false if the user wishe to generated a
* Catalogue for only the specified path.
*
* bool getDuplicate()
* returns true if the user wishes to see the duplicate entries in the
* catalogue after its generation. This information is given to the Display
* package for appropriate display of information.
*
* bool getSearch()
* returns true if user wishes to search for a keyword in the catalogue
* after its generation.
*
* string getSearchText()
* if the getSearch() returns true, this methid returns the keyword that is to
* be searched in the catalogue.
*
* bool getValid()
* returns true if the command entered by the user is valid.
* returns false if the user has entered an invalid command.
*
* Required Files:
* ===============
* FileManager.h, FileManager.cpp
*
* Build Command:
* ==============
* cl/EHsc/TEST_COMMANDLINEPARSER CommandLineParser.cpp FileSystem.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 29 January 2015
* - first release
*/
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include "FileSystem.h"

using namespace std;

class CommandLineParser
{
public:

	CommandLineParser(char* const args[], int count);
	void parseUserRequest(string request);
	string getPath();
	vector<string> getCataloguePatterns();
	vector<string> getSearchPatterns();
	bool getRecurse();
	bool getDuplicate();
	bool getSearch();
	string getSearchText();
	bool getValid();
	

private:
	string path;
	vector <string> search_patterns;
	vector<string> catalogue_patterns;
	bool recurse;
	bool duplicate;
	bool search;
	string search_text;
	bool valid;
	void handleArguments(char* const args[], int count);
	vector<string> handleArguments(string request);
};

#endif