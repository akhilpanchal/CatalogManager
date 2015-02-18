/////////////////////////////////////////////////////////////////////////////
// FileManager.cpp - Discovers the files to be added in the DataStore and  //
//					 manages the contents of the DataStore.				   //
//																		   //
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

#include "FileManager.h"
#include <sstream>

using namespace std;

FileManager::FileManager(const string& path, DataStore& ds) : path_(path), store_(ds)
{
	
}


void FileManager::createDataStore(patterns patt, bool recurse)
{
	patterns_ = patt;
	if (!recurse)
	{
		store_.addPathtoSet(path_);
		for (patterns::size_type iter = 0; iter != patterns_.size();iter++)
		{
			vector<string> files = FileSystem::Directory::getFiles(path_);
			for (vector<string>::size_type iter2 = 0; iter2 != files.size();iter2++)
			{
				//Add entry to map;
				store_.addMapEntry(files[iter2],path_);
			}
		}
	}
	else
	{
		addfilesrecurse(path_);
	}

}

void FileManager::addfilesrecurse(string path)
{	//Get full path
	string curr_path = FileSystem::Path::getFullFileSpec(path);
	//Go to the path and add it to the set of paths
	store_.addPathtoSet(curr_path);

	for (patterns::size_type iter = 0; iter != patterns_.size(); iter++)
	{//Get files in the current directory
		vector<string> newfiles = FileSystem::Directory::getFiles(curr_path,patterns_[iter]);
		for (vector<string>::size_type iter2 = 0; iter2 != newfiles.size(); iter2++)
		{
			//Add them to map with curr dir as reference
			store_.addMapEntry(newfiles[iter2], curr_path);
		}
	}
	//Get subdirs
	vector<string> subdirs = FileSystem::Directory::getDirectories(curr_path);
	for (vector<string>::size_type iter3 = 0; iter3 != subdirs.size(); iter3++)
	{//for each subdirs, perform addfilesrecurse()
		if (subdirs[iter3] != "." && subdirs[iter3] != "..")
			addfilesrecurse(curr_path + "\\" + subdirs[iter3]);
	}
}

list<string> FileManager::getSearchInfo(string key, vector<string> patterns)
{
	map<string, list<string>> catalogue = store_.getCatalogue();
	map<string, list<string>>::iterator cat_iter = catalogue.begin();
	
	//create a new map of key: string and value: list of strings
	list<string> keyfound;
	for (cat_iter; cat_iter != catalogue.end(); cat_iter++)
	{
		//cout << endl<< "extension: " << FileSystem::Path::getExt(cat_iter->first);
		//open file only if pattern matches
		string temp_patt = "*." + (FileSystem::Path::getExt(cat_iter->first));
		bool anyPattern = (find(patterns.begin(), patterns.end(), "*.*") != patterns.end());
		bool containsPattern = (find(patterns.begin(), patterns.end(), temp_patt) != patterns.end());
		if (containsPattern || anyPattern)
		{
			//open file for each path reference
			for (list<string>::iterator ref_iter = (cat_iter->second).begin(); ref_iter != (cat_iter->second).end(); ref_iter++)
			{//dereference the paths, create absolute path and open the file to search for key
				string temp_filepath = (*ref_iter) + "\\" + cat_iter->first;
				if (searchkey(temp_filepath, key))
				{
					keyfound.push_back(temp_filepath);
				}
			}
		}
	}
	return keyfound;
}


bool FileManager::searchkey(string filepath, string key)
{
	FileSystem::File searchfile(filepath);

	//File inTestFile("tempTestFile.txt");
	searchfile.open(FileSystem::File::in);
	string line;
	while(searchfile.isGood())
	{
		line = searchfile.getLine();
		line = FileSystem::Path::toUpper(line);
		key = FileSystem::Path::toUpper(key);

		if (line.find(key) != std::string::npos)
		{
			return true;
		}
	}
	searchfile.close();
	return false;
}

void FileManager::clearCatalogue()
{
	store_.clearStore();
}

#ifdef TEST_FILEMANAGER 

int main()
{
	cout << "====Testing FileManager====\n\n";
	DataStore ds;
	FileManager fm("../../",ds);
	vector<string> tp;
	tp.push_back("*.*");
	fm.createDataStore(tp, true);
}

#endif