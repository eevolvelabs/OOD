/////////////////////////////////////////////////////////////////////////////
//  testProcess.cpp      : It is main function of the child process        //
//                         It will execute the test using helper functions //
//                         provided by testProcessClass package            //
//  Version              : 1.0                                             //
//  Language             : Visual C++, Visual Studio 2010, SP1             //
//  Platform             : Sony VIO, Win 7 Home Premium, SP1               //
//  Application          : Project 3, 2012                                 //
//  Author               : Dhaval Malaviya, Syracuse University            //
//  Contact              : dmmalavi@syr.edu                                //
/////////////////////////////////////////////////////////////////////////////



#include <sstream>
#include <stdlib.h>
#include "testProcessClass.h"

using namespace std;

int main(int argc, char *argv[]) {
  //---Delete this line//// Loading the dlls explicitly /* char* dllPath = "../dlls/TestTokenQuotedString.dll"  testProcess tp;  tp.ldnrundlltest(dllPath);*/
  testProcessClass tp; // Create the testProcess instance
  fileMgr fm;
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);  // get WriteHandle to pipe, passed as STD_OUTPUT_HANDLE
  HANDLE console = CreateFile("CONOUT$",GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0); // get Handle to screen buffer so we can write a few visible lines
  DWORD dwWritten;  // bytes written
  // From here write the different string on the console.
  std::string dispStr = "\n---------------------------------------------------------------\nThis is Child Process which will run the test function \nof the dll passed to this process \n---------------------------------------------------------------\n";
  tp.displayStr(console,dwWritten,dispStr);
  dispStr = "\n\nDLLs Passed to this child process are:\n\n";
  for(int i=0; i<argc; i++)
  { dispStr = dispStr + "dll = " + argv[i] + "\n"; }
  tp.displayStr(console,dwWritten,dispStr);
  dispStr = "\n\n--------------------------------------------------------------\n Running Tests: \n--------------------------------------------------------------\n";
  std::vector<std::string> results,arguments; // result vector which will store the result of corresponding dlls
  for(int i=0; i<argc; i++)  // For loop to run test of each of the dlls passed to this child process
  { arguments.push_back(argv[i]);
    dispStr = dispStr + "\nTest for dll: " + argv[i]; 
    std::string resultTemp = tp.ldnrundlltest(argv[i]); // Temp storage of the result string
    results.push_back(resultTemp);
    dispStr = dispStr + "\n----------------------------------\nResult of running test\n----------------------------------\n" + resultTemp + "\n\n";
  }
  tp.displayStr(console,dwWritten,dispStr);
  std::string displaypath = "\n\n----------------------------------\nFor detailed logs look at:\n----------------------------------\n ";
  std::vector<std::string> path;  // path vector to store the path where the log files are stored.
  for (int i = 0; i < argc; i++)
  { displaypath = displaypath + tp.displayLogPath(argv[i]) + "\n";
    if(results.at(i).find("ERROR:") != -1)
     {path.push_back("LOG NOT GENERATED. CHECK RESULT");}
    else{     path.push_back(tp.displayLogPath(argv[i]));}
  }std::string workDir = "../thWorkDir/"; tp.moveFilesToWorkDir(path,workDir);
  tp.displayStr(console,dwWritten,displaypath);
  std::string xml = tp.createXML(arguments,results,path);  // Create the XML file for the result.
  //tp.displayStr(console,dwWritten,xml);  // Console display of the xml string.
  // write opening text to pipe
  WriteFile(hStdout,xml.c_str(),xml.size(),&dwWritten,NULL);
  // write closing lines to pipe
  WriteFile(hStdout,"\n",strlen("\n"),&dwWritten,NULL);
  WriteFile(hStdout,"quit",strlen("quit"),&dwWritten,NULL);
  char* closeMsg = "\n  press a key to finish: ";  // write prompt to child screen
  WriteFile(console, closeMsg, strlen(closeMsg), &dwWritten, NULL);
  ///////////////////////////////////////////////////////////////////////
  // Uncomment to keep window from closing so user can look at contents. Parent needs to specify CREAT_NEW_CONSOLE when you uncomment.
  // Parent needs to specify CREATE_NO_WINDOW when you comment. Test should not call getche().
  int ch = _getche();
  CloseHandle(hStdout);
  return 0;
}