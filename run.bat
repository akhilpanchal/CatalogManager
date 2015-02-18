:run.bat
:
:runs filecatalogue code

@echo off

echo .& echo.==========Testing REQUIREMENT 3==========& echo.
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory *.cpp *.txt /s
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory *.cpp
echo ==========For REQUIREMENT 4, please refer to DataStore.cpp file in the CatalogManager Solution==========& echo.
echo ==========Testing REQUIREMENT 5==========& echo.
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory *.* /s /d
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory /d
echo ==========Testing REQUIREMENT 6==========& echo.
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory /s /d /f"akhil panchal"
echo ==========Testing REQUIREMENT 7==========& echo.
.\VSHelp\Debug\CatalogExecutive.exe 
echo ==========Testing REQUIREMENT 8 - Enter query (text and pattern) when prompted.==========& echo.
.\VSHelp\Debug\CatalogExecutive.exe TestDirectory /s
echo ==========For REQUIREMENT 9, please refer to Executive.cpp and Display.cpp in the CatalogManager Solution.==========& echo.
echo -x-x-x-x-x-x-x-x-x-x-x-ALL REQUIREMENTS DEMONSTRATED-x-x-x-x-x-x-x-x-x-x-x-

