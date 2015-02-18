
/////////////////////////////////////////////////////////////////////////////
// DataStore.cpp - Stores the File Catalogue							   //
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

#include "DataStore.h"
#include "../CatalogManager/FileSystem.h"
#include <iostream>
#include <map>
#include <list>
#include <string>

void DataStore::addPathtoSet(string path)
{
	pathset.insert(path);
}


void DataStore::addMapEntry(string& filename, string& paths)
{
	//check if key <filename> exists in the Map
	if (files.find(filename)==files.end())
	{//not found
		for (pathref iter = pathset.begin(); iter != pathset.end(); iter++)
		{
			if (paths == (*iter))
			{
				listofrefs temp;
				temp.insert(temp.begin(), iter);
				files.insert(pair<File, listofrefs>(filename, temp));
				break;
			}
		}
	}
	else
	{//found
		map<File, listofrefs>::iterator map_iter = files.find(filename);
		for (pathref iter = pathset.begin(); iter != pathset.end(); iter++)
		{//add reference to the list of pathrefs in map
			if (paths == (*iter))
			{
				(map_iter->second).push_back(iter);
			}
		}
	}
}

int DataStore::getDirectoryCount()
{
	return pathset.size();
}

int DataStore::getFileCount()
{
	return files.size();
}

map<string, list<string>> DataStore::getDuplicates()
{
	map<File,listofrefs>::iterator map_iter = files.begin();
	//create a new map of key: string and value: list of strings
	map<File, list<string>> duplicates;

	for (map_iter ; map_iter != files.end();map_iter++)
	{
		//Check if duplicate
		if ((map_iter->second).size() > 1)
		{
			list<string> temp_list;
			for (listofrefs::iterator ref_iter = (map_iter->second).begin(); ref_iter != (map_iter->second).end(); ref_iter++)
			{//dereference the paths
				temp_list.push_back(**ref_iter);
			}
			//add entry to duplicate map
			duplicates.insert(pair<string, list<string>>(map_iter->first, temp_list));
		}	
	}
	return duplicates;
}

map<string, list<string>> DataStore::getCatalogue()
{
	map<File, listofrefs>::iterator map_iter = files.begin();
	//create a new map of key: string and value: list of strings
	map<File, list<string>> catalogue;

	for (map_iter; map_iter != files.end(); map_iter++)
	{
		list<string> temp_list;
		for (listofrefs::iterator ref_iter = (map_iter->second).begin(); ref_iter != (map_iter->second).end(); ref_iter++)
		{//dereference the paths
			temp_list.push_back(**ref_iter);
		}
		//add entry to duplicate map
		catalogue.insert(pair<string, list<string>>(map_iter->first, temp_list));
	}
	return catalogue;
}

set<string> DataStore::getPaths()
{
	return pathset;
}

void DataStore::clearStore()
{
	files.clear();
	pathset.clear();
}

#ifdef TEST_DATASTORE

int main()
{
	std::cout << "\n ====Testing DataStore====\n\n";
	DataStore ds;

	ds.addPathtoSet("../");
	ds.addPathtoSet("../../");
	string a = "a.txt";
	string b = "b.txt";
	string c = "c.txt";
	string a1 = "../";
	string b1 = "../../";


	ds.addMapEntry(a, a1);
	ds.addMapEntry(b, a1);
	ds.addMapEntry(c, b1);

	cout << "getFileCount() = " << ds.getFileCount() << endl;
	cout << "getDirectoryCount() = " << ds.getDirectoryCount() << endl;
	return 0;
}
#endif