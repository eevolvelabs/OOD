#ifndef CLIENT_H
#define CLIENT_H
///////////////////////////////////////////////////////////////////////
//  client.h         : This package has functionailty of reading the //
//                     and put the message into the Message Q        //  
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 3, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class client Operations:
    --------------------------------
    this package has mainly following functions
    a) to read the xml files present at the given path
    b) convert the message into the string
    c) push those messages into the blocking Q
    
    Public Interface:
    -----------------
    client cl;
    std::string xmlString = readXML(std::string&);   // function which shall read the xml present at the given path and shall generate the string out
                                                     // of it.
    pushMsgInQueque(std::string&, BQueue<std::string>&);  // member function to insert the message (string obtain by
                                                          // converting xml content into string.

    See test stub for example.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//  BlockingQueue.h                                          //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_CLIENT client.cpp                       //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 10 April 2012
      - first release
*/

// client class which shall 
// a) read the xml and 
// b) convert xml data into string
// c) push the step b) string into blocking queque
// It has thread which does above functions.
#include <iostream>
#include <string>
#include "./BlockingQueue/BlockingQueue.h"

class client
{
  // public interface
public:
  std::string readXML(std::string&);   // function which shall read the xml present at
                                       // the given path and shall generate the string out
                                       // of it.
  void pushMsgInQueque(std::string&, BQueue<std::string>&);  // member function to insert the message (string obtain by
                                                             // converting xml content into string.

};



#endif