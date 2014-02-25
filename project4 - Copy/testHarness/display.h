#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////
//  display.h        : This package shall display the results in     //
//                     good form.                                    //
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 3, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class display Operations:
    --------------------------------
    This is display package:
    This package will display the results in good way on the console.
    
    Public Interface:
    -----------------
     display disp;
     disp.displayResult(std::vector<std::string>& testname; std::vector<std::vector<std::string>& dlls, std::vector<std::vector<std::string>& results, std::vector<std::vector<std::string>& childMsg);

     See test stub for example.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_DISPLAY display.cpp                     //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 10 April 2012
      - first release
*/
#include <iostream>
#include <vector>
#include <string>

class display
{
public:
  // Function to display the results of the child process on console
  std::string displayResult(std::vector<std::string>&,std::vector<std::vector<std::string>>&,std::vector<std::vector<std::string>>&,std::vector<std::vector<std::string>>&);
  
};






#endif