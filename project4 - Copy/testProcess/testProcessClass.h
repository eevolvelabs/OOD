#ifndef TESTPROCESSCLASS_H
#define TESTPROCESSCLASS_H

/////////////////////////////////////////////////////////////////////////////
//  testProcessClass.h : This class implements different helper            //
//                       functions used by the child process "testProcess" //
//  Version            : 1.0                                               //
//  Language           : Visual C++, Visual Studio 2010, SP1               //
//  Platform           : Sony VIO, Win 7 Home Premium, SP1                 //
//  Application        : Project 3, 2012                                   //
//  Author             : Dhaval Malaviya, Syracuse University              //
//  Contact            : dmmalavi@syr.edu                                  //
/////////////////////////////////////////////////////////////////////////////
/*
    class testProcessClass.h Operations:
    ------------------------------------
    This class provides helper function which can:
    a) create xml out of the supplied vector of strings
    b) display on the console using console handle passed by testProcess.exe
    c) load and run the dll files
    d) determine the path where the detail logs for test will be stored

    Public Interface:
    -----------------
    testProcessClass tp;
    
    tp.displayStr(HANDLE&,DWORD&,std::string&);             // Function which displays on console
    
    std::string message = ldnrundlltest(char*& dlls);       // Function which will load the dll and runs the test function of it
    
    std::string path = displayLogPath(char*& dlls);         // function which will create the string for path where log files are stored
    
    std::string xml = createXML(std::vector<std::string>&dlls,std::vector<std::string>& result,std::vector<std::string>& detailedlog); // function to create the xml string
    
    bool copyFilesToWDir(std::vector<std::string>& path)    // copy files to working directory 
    See test stub for example.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//  fileMgr.h                                                //
//  XmlWriter.h                                              //
//  ITest.h                                                  //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_TESTPROCESSCLASS testProcessClass.cpp   //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.1 : 23 April 2012
      - Added function which shall copy the files from path to working
        directory. Working directory is "../thWorkdir/"
    ver 1.0 : 10 April 2012
      - first release
*/

///////////////////////////////////////////////////////////////
//                         Declarations                      //
///////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "fileMgr.h"
#include "XmlWriter.h"
#include "ITest.h"

class testProcessClass
{
public:
  void displayStr(HANDLE&,DWORD&,std::string&);             // Function which displays on console
  std::string ldnrundlltest(char*&); // Function which will load the dll and runs the test function of it
  std::string displayLogPath(char*&); // function which will create the string for path where log files are stored
  std::string createXML(std::vector<std::string>&,std::vector<std::string>&,std::vector<std::string>&); // function to create the xml string
  void moveFilesToWorkDir(std::vector<std::string>,std::string);
private:
 // NO DATA MEMBERS 
};

#endif