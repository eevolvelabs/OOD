///////////////////////////////////////////////////////////////////////
// fileMgr.cpp  : Implementation of fileMgr.h interface              //
// version      : 1                                                  //
// Language     : Visual C++, Visual Studio 2010, SP1                //
// platform     : Sony Vio, Windows 7, Home Premium, SP1             //
// Application  : Project 1 Spring 2012                              //
// Author       : Dhaval Malaviya, Syracuse University               //
// Contact      : dmmalavi@syr.edu                                   //
///////////////////////////////////////////////////////////////////////

// Will eventually put some XML processing in this file.
//
#include<string>    // Angle brackets looks into system directory
#include<vector>
#include<iostream>
#include "WinTools.h" // quotes looks into local directory
#include "fileMgr.h"

using namespace Win32Tools;


fileMgr::fileSet fileMgr::findFiles(const std::string& path, const std::string& pattern)
{
  // Eventually we will use XML config file to possibly modify fileSet
  return directory::GetFiles(path, pattern);
   
}

// Check if the directory exists
bool fileMgr::checkifdirExists(std::string& path)
{
  return directory::DirectoryExists(path);
}

// above function when called for particular path and pattern (in our case pattern will
// be either .cpp or .h) shall return all the possible files in that file. However, out of 
// those file list, below function will drop interface files. 
// Interface here will be 
// a) ITest.h
// b) ITestGenerator.h
// c) ITestLogger.h
// Other functionality to be added later is, below function will also drop those files 
// which are not present in the XML file.
fileMgr::fileSet fileMgr::returnFilesToBeTested(const std::vector<std::string> allFoundFiles)
{
  // eliminating files with name
  // a) ITest.h
  // b) ITestGenerator.h
  // c) ITestLogger.h
  for (int i = 0; i <(int) allFoundFiles.size(); i++)
  {
    if(allFoundFiles[i].find("ITest") == -1 && allFoundFiles[i].find("ITestGenerator") && allFoundFiles[i].find("ITestLogger"))
    { 
      filesToTest.push_back(allFoundFiles[i]);
    }
  }
  return filesToTest;

}

std::string fileMgr::getCurrentDirectory()
{
  return directory::GetCurrentDirectoryW(); 
    //directory::GetCurrentDirectoryW();
}


///// ------TEST STUB ---------------
#ifdef TEST_FILEMGR


// Standard says main should be of return type int as standard says
// main may return different errors which can be int.
int main(int argc, char* argv[])
{
  fileMgr fs;

  std::string path;
  std::string pattern;

  std::vector<std::string> foundFiles;
  std::vector<std::string> filesToBeTested;

  path = directory::GetCurrentDirectoryW();
  pattern = "*.h";

  foundFiles = fs.findFiles(path,pattern);
  filesToBeTested = fs.returnFilesToBeTested(foundFiles);

  //// assumung path is named by argv[1]
  //// assumung pattern is named by argv[2], argv[3]....

  //// Declaring default
  //std::string path = ".";
  //std::string pattern = "*.*";

  //if(argc > 1)
  //  path = argv[1];

  //if(argc > 2)
  //  pattern = argv[2];


  //fileMgr fm(argc, argv);

  //fileMgr::fileSet fs = fm.findFiles(path, pattern);

  //int count = 2;
  //while(count < argc)
  //{
  //  pattern = argv[count++];
  //  fileMgr::fileSet files = fm.findFiles(path, pattern);

  //  for(int i = 0; i < files.size(); ++i)
  //    std::cout << "\n " << files[i];
  //  std::cout << "\n\n";

  //}
  std::cout << "THIS IS TEST STUB";

  int dummy;
  std::cout << "Please enter anything....";
  std::cin >> dummy;

}
#endif


