#ifndef CREATETESTPROCESS_H
#define CREATETESTPROCESS_H

///////////////////////////////////////////////////////////////////////
//  createTestProcess.h : This package has functionailty of creating //
//                        the child process.                         //
//  Version             : 1.0                                        //
//  Language            : Visual C++, Visual Studio 2010, SP1        //
//  Platform            : Sony VIO, Win 7 Home Premium, SP1          //
//  Application         : Project 3, 2012                            //
//  Author              : Dhaval Malaviya, Syracuse University       //
//  Contact             : dmmalavi@syr.edu                           //
///////////////////////////////////////////////////////////////////////
/*
    class createTestProcess Operations:
    ------------------------------------
    this package has mainly following functions
    a) set the variables required to create the child process
    b) spawn the child process
    c) read the pipe connected to child process
    d) extract all dll file names from the xml string
    e) get the test name from the xml passed
    f) has a global function to retrive while creating the child process

    Public Interface:
    -----------------
    createTestProcess ctp;
    
    std::string output =  ctp.createChildProc(std::vector<std::string>& dlls);  // Function which will create the child process and will return
                                                                                // string consists of the result from the child process.
    std::string testName = ctp.getTestName(std::string&);                       // Function to determine the test names mentioned in the configuration file.
  
    std::vector<std::string> dlls = ctp.getdllPath(std::string&);               // Function to determine the dlls and their respective paths.
    
    See test stub for example.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//  BlockingQueue.h                                          //
//  XmlReader.h                                              //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_CREATETESTPROCESS createTestProcess.cpp //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 10 April 2012
      - first release
*/

#include <windows.h>
#include <iostream>

#include "BlockingQueue\BlockingQueue.h"
#include "XmlReader.h"
using namespace std;


class createTestProcess
{
public:
  std::string createChildProc(std::vector<std::string>& dlls);  // Function which will create the child process and will return
                                                                // string consists of the result from the child process.
  std::string getTestName(std::string&);              // Function to determine the test names mentioned in the configuration file.
  std::vector<std::string> getdllPath(std::string&);    // Function to determine the dlls and their respective paths.
  
private:
  
  std::string testName;
  std::vector<std::string> dllToRunTest;
 
};

#endif
















