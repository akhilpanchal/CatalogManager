/////////////////////////////////////////////////////////////////////////////
// Executive.cpp -	Initializes the components of Catalogue Manager		   //
//					Application and commands each component to carry out   //
//					its job												   //
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

#include<iostream>
#include<string>
#include<set>
#include<list>
#include<map>
#include"CommandLineParser.h"
#include"FileManager.h"
#include"Display.h"

using namespace std;

#ifdef TEST_EXECUTIVE

int main(int argc, char* args[])
{
	CommandLineParser clp(args, argc);
	DataStore ds;
	FileManager fm(clp.getPath(), ds);
	Display d(ds);
	if (clp.getValid())
	{
		fm.createDataStore(clp.getCataloguePatterns(), clp.getRecurse());
		string user_reqs = "";
		do
		{
			d.genericDisplay(clp.getValid(), clp.getDuplicate(), clp.getSearch(), clp.getSearchText(), fm.getSearchInfo(clp.getSearchText(), clp.getSearchPatterns()));
			getline(cin, user_reqs);
			clp.parseUserRequest(user_reqs);
		} while (user_reqs != "");
	}
	else
	{
		d.genericDisplay(clp.getValid(), false, false, "", fm.getSearchInfo(clp.getSearchText(), clp.getSearchPatterns()));
	}
	cout << "-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n";
	return 0;
}

#endif