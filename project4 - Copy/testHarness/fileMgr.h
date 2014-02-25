#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
//  fileMgr.h        : This is wrap class around the fileInfo class  //  
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 1, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class fileMgr Operations:
    --------------------------------
    The fileMgr class acquires file information from win32 API
    functions and returns parts of the information on demand.
    Specifically a fileMgr object extracts file name. files to be tested
     and current working directory.
    
    Public Interface:
    -----------------
    fileMgr fm;
    std::vector<std::string> = fm.findFiles(cwdPath,"*.xml");
    std::vector<std::string> = fm.returnFilesToBeTested(testFiles);
    std::string getCurrentDirectory();

    See test stub for example of how to use createFile object to check for the missing 
    files, creating the dependency graph and then finding the root. 
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//  WinTools.h                                               //
//  WinTools.cpp                                             //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -TEST_FILEMGR fileMgr.cpp                     //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 2.0 : 22 April 2012
        Added method to create the directory at the given path
    ver 1.0 : 1 FEB 2012
      - first release
*/

///////////////////////////////////////////////////////////////
//                         Declarations                      //
///////////////////////////////////////////////////////////////

#include <vector>
#include <string>

class fileMgr
{
public:
  typedef std::vector<std::string> fileSet; // Kept it local to this class so as to avoid collision of name fileSet with same name some where else if declared global
  //fileMgr(int argc, char* argv[]);

  std::vector<std::string> findFiles(const std::string& path, const std::string& pattern);
  std::vector<std::string> returnFilesToBeTested(const std::vector<std::string> allFoundFiles); 
  std::string getCurrentDirectory();
  bool checkifdirExists(std::string&);
  bool createDir(std::string&);
private:
  int _argc;
  char** _argv;
  std::vector<std::string> filesToTest;

};

#endif