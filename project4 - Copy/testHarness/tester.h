#ifndef TESTER_H
#define TESTER_H
///////////////////////////////////////////////////////////////////////
//  tester.h         : This package has functionailty of creating    //
//                     child read thread which will spawn another    //
//                     thread to spawn child process                 //
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 3, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class tester Operations:
    --------------------------------
    This is tester package function of the tester package is to
    a) create main thread that will read the messages from the blocking queue.
    b) in turn above thread will create the terminating threads for each message read
    c) each of terminating thread will send the message to the test exe created.
    d) each of terminating thread will also return the response from the test.exe

    This package has two class:
    a) chthreadToRunTest which is the child thread and also creates the child process
    b) threadToRdQ thread to read the blocking Q

    Public Interface:
    -----------------
     threadToRdQ parentTh(msgQ,resultQ);
     thread th(parentTh);
     th.start();
     th.wait();

     NOTE: child thread is not exposed to as public interface. Hence these two classes
           are in same package

    See test stub for example.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//  Threads.h                                                //
//  locks.h                                                  //
//  BlockingQueue.h                                          //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_TESTER tester.cpp                       //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 10 April 2012
      - first release
*/


#include <iostream>
#include <string>
#include <vector>

#include "./Threads/Threads.h"
#include "./Threads/locks.h"
#include "BlockingQueue\BlockingQueue.h"
#include "createTestProcess.h"

/// Child thread class which will be created by threadRdQ thread.
//  child thread will spawn the child process if needed
//  else it will log the message in result Q.
class chthreadToRunTest : public Thread_Processing<chthreadToRunTest>
{
public:
  chthreadToRunTest(std::string& xmlStr, BQueue<std::string>& resultQ): _xmlStr(xmlStr),_resultQ(resultQ) {}   // Constructor

  virtual void run();  // run() function
  
private:
  std::string _xmlStr;     // xml string
  BQueue<std::string>& _resultQ; // resultQ
 
};


// Read Q thread which reads the blocking Q and 
// creates the child thread passing the message to it
class threadToRdQ : public Thread_Processing<threadToRdQ>
{
public:

  threadToRdQ(BQueue<std::string>& Q,BQueue<std::string>& resultQ): _Q(Q),_resultQ(resultQ) {}  // Constructor
  
  virtual void run();   // run() function
private:
  BQueue<std::string>& _Q;  // note reference
  BQueue<std::string>& _resultQ; // blocking Q to store the result Result will be in xml format.
};


#endif