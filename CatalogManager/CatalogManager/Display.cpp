/////////////////////////////////////////////////////////////////////////////
// Display.cpp -	Displays the contents of the File Catalogue as		   //
//					requested by the user								   //
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

#include "Display.h"

using namespace std;

Display::Display(DataStore& ds) : catalogue(ds)
{
	
}

void Display::summary()
{
	cout << endl << "==========Catalogue Summary:==========" << endl;
	cout <<"("<< catalogue.getFileCount() << ") files found in ";
	cout <<"("<< catalogue.getDirectoryCount() << ") directories."<< endl;
}

void Display::duplicates()
{
	//Traverse map and retrieve entries that have value size greater than 1
	map<string, list<string>> duplicates = catalogue.getDuplicates();
	map<string, list<string>>::iterator dup_iter = duplicates.begin();

	cout << endl << endl;
	if (duplicates.size() == 0)
	{
		cout << "No duplicate files found!\n\n";
	}
	else
	{
		cout << "==========Duplicate File Name Information==========\n\n";
		cout << "File Name\tPaths\n\n";
		//display duplicates
		for (dup_iter = dup_iter; dup_iter != duplicates.end(); dup_iter++)
		{
			cout << dup_iter->first;
			list<string>::iterator path_iter = (dup_iter->second).begin();
			for (path_iter = path_iter; path_iter != (dup_iter->second).end(); path_iter++)
			{
				cout << "\t\t" << *path_iter << endl;
			}
			cout << endl;
		}
	}
	
}

//Displays locations where search text is found
void Display::searchInfo(string key, list<string> foundLocations)
{
	cout << endl << endl;
	if (foundLocations.size() != 0)
	{
		cout << "Key \"" << key << "\" found in "<<foundLocations.size()<<" file(s):\n\n";
		for (list<string>::iterator list_iter = foundLocations.begin(); list_iter != foundLocations.end(); list_iter++)
		{
			cout << "\t" << *list_iter << endl;
		}
	}
	else
	{
		cout << "Key \"" << key << "\" not found in the catalogue.\n";
	}
	
}

void Display::genericDisplay(bool valid, bool dup, bool search, string key, list<string> foundLocations)
{
	if (valid)
	{
		summary();
		if (dup)
			duplicates();
		if (search)
			searchInfo(key, foundLocations);
		cout << endl << "Enter Search Text and/or patterns or Press Enter to Quit!\n";
	}
	else
	{
		cout << "Invalid command:\nFormat: /f<\"text\"> <filepatterns>\n";
	}
}

void Display::displayCatalogue()
{
	set<string> temp = catalogue.getPaths();
	for (set<string>::iterator i = temp.begin(); i != temp.end();i++)
	{
		cout << endl << "Path " << *i;
	}
}

#ifdef TEST_DISPLAY

int main()
{
	cout << "====Testing Display====\n\n";
	DataStore ds;
	Display objd(ds);
	list<string> temp;
	temp.push_back("../");
	objd.genericDisplay(true, true, true, "akhil", temp);
	return 0;
}

#endif