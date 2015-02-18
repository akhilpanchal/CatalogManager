#ifndef DATASTORE_H
#define DATASTORE_H
/////////////////////////////////////////////////////////////////////////////
// DataStore.h - Stores the File Catalogue								   //
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
* This module provides DataStore class that holds the File Catalogue.
* It adds (new File) and/or updates (File already in catalogue) entries to
* the Catalogue by accepting File Name and path.
*
* Public Interface:
* =================
* void addPathtoSet(string path);
* Adds a unique path to the catalogue
*
* void addMapEntry(string& filename, string& path);
* Adds the file to the catalogue if not already present and adds 
* the reference to the path from the path set.
*
* Required Files:
* ===============
* No dependencies
*
* Build Command:
* ==============
* cl /EHa /DTEST_DATASTORE DataStore.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 29 January 2015
* - first release
*/

#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

class DataStore{

public:	
	using File = string;
	using Path = string;
	using pathref = set<Path>::iterator;
	using listofrefs = list<pathref>;

	void addPathtoSet(string path);
	void addMapEntry(string& filename, string& path);
	int getFileCount();
	int getDirectoryCount();
	map<string, list<string>> getDuplicates();
	map<string, list<string>> getCatalogue();
	set<string> getPaths();
	void clearStore();
	//list<string> getSearchInfo(string key);
	//bool searchkey(string path, string key);

private:
	map<File,listofrefs> files;
	set<Path> pathset;
};

#endif