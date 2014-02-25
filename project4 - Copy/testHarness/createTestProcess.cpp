///////////////////////////////////////////////////////////////////////
// createTestProcess.cpp   : Implementation of createTestProcess.h   //
// version                 : 1                                       //
// Language                : Visual C++, Visual Studio 2010, SP1     //
// platform                : Sony Vio, Windows 7, Home Premium, SP1  //
// Application             : Project 3 Spring 2012                   //
// Author                  : Dhaval Malaviya, Syracuse University    //
// Contact                 : dmmalavi@syr.edu                        //
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string>
#include "createTestProcess.h"

//using namespace System;

//----< retrieve system error message >--------------------------------
std::string GetLastErrorString()
{
  DWORD errorCode = GetLastError();
  DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM 
    | FORMAT_MESSAGE_ALLOCATE_BUFFER;
  LPCVOID lpSource = NULL;
  DWORD dwMessageID = errorCode;
  DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
  LPSTR lpBuffer;
  DWORD nSize = 0;
  va_list *Arguments = NULL;

  FormatMessage(
    dwFlags,lpSource,dwMessageID,dwLanguageId, 
    (LPTSTR)&lpBuffer,nSize,Arguments
    );

  if(lpBuffer)
    return std::string(lpBuffer);
  return "";
}

// Function to spawn child process.
std::string createTestProcess::createChildProc(std::vector<std::string>& dlls)
{ // declare structures for CreateProcess
  STARTUPINFO startInfo;            // we fill to control startup
  PROCESS_INFORMATION procInfo;     // CreateProcess will fill
  SECURITY_ATTRIBUTES sa;           // set parameters for CreatePipe
  sa.bInheritHandle = TRUE;         // tells pipe to support inheritance of handles
  sa.lpSecurityDescriptor = NULL;   // client process security properties
  sa.nLength = sizeof(sa); HANDLE hRead;  HANDLE hWrite;
  if(!::CreatePipe(&hRead, &hWrite, &sa, 0))  // Create the anonymous pipe
  { std::cout << "\n  could not create anonymous pipe\n\n" << "\n\n" << GetLastErrorString().c_str() << "\n\n"; return "ERROR: Could Not Create Pipe"; }
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // save parent stdout handle
  SetStdHandle(STD_OUTPUT_HANDLE,hWrite);           // Set parent stdout handle to pipe write handle. This lets child access pipe.
  char *pCL; std::string test;
  for(int count = 0; count < (int)dlls.size(); ++count)   // For loop which will make string out of the vector. String is made to pass it as argument to child process.
  { if(count == 0) { test = dlls.at(0).c_str();} else {test.append("  "); test.append(dlls.at(count).c_str());} }
  pCL = (char*)test.c_str();
  LPCTSTR appName                = "../debug/testProcess.exe";   // program to run
  LPTSTR  commandLine            = pCL;                // main's args
  LPSECURITY_ATTRIBUTES procSec  = &sa;                // default security
  LPSECURITY_ATTRIBUTES thrdSec  = NULL;               // default security
  BOOL inheritHandles            = TRUE;               // inherit so child can get pipe Write Handle
  DWORD createFlags              = CREATE_NEW_CONSOLE; // make a console
  //DWORD createFlags              = CREATE_NO_WINDOW;   // don't allocate a console for child
  LPVOID environment             = NULL;               // caller's evironmt
  LPCTSTR currentPath            = NULL;               // default dir
  LPSTARTUPINFO pStartInfo       = &startInfo;         // set process style
  LPPROCESS_INFORMATION pPrInfo  = &procInfo;          // retrieve info
  string buildTitle = "Child Process: ";   buildTitle += "../debug/testProcess.exe";
  GetStartupInfo(&startInfo);
  startInfo.lpTitle = (char*)buildTitle.c_str(); startInfo.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE | STARTF_USESTDHANDLES; 
  startInfo.dwX = 200; startInfo.dwY     = 250;  startInfo.dwXSize = 500; startInfo.dwYSize = 300;
  startInfo.hStdOutput = hWrite; startInfo.hStdError = hWrite;
  cout << "\n\nAttempting to start: " << "../debug/testProcess.exe" << "\n  with arguments: " << pCL << endl;
  BOOL OK = CreateProcess(appName,commandLine,procSec,thrdSec,inheritHandles,createFlags,environment,currentPath,pStartInfo,pPrInfo);  // Trying to create the child process using createProcess Function
  CloseHandle(hWrite);                               // Now close the hWrite handle
  SetStdHandle((DWORD)STD_OUTPUT_HANDLE,hStdout);    // restore parent stdout handle
  if(!OK) { cout << "\n\n failed to create process: " << appName << "\n\n" << GetLastErrorString().c_str() << "\n\n"; return "Failed To Spawn Child Process"; }
  const size_t BUFSIZE = 256; char buffer[BUFSIZE+1]; DWORD dwRead; std::string outFromChildP = ""; // read child's output from pipe
  for(;;)  { cout << "\n\n reading pipe...\n";
    if(!ReadFile(hRead,buffer,BUFSIZE,&dwRead,NULL))
      break;
    buffer[dwRead] = 0; std::string str(buffer);
    outFromChildP = outFromChildP + str; // cout << str.c_str();
    if(str.find("quit") < str.size()) break; }
  WaitForSingleObject(procInfo.hProcess,INFINITE); // if you want to see the child window you need to wait until the user closes it, then quit
  CloseHandle(hRead); cout << "\n\n";
  int index1 = outFromChildP.find_first_of("<"); int index2 = outFromChildP.find_last_of(">");
  outFromChildP = outFromChildP.substr(index1,outFromChildP.size()-index1-4);
  return outFromChildP;}


// Function which will return the test name present in the XML file string
std::string createTestProcess::getTestName(std::string& xmlMsg)
{
  // Initializing the XmlReader object with input string as content of the xml file.
  XmlReader rdr(xmlMsg);
  try{
  while(rdr.next()) // While loop which will go through the xml to find test name in XML file.
  {
    // Check if the tag read from the xml is for test name
    if(rdr.tag().compare("testName") == 0)
    {
      testName = rdr.body().c_str();
      return testName;
    }
  }
  }
  catch(std::exception ex){ std::cout << "\n**********************************\n" << ex.what() << "\n**********************************\n";};
  testName = "Test"; // if no test name found in the xml then use Test as default test name
  return testName;
}

// Function which will return vector of the string indicating the dll files which need 
// to be tested.
std::vector<std::string> createTestProcess::getdllPath(std::string& xmlMsg)
{
  std::vector<std::string> tempStrName; // Temp string used to append the dll names to its path
  std::vector<std::string> tempStrPath;
  XmlReader rdr(xmlMsg);  // instantiate the xmlReader object with xml inform of string passed
  try{
  while(rdr.next())       // loop through xml
  { if(rdr.tag().compare("dll") == 0) // if dll tag found then read its attributes. its attributes will be dll name and path for its location
    { // if dll tag found then, store the respective dll name and its path
      XmlReader::attribElems attribs;
      try
      { attribs = rdr.attributes(); }
      catch(std::exception ex)
      { std::cout<<ex.what();  };
      for(size_t i=0; i<attribs.size(); ++i)
      { if(attribs[i].first.compare("name") == 0)
        { tempStrName.push_back(attribs[i].second.c_str()); }
        else if(attribs[i].first.compare("path") == 0)
        { tempStrPath.push_back(attribs[i].second.c_str()); }
      }
    }
  }
  }catch(std::exception ex){ std::cout << "\n**********************************\n" << ex.what() << "\n**********************************\n";};
  // combine path and dll name
  try{
   if(tempStrName.size() == tempStrPath.size())
    {
      for(int i = 0; i < (int)tempStrName.size(); ++i)
      {
        dllToRunTest.push_back(tempStrPath.at(i).append(tempStrName.at(i)));
      }
    }
   else if(tempStrName.size() < 1 || tempStrPath.size() < 1)
   { return dllToRunTest; }
  else { throw "exception";} // Need to throw the exception here.
  }
  catch(char* ) { std::cout <<  "\n\n****************EXCEPTION*********************\nNumber of dll files and path mentioned in config XML does not match\n.Correct the Config XML\n****************EXCEPTION*********************\n"; return dllToRunTest; }
  
 return dllToRunTest;
}


/////////////////////////TEST STUB///////////////////////////

#ifdef TEST_CREATETESTPROCESS

void main()
{
  createTestProcess ctp;
  std::string xml = "<testName>ExampleTest<\testName>";
  std::string testName = ctp.getTestName(xml);                       // Function to determine the test names mentioned in the configuration file.
  
  std::string xml = "<dll name=\"example.dll\" path=\"..\dlls\">  </dll>";
  std::vector<std::string> dlls = ctp.getdllPath(xml);
  // To run test for creation of child process
  // make sure testProcess.exe is present
  //std::string output =  ctp.createChildProc(std::vector<std::string>& dlls);  // Function which will create the child process and will return
                                                                                // string consists of the result from the child process.
}


#endif