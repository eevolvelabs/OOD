// This is help class implementation file
// it has methods such as
// a) store the files

#include "thHelperClass.h"
#include "fileMgr.h"
#include "../Base64Encoding/Base64.h"
#include <fstream>
#include <vector>
#include <string>

#include "testHarness.h"
#include "display.h"
#include "fileMgr.h"

bool thHelperClass::storeFiles(std::string& fileWpath)
{
  try{
    int pos = fileWpath.find_first_of("$");
    std::string filename = fileWpath.substr(0,pos);
    std::string file = fileWpath.substr(pos+1,fileWpath.length());
    // Insert the check if working directory is there or not, if not there then create one.
    fileMgr fm; std::string path = "../thWorkDir/"; 
    if(!fm.checkifdirExists(path))
    { //create the working directory
      fm.createDir(path); }
    path.append(filename);
    Base64::decodeToFile(path,file);                      // make the file ant given path
    std::cout<<"\n File ::"<< filename <<" Successfully  Received At client\n And Store to  Folder ../thWorkDir/ \n";
   }
  catch(std::exception ex)
  {	std::cout << "\n  " << ex.what() << "\n\n"; return false;}
  return true;
}


std::string thHelperClass::executeTest()
{
  testHarness th;  // Create object instance of the testHarness
  std::string path = "../thWorkDir/";
  std::string outputStr;
  if(th.readConfigFileGenStr(path) == false)   // Check if the config path provided has xml file
  {
    outputStr = "ERROR: NO XML IN WORK DIRECTORY: ../thWorkDir/";
    return outputStr;
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
  outputStr = disp.displayResult(testName,dllsTested,results,childMsg); // display
  // Call function which form the xml to be displayed at he client end.

  return outputStr;
}