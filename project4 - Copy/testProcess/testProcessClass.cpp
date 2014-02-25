/////////////////////////////////////////////////////////////////////////////
//  testProcessClass.cpp : Implementation of class testProcessClass        //
//  Version              : 1.0                                             //
//  Language             : Visual C++, Visual Studio 2010, SP1             //
//  Platform             : Sony VIO, Win 7 Home Premium, SP1               //
//  Application          : Project 3, 2012                                 //
//  Author               : Dhaval Malaviya, Syracuse University            //
//  Contact              : dmmalavi@syr.edu                                //
/////////////////////////////////////////////////////////////////////////////


// THis is test process class package which shall 
// a) reads the XML file passed to it from parent process
// b) determines the test name
// c) determines the dll name and its path


#include <stdio.h>
#include "testProcessClass.h"


// Function used to display on the child console
void testProcessClass::displayStr(HANDLE& console,DWORD& dwWritten,std::string& dispStr)
{
  WriteFile(console,dispStr.c_str(),dispStr.size(),&dwWritten,NULL);
}

// function to find the path where the log file created by the child process are stored.
std::string testProcessClass::displayLogPath(char*& dlls)
{
  fileMgr fm;  // Instance of the file manager
  std::string path = fm.getCurrentDirectory();
  path.append("\\");
  // Removing dll from the argv
  std::string temp = dlls;
  int index1 = temp.find_last_of("\\");
  if(index1 == -1)
  { index1 = temp.find_last_of("/");}
  int index2 = temp.find(".dll");
  temp = temp.substr(index1+1,temp.size()-index1-1-4);
  path = path.append(temp);
  path.append("TL.log");
  return path;
}

// Function to create the xml string
std::string testProcessClass::createXML(std::vector<std::string>& dlls,std::vector<std::string>& results, std::vector<std::string>& detailedLog)
{
  XmlWriter wtr;
  wtr.addDeclaration(); /*<---Adding the declaration*/ wtr.start("display"); /*<---adding the main title*/
  XmlWriter wtrSub; /*<---Create the sub xml writer obj*/ 
  // XML format will be
  // <display>
  //   <test>
  //      <dllname> dllname<\dllname>
  //      <result> result <\result>
  //      <detaillog> path to detailedlog <\detaillog>
  //   <\test>
  // <\display>
  
  XmlWriter wtrSub1;
  for(int i = 0; i < (int)dlls.size(); ++i)
  {
    wtrSub.start("test"); /*<----adding main title*/
    wtrSub1.start("dllname");
    wtrSub1.addBody(dlls.at(i));
    wtrSub1.end();
    wtrSub.addBody(wtrSub1.xml());
    wtrSub1.clear();
    wtrSub1.start("result");
    wtrSub1.addBody(results.at(i));
    wtrSub1.end();
    wtrSub.addBody(wtrSub1.xml());
    wtrSub1.clear();
    wtrSub1.start("detailLog");
    wtrSub1.addBody(detailedLog.at(i));
    wtrSub1.end();
    wtrSub.addBody(wtrSub1.xml());
    wtrSub1.clear();
    wtrSub.end();
    wtr.addBody(wtrSub.xml());
    wtrSub.clear();
  }
  wtr.end();
  return wtr.xml();
}


// Function which will 
// a) aload the dll library along with error checking
// b) GetProcAddress for the test function from the dll to run test
// c) runs the test from dll.
std::string testProcessClass::ldnrundlltest(char*& dllPath)
{
  HMODULE hmod = LoadLibrary(dllPath);
  if(!hmod)
  {
    std::cout << "\n  failed to load derived.dll\n\n";
    return "ERROR: Failed To Load dll";
  }
  // Get the process address from the dll.
  typedef ITest* (*gMO)();
  gMO gMakeObj = (gMO)GetProcAddress(hmod,"gCreateTest");
  if(!gMakeObj)
  {
    std::cout << "\n  GetProcAddress failed for gMakeObj\n\n";
    return "ERROR: GetProcAddress Fail to Load the function";
  }
  ITest* createTestPtr;
  createTestPtr = gMakeObj();
  
  bool testResult = createTestPtr->test();
  if(testResult == true)
  {  return "PASSED";}
  else { return "FAILED"; }

}

// Member function to move files from the given path to work dir
void testProcessClass::moveFilesToWorkDir(std::vector<std::string> path, std::string workDir)
{
  fileMgr fm;
  std::string tempWorkDir = workDir;
  for(int i = 0; i < (int) path.size(); ++i)
  {
    int index = path.at(i).find_last_of("\\"); // Appending the \ so to add filename below
    std::string fileName = path.at(i).substr(index+1,path.at(i).size()-1);
    tempWorkDir = tempWorkDir.append("\\");
    tempWorkDir = tempWorkDir.append(fileName);

    int done = fm.copyFilesToWDir(path.at(i),tempWorkDir);
    tempWorkDir.clear();
    tempWorkDir = workDir;
  }
}
//------------------------TEST STUB------------------------//

#ifdef TEST_TESTPROCESSCLASS

void main()
{
  std::cout << "\nThis is test stub for testing the class testProcessClass\n";
  // create the instance of the testProcessClass
  testProcessClass tp;

  HANDLE console = CreateFile("CONOUT$",GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0); // get Handle to screen buffer so we can write a few visible lines
  DWORD dwWritten;  // bytes written
  std::string testString = "\nThis is test string. To be displayed on the console\n";
  tp.displayStr(console,dwWritten,testString);

  std::vector<char*> dlls;
  std::vector<std::string> dllsStr;
  std::vector<std::string> results;
  std::vector<std::string> detailLog;
  dlls.push_back("../../dummy1.dll");
  dllsStr.push_back("../../dummy1.dll");
  dlls.push_back("../../dummy2.dll");
  dllsStr.push_back("../../dummy2.dll");
  dlls.push_back("../../dummy3.dll");
  dllsStr.push_back("../../dummy3.dll");
  results.push_back(tp.ldnrundlltest(dlls.at(0)));
  results.push_back(tp.ldnrundlltest(dlls.at(1)));
  results.push_back(tp.ldnrundlltest(dlls.at(2)));
  detailLog.push_back(tp.displayLogPath(dlls.at(0)));
  detailLog.push_back(tp.displayLogPath(dlls.at(1)));
  detailLog.push_back(tp.displayLogPath(dlls.at(2)));
  std::string xml = tp.createXML(dllsStr,results,detailLog);

  std::cout << xml;
  // Visual check is requred for this test stub
}

#endif