/////////////////////////////////////////////////////////////////////////////
//  testHarness.cpp      : Implementation of class testHarness             //
//  Version              : 1.0                                             //
//  Language             : Visual C++, Visual Studio 2010, SP1             //
//  Platform             : Sony VIO, Win 7 Home Premium, SP1               //
//  Application          : Project 3, 2012                                 //
//  Author               : Dhaval Malaviya, Syracuse University            //
//  Contact              : dmmalavi@syr.edu                                //
/////////////////////////////////////////////////////////////////////////////


#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "fileMgr.h"

#include "testHarness.h"

// This function will be used to generate the string out of the 
// the XML file contents
bool testHarness::readConfigFileGenStr(std::string& path)
{
  fileMgr fm; // Creating the instance of the fileMgr to use findFiles function below
  std::vector <std::string> xmlName = fm.findFiles(path,"*.xml"); // Now Check if the XML file exists at the given path
  std::string xmlPath = path;
  client cl; // create instance of client which shall be used to read the XML and convert string
  if(xmlName.size() < 1)  // Check if there are no XML config files at the given path.
  {
    std::cout << "\nNo XML File present @ " << path << " Hence quiting\n";
    return false;
  }
  for(int i = 0 ; i < (int)xmlName.size(); ++i)
  {
    // Append the xml file name to path so as to read the file in string.
    xmlPath = xmlPath.append(xmlName.at(i).c_str());
    xmlRdString.push_back(cl.readXML(xmlPath)); // Pusing the xml config string into the xmlRdString vector.
    xmlPath = path;
  }
  return true;
 }

// Function which will insert the string into the blocking Q
void testHarness::insertStrInBlockQ()
{
  // Create the client instance which will add the string into the blocking Q
  client cl;
  std::string quit = "quit";
  // Insert the string into the Blocking Q
  for (int i = 0; i < (int) xmlRdString.size(); i++)
  {
    cl.pushMsgInQueque(xmlRdString.at(i),msgQ);
  }
  // Inserting Quit in the blocking Q marking end of the messages
  cl.pushMsgInQueque(quit,msgQ);
}

// Function to create the thread which will read the blocking Q and also will 
// generate the child thread which will spawn child process.
void testHarness::createnRunRdThrd()
{
  threadToRdQ parentTh(msgQ,resultQ);  // Create the thread to read the blocking Q
  thread th(parentTh);
  th.start();                          // Start executing the readQ thread
  th.wait();
}


// function which will shall message from the xml resulted from the 
// child thread stored in the resultQ
void testHarness::extractXMLMsg()
{
  std::string xmlString = resultQ.deQ();  // DeQ the result which is form of xml string
  while(xmlString != "quit") // if Quit reached (it is end of queue) then exist
  {
    createTestNameVector(xmlString);  // create the test name vector
    createdllTestedVector(xmlString); // create the dll tested vector of vector of string
    createResultVector(xmlString);    // create the result vector of vector of string 
    createLogLocVector(xmlString);    // create the log location vector of vector of string
    xmlString = resultQ.deQ();        // deQ the next message
  }
}

// Member function to create the vector for test names
void testHarness::createTestNameVector(std::string& xmlString)
{
   // Initializing the XmlReader object with input string as content of the xml file.
   XmlReader rdr(xmlString);
   while(rdr.next()) // While loop which will go through the xml to find test name in XML file.
   {
     // Check if the tag read from the xml is for test name
     if(rdr.tag().compare("testName") == 0)
     {
       testNames.push_back(rdr.body().c_str());
     }
   }
}

// Member function to create the vector of vector of string consists of the dlls tested.
// if there is no dlls then it will consists of the ERROR message
void testHarness::createdllTestedVector(std::string& xmlString)
{
  if(xmlString.find("ERROR:NO") != -1)
  {
    // This indicates that no dll was present in the config file
    // stroing error message in the all three parameters of the testname
    //results.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    std::vector<std::string> error;
    error.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    dlls.push_back(error);
    //childMsg.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    //return;
  }
  else // If there is no error in xml file. Mean dlls were mentioned then do below
  {
    XmlReader rdr(xmlString);
    std::vector<std::string> dllsInXML;
    while(rdr.next())
    {
      if(rdr.tag().compare("dllname") == 0)
      {
        dllsInXML.push_back(rdr.body().c_str());
      }

    }
    dlls.push_back(dllsInXML);
  }
}


// Member function to create the vector of vector of string consists of the results of the test run.
// if there is no dlls then it will consists of the ERROR message
void testHarness::createResultVector(std::string& xmlString)
{
  if(xmlString.find("ERROR:NO") != -1)
  {
    // This indicates that no dll was present in the config file
    // stroing error message in the all three parameters of the testname
    //results.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    std::vector<std::string> error;
    error.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    results.push_back(error);
    //childMsg.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    //return;
  }
  else // If there is no error in xml file. Mean dlls were mentioned then do below
  {
    XmlReader rdr(xmlString);
    std::vector<std::string> resultsInXML;
    while(rdr.next())
    {
      if(rdr.tag().compare("result") == 0)
      {
        resultsInXML.push_back(rdr.body().c_str());
      }

    }
    results.push_back(resultsInXML);
  }
}


// Member function to create the vector of vector of string consists of the path of log created for details
// if there is no dlls then it will consists of the ERROR message
void testHarness::createLogLocVector(std::string& xmlString)
{
  if(xmlString.find("ERROR:NO") != -1)
  {
    // This indicates that no dll was present in the config file
    // stroing error message in the all three parameters of the testname
    //results.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    std::vector<std::string> error;
    error.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    childMsg.push_back(error);
    //childMsg.push_back("ERROR:NO DLL PRESENT IN THE CONFIG XML");
    //return;
  }
  else // If there is no error in xml file. Mean dlls were mentioned then do below
  {
    XmlReader rdr(xmlString);
    std::vector<std::string> childMsgInXML;
    while(rdr.next())
    {
      if(rdr.tag().compare("detailLog") == 0)
      {
        childMsgInXML.push_back(rdr.body().c_str());
      }

    }
    childMsg.push_back(childMsgInXML);
  }
}


// Member function which will return the testNames
std::vector<std::string> testHarness::getTestNames()
{
  return testNames;
}

// Member Function which will return the dlls tested by the child process
std::vector<std::vector<std::string>> testHarness::getdllsTested()
{
  return dlls;
}

// Member function which will return the results of test run by child process
std::vector<std::vector<std::string>> testHarness::getResults()
{
  return results;
}

// Member function which will return the location of logs created for each test run
std::vector<std::vector<std::string>> testHarness::getchildMsg()
{
  return childMsg;
}


///////////////////////////TEST STUB/////////////////////////////

#ifdef TEST_TESTHARNESS
#include "display.h"
void main()
{
  //bool readConfigFileGenStr(std::string&);  // function which will convert the xml file content into the string and shall store into the vector
  //void insertStrInBlockQ();                 // function to enqueue the xml string
  //void createnRunRdThrd();                  // function to create the read thread and there by which will create another child thread which will spawn the child process
  std::string xmlString = "<testName>Demo</testName><?xml version=\"1.0\"?><display><test><dllname>..\\dlls\\SemiExpTest2.dll</dllname><result>PASSED</result><detailLog>C:\\Users\\dhavalmalaviya\\Desktop\\OOD\\project3\\project3\\project3\\SemiExpTest2TL.log</detailLog></test><test><dllname>..\\dlls\\TestTokenQuotedString.dll</dllname><result>PASSED</result><detailLog>C:\\Users\\dhavalmalaviya\\Desktop\\OOD\\project3\\project3\\project3\\TestTokenQuotedStringTL.log</detailLog></test><test><dllname>..\\dlls\\TestTokenizerWithComments.dll</dllname><result>PASSED</result><detailLog>C:\\Users\\dhavalmalaviya\\Desktop\\OOD\\project3\\project3\\project3\\TestTokenizerWithCommentsTL.log</detailLog></test><test><dllname>..\\dlls\\SemiExpTest1.dll</dllname><result>PASSED</result><detailLog>C:\\Users\\dhavalmalaviya\\Desktop\\OOD\\project3\\project3\\project3\\SemiExpTest1TL.log</detailLog></test></display>";

  //void extractXMLMsg();                     // function to extract the xml string details stored in to the resultQ by the child thread
  testHarness th;
  th.createTestNameVector(xmlString);  // function to create the vector of all test names
  th.createdllTestedVector(xmlString); // function to create the vector of vector of string of the dlls tested
  th.createResultVector(xmlString);    // function to create the vector of vector of string of the results forwarded by child thread
  th.createLogLocVector(xmlString);    // function to create the vector of vector of string of the log location is generated
  std::vector<std::string> testNames = th.getTestNames();  // function which return all test names in form of vector
  std::vector<std::vector<std::string>> results = th.getResults(); // function which return the results of each test case run
  std::vector<std::vector<std::string>> dllTested = th.getdllsTested(); // function which return the dlls tested 
  std::vector<std::vector<std::string>> childMsg = th.getchildMsg(); // function which will return the child msg which will consists of the path and name of log file stored

  display disp;
  disp.displayResult(testNames,dllTested,results,childMsg);
   

}

#endif