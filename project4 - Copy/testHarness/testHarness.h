#ifndef TESTHARNESS_H
#define TESTHARNESS_H

///////////////////////////////////////////////////////////////////////
//  testHarness.h    : This package is kind of top level package     //
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 3, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class testHarness Operations:
    --------------------------------
     This is test harness package which shall
     a) accept the configuration files and shall convert to string
     b) put the string created in above step a) into the Blocking Q
     c) create the reading thread which reads the messages from the Q
     d) reading thread shall create different threads for each messages 
     e) child threads created by reading thread will create the child process for testing 
     f) child thread created also will store the messages received from the child process
     g) create the test name vector later used by display package 
     h) create the result vector later used by display package
     i) create the log vector later used by display package
     j) create the child msg vector later used by display package
    
    Public Interface:
    -----------------
    testHarness th;

    bool check = th.readConfigFileGenStr(std::string& path); // Function will return false is no XML files are present at the given path
    th.insertStrInBlockQ();                                  // Function to push the xml string in to the blocking Q
    th.createnRunRdThrd();                                   // Function will create the read thread which in turn shall create child thread which spawn the child process
    th.extractXMLMsg();                                      // Function will read the resultQ and shall extract different attributes such as test name, results, dll tested, log path
    th.createTestNameVector(std::string&);                   // Function to determine the test name
    th.createdllTestedVector(std::string&);                  // Function to determine dll tested from resultQ
    th.createResultVector(std::string&);                     // Function to determine result from resultQ
    th.createLogLocVector(std::string&);                     // Function to determine the location of log for each test run
    std::vector<std::string> testNames = th.getTestNames();  // Function which will return all the test names in vector
    std::vector<std::vector<std::string>> results = th.getResults();  // Function which will return results of each dll of each test name in form of vector of vector of string
    std::vector<std::vector<std::string>> dllsTested = th.getdllsTested(); //// Function which will return dlls tested of each test name in form of vector of vector of string
    std::vector<std::vector<std::string>> childMsg = th.getchildMsg(); // Function which will return child msg of each dll of each test name in form of vector of vector of string

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
//  tester.h                                                 //
//  client.h                                                 //
//  XmlReader.h                                              //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_TESTHARNESS testHarness.cpp             //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 10 April 2012
      - first release
*/

#include <string>

#include "tester.h"           // This is the package which will create the rd thread and test thread from that
#include "Threads\Threads.h"  // Thread class
#include "Threads\locks.h"    // Lock class
#include "BlockingQueue\BlockingQueue.h" // Blocking Q header file
#include "client.h"           // This is the client package which shall insert the config messages into the blocking Q
#include "XmlReader.h"

class testHarness
{
public:
  bool readConfigFileGenStr(std::string&);  // function which will convert the xml file content into the string and shall store into the vector
  void insertStrInBlockQ();                 // function to enqueue the xml string
  void createnRunRdThrd();                  // function to create the read thread and there by which will create another child thread which will spawn the child process
  void extractXMLMsg();                     // function to extract the xml string details stored in to the resultQ by the child thread
  void createTestNameVector(std::string&);  // function to create the vector of all test names
  void createdllTestedVector(std::string&); // function to create the vector of vector of string of the dlls tested
  void createResultVector(std::string&);    // function to create the vector of vector of string of the results forwarded by child thread
  void createLogLocVector(std::string&);    // function to create the vector of vector of string of the log location is generated
  std::vector<std::string> getTestNames();  // function which return all test names in form of vector
  std::vector<std::vector<std::string>> getResults(); // function which return the results of each test case run
  std::vector<std::vector<std::string>> getdllsTested(); // function which return the dlls tested 
  std::vector<std::vector<std::string>> getchildMsg(); // function which will return the child msg which will consists of the path and name of log file stored
  
private:
  BQueue<std::string> msgQ;              // Input Blocking Q to store the XML config messages
  std::vector<std::string> xmlRdString;  // XML config file contents converted to string 
  BQueue<std::string> resultQ;           // Blocking Q used to store the results obtained from the child thread
  std::vector<std::string> testNames;    // vector indicating the testnames
  std::vector<std::vector<std::string>> results;      // vector indicating the result
  std::vector<std::vector<std::string>> dlls;         // vector indicating the dlls executed
  std::vector<std::vector<std::string>> childMsg;     // vector indicating the any message from the child
  
};


#endif