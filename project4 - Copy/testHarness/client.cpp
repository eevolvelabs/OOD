///////////////////////////////////////////////////////////////////////
// client.cpp   : Implementation of client.h                         //
// version      : 1                                                  //
// Language     : Visual C++, Visual Studio 2010, SP1                //
// platform     : Sony Vio, Windows 7, Home Premium, SP1             //
// Application  : Project 3 Spring 2012                              //
// Author       : Dhaval Malaviya, Syracuse University               //
// Contact      : dmmalavi@syr.edu                                   //
///////////////////////////////////////////////////////////////////////


#include <fstream>
#include <sstream>
#include "client.h"


// Function to read the XML file and convert its content to
// the string
std::string client::readXML(std::string& xmlPath)
{
  // path checking will be performed in the file in which
  // readXML is called.
  // Reading the xml at path represented at xmlPath
  std::ifstream inputXMLString (xmlPath);

  // Converting the content of the xml file read into 
  // string
  std::string content( (std::istreambuf_iterator<char>(inputXMLString) ),
    (std::istreambuf_iterator<char>()    ) );

  return content;
}

// Function to push the string message into the blocking Q
void client::pushMsgInQueque(std::string& msg, BQueue<std::string>& sQ)
{
  sQ.enQ(msg);
}


///////////////////TEST STUB////////////////////////
#ifdef TEST_CLIENT

#include "tester.h"
#include "Threads\Threads.h"
#include "Threads\locks.h"
//#include "createTestProcess.h"
void main()
{
  std::string test;
  test = "hi my name is dhaval";
  BQueue<std::string> sQ;
  std::string testend = "quit";
  client cl;
  cl.pushMsgInQueque(test,sQ);
  cl.pushMsgInQueque(test.append("1"),sQ);
  cl.pushMsgInQueque(test.append("2"),sQ);
  cl.pushMsgInQueque(test.append("3"),sQ);
  cl.pushMsgInQueque(testend,sQ);

  //threadToRdQ parentTh(sQ);
  //thread th(parentTh);
  //th.start();
  //th.wait();
  
  //parentTh.wait()

}

#endif