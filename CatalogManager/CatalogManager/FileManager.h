#ifndef FILEMANAGER_H
#define FILEMANAGER_H
/////////////////////////////////////////////////////////////////////////////
// FileManager.h -  Navigates local FileSystem and supports creation of	   //
//					File Catalogue										   //
// ver 1.0                                                                 //
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
* This module provides FileManager class that creates a Data Store.
* It accepts directory path, file patterns and search mode (/s: Recursive search)
* and a DataStore instance where the Catalogue is to be created.
*
* Public Interface:
* =================
* Constructor:
* FileManager(const string& directorypath, DataStore& datastoreinstance);
* Create Data Store:
* void createDataStore(std::vector<string> patterns, bool recursive_searchmode);
* 
* Required Files:
* ===============
* FileSystem.h, FileSystem.cpp, DataStore.h, DataStore.cpp,
* CommandLineParser.h, CommandLineParser.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_FILEMANAGER FileManager.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 29 January 2015
* - first release
*/

#include "FileSystem.h"
#include "../DataStore/DataStore.h"
#include "CommandLineParser.h"
#include <iostream>

using namespace std;


class FileManager{
public:
	using patterns = vector < string > ;

	FileManager(const string& path, DataStore& ds);
	void createDataStore(patterns patt, bool recurse);
	//void handleUserRequest(vector<string> getPatterns, bool getSearch, string getSearchText, bool getDuplicate);
	list<string> getSearchInfo(string key, vector<string> patterns);
	bool searchkey(string path, string key);
	void clearCatalogue();

	
private:
	string path_;
	DataStore& store_;
	patterns patterns_;

	void addfilesrecurse(string path);
};
#endif
