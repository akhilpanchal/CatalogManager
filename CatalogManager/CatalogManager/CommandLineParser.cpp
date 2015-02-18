/////////////////////////////////////////////////////////////////////////////
// CommandLineParser.cpp - Parses the Command Line Arguments and user	   //
//						   requests										   //
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

#include "CommandLineParser.h"
using namespace std;


CommandLineParser::CommandLineParser(char* const args[], int count)
{
	cout << "Command:\t";
	for (int i = 1; i < count;i++)
		cout << args[i] << " ";
	cout << endl;
	search = duplicate = recurse = false;
	if (count >= 2)
	{
		valid = true;
		path = FileSystem::Path::getFullFileSpec(args[1]);
		if (!FileSystem::Directory::exists(path))
		{
			cout << "Invalid Path!\n";
			valid = false;
			return;
		}
		if (count == 2)
			catalogue_patterns.push_back("*.*");
		else
		{
			handleArguments(args, count);
		}
	}
	else
	{
		valid = true;
		path = FileSystem::Path::getFullFileSpec("./");
		catalogue_patterns.push_back("*.*");
		//valid = false;
	}
}


//Stores the CMD arguments in data members
void CommandLineParser::handleArguments(char* const args[], int count)
{
	int i = 2;
	while (i<count && args[i][0] != '/')
	{
		catalogue_patterns.push_back(args[i]);
		i++;
	}
	while (i<count)
	{
		if (i<count && args[i][0] == '/' && args[i][1] == 'f')
		{
			search = true;
			if (args[i][2] != '\0')
			{
				string temp_key; int k = 0;
				for (int j = 2; args[i][j] != '\0'; j++)
				{
					temp_key += args[i][j];
					//k++;
				}
				//temp_key[k] = '\0';
				search_text = temp_key;
				i++;
			}
			else
			{
				search_text = args[i + 1];
				i += 2;
			}
		}
		if (i<count && args[i][0] == '/' && args[i][1] == 's')
		{
			recurse = true;
			i++;
		}
		if (i<count && args[i][0] == '/' && args[i][1] == 'd')
		{
			duplicate = true;
			i++;
		}
	}
	if (catalogue_patterns.size() == 0)
	{
		catalogue_patterns.push_back("*.*");
	}
	search_patterns = catalogue_patterns;
}

//Parses the subsequent user requests and updates data members
void CommandLineParser::parseUserRequest(string request)
{
	duplicate = valid = false;
	vector<string> temp_patterns = handleArguments(request);
	if (temp_patterns.size()!=0)
	{
		search_patterns.clear();
		search_patterns = temp_patterns;
	}
	else
		search_patterns = catalogue_patterns;
}

vector<string> CommandLineParser::handleArguments(string request)
{
	vector<string> temp_patterns;
		istringstream iss(request);
		do
		{
			string sub;
			iss >> sub;
			if (sub[0] == '\"')
			{
				valid = search = true;
				int i = 1;
				string temp;
				while(sub[i]!='\"')
				{
					if (sub[i] == '\0')
					{
						temp += ' ';
						iss >> sub;
						i = 0;
					}
					if (sub[i] == '\"')
						break;
					temp += sub[i];
					i++;
				}
				search_text = temp;
			}
			else if (sub[0] == '*')
			{
				valid = true;
				temp_patterns.push_back(sub);
			}
		} while (iss);
		return temp_patterns;
}

string CommandLineParser::getPath()
{
	return path;
}

vector<string> CommandLineParser::getCataloguePatterns()
{
	return catalogue_patterns;
}

vector<string> CommandLineParser::getSearchPatterns()
{
	return search_patterns;
}

bool CommandLineParser::getRecurse()
{
	return recurse;
}

bool CommandLineParser::getDuplicate()
{
	return duplicate;
}

bool CommandLineParser::getSearch()
{
	return search;
}

string CommandLineParser::getSearchText()
{
	return search_text;
}

bool CommandLineParser::getValid()
{
	return valid;
}

#ifdef TEST_COMMANDLINEPARSER

int main(int argc, char* args[])
{
	CommandLineParser objC(args, argc);
	cout <<"Testing CMDLineParser\n\n";
	cout <<"getSearch() = "<<objC.getSearch() << endl;
	
	cout << "getpath() = " << objC.getPath() << endl;
	//cout << "getCataloguePatterns()" << objC.getCataloguePatterns();
	cout << "getRecurse() = " << objC.getRecurse() << endl;
	cout << "getDuplicate() = " << objC.getDuplicate() << endl;
	cout << "getSearch() = " << objC.getSearch() << endl;
	cout << "getSearchText() = " << objC.getSearchText() << endl;
	cout << "getValid() = " << objC.getValid() << endl;
	//cout << "getSearchPatterns() = " << objC.getSearchPatterns();
	
}

#endif