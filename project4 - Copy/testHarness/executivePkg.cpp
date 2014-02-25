///////////////////////////////////////////////////////////////////////
// executive.Pkg.cpp   : This is top executive package.              //
// version             : 1                                           //
// Language            : Visual C++, Visual Studio 2010, SP1         //
// platform            : Sony Vio, Windows 7, Home Premium, SP1      //
// Application         : Project 3 Spring 2012                       //
// Author              : Dhaval Malaviya, Syracuse University        //
// Contact             : dmmalavi@syr.edu                            //
///////////////////////////////////////////////////////////////////////


#include <vector>
#include <string>

#include "testHarness.h"
#include "display.h"
#include "fileMgr.h"

void main(int argc, char *argv[])
{
  // Error checking. 
  if(argc < 2) // 2 because, first argument will be exe, second argument should be path where dlls are located 
  {
    std::cout << "\n************************************************\nINPUT ERROR: Wrong Inputs.\nCorrect way of input <>.exe <PATH for dll>\n************************************************\n";
    return;
  }
  //std::string path = "../configXML/";
  std::string path = argv[1];
  path.append("/"); // To make sure path is followed by / else it will create error
  fileMgr fm; 
  if(fm.checkifdirExists(path) == false)
    { std::cout << "\n\n************** NO SUCH DIRECTORY EXISTS *************\n\n"; return;}
  testHarness th;  // Create object instance of the testHarness
  if(th.readConfigFileGenStr(path) == false)   // Check if the config path provided has xml file
  {
    return;
  }
  std::vector<std::string> testName;   // variable to store test name
  std::vector<std::vector<std::string>> results, dllsTested, childMsg;  // variables to store results, dllsTested and log path
  try{
  th.insertStrInBlockQ();   // Insert the xml string in the Blocking Q or read Q
  th.createnRunRdThrd();    // Create and run the read thread which in turn will create the child thread which will spawn child process
  th.extractXMLMsg();       // Extract the details from the xml message forwarded by child process through child thread
  testName = th.getTestNames();   // get the test names present in the result xml string
  results = th.getResults(); // get the result present in the result message xml string
  dllsTested = th.getdllsTested(); // get the dlls tested present in the result message xml string
  childMsg = th.getchildMsg();  // get all other messages present in result message xml string
  }
  catch(std::exception ex){ std::cout << ex.what();};
  display disp; // instance of the display object
  disp.displayResult(testName,dllsTested,results,childMsg); // display
}
