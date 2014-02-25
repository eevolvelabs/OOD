///////////////////////////////////////////////////////////////////////
// tester.cpp   : Implementation of tester.h                         //
// version      : 1                                                  //
// Language     : Visual C++, Visual Studio 2010, SP1                //
// platform     : Sony Vio, Windows 7, Home Premium, SP1             //
// Application  : Project 3 Spring 2012                              //
// Author       : Dhaval Malaviya, Syracuse University               //
// Contact      : dmmalavi@syr.edu                                   //
///////////////////////////////////////////////////////////////////////

#include "tester.h"

// Implementation of the run() function of the child thread which
// creates the child process.
void chthreadToRunTest::run()
{
  sout << "\nStarting child thread which Spawns Child Process";
  //std::string msg;
  //sout << msg;
   std::vector<std::string> dlls;
  createTestProcess ctp;
  std::string resultString;
  std::string testName = ctp.getTestName(_xmlStr);
  resultString = "<testName>" + testName + "</testName>";
  dlls = ctp.getdllPath(_xmlStr);
  if(dlls.size() != 0) { resultString.append(ctp.createChildProc(dlls));}
  else {resultString.append("\n\nERROR:NO DLL PRESENT IN THE CONFIG XML\n\n");}
  _resultQ.enQ(resultString);
  ::Sleep(200);
  //unlocker();
}

// Blocking Q read thread, run() function which will
// create the child thread to spawn the child process
void threadToRdQ::run()
{
  sout << "\nStarting child thread which reads the blocking Q";
  std::string msg;
  std::vector<HANDLE> h;
  msg = _Q.deQ();
  while (msg != "quit")
  {
    //sout << locker << "\n  received msg: " << msg << unlocker;
    // create the child terminating thread
    tthread* ptthreadToRunTest = new tthread(*new chthreadToRunTest(msg,_resultQ))  ;
    ptthreadToRunTest->setPriority(very_high);
    ptthreadToRunTest->start();
    h.push_back(ptthreadToRunTest->handle());
    //ptthreadToRunTest->wait();
    msg = _Q.deQ();
  }
  for (int i = 0; i < (int)h.size(); i++)
  {
    tthread::wait(h.at(i));
  }
  _resultQ.enQ("quit"); // adding quit into the result Q once messages of all child thread has been added
}



////////////////////TEST STUB////////////////////

#ifdef TEST_TESTER

void main()
{
  BQueue<std::string> msgQ;
  BQueue<std::string> resultQ;

  std::string xmlString = "<testName>ExampleTest<\testName>";
  xmlString = xmlString + "<dll name=\"example.dll\" path=\"..\\dlls\">  </dll>";
  msgQ.enQ(xmlString);

  threadToRdQ parentTh(msgQ,resultQ);
  thread th(parentTh);
  th.start();
  th.wait();

}


#endif