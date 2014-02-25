/////////////////////////////////////////////////////////////////////////////
//  display.cpp          : Implementation of class display                 //
//  Version              : 1.0                                             //
//  Language             : Visual C++, Visual Studio 2010, SP1             //
//  Platform             : Sony VIO, Win 7 Home Premium, SP1               //
//  Application          : Project 3, 2012                                 //
//  Author               : Dhaval Malaviya, Syracuse University            //
//  Contact              : dmmalavi@syr.edu                                //
/////////////////////////////////////////////////////////////////////////////


#include "display.h"

// Function to display the result on the console
std::string display::displayResult(std::vector<std::string>& testName,std::vector<std::vector<std::string>>& dlls,std::vector<std::vector<std::string>>& results,std::vector<std::vector<std::string>>& childMsg)
{
  std::string outputStr = "\n\n************************DISPLAY RESULT**********************\n"; // output string
  for(int i = 0; i < (int)testName.size(); ++i)  // Display for each test name
  {
    outputStr = outputStr + "\n\n******************************************\nTest Name :" + testName.at(i) + "\n******************************************\n";
    for(int j = 0; j < (int) dlls.at(i).size(); ++j) // Display for each dll for each test name
    {
      outputStr = outputStr + "\n----------------\ndll Tested :" + dlls.at(i).at(j) + "\n----------------\n";
      outputStr = outputStr + "\n----------------\nTest Result :" + results.at(i).at(j) + "\n----------------\n";
      outputStr = outputStr + "\n----------------\nDetailed Log are at location :" + childMsg.at(i).at(j) + "\n----------------\n";
    }
  }
  std::cout << outputStr; // Output the string on console
  return outputStr;
}


//////////////////////////TEST STUB/////////////////////////////////

#ifdef TEST_DISPLAY

void main()

{
  std::vector<std::string> testname;
  testname.push_back("dummy1");
  testname.push_back("dummy2");
  testname.push_back("dummy3");

  std::vector<std::vector<std::string>> dllsTested;
  std::vector<std::string> temp;
  temp.push_back("d1.dll");
  temp.push_back("d2.dll");
  dllsTested.push_back(temp);
  temp.clear();
  temp.push_back("d3.dll");
  temp.push_back("d4.dll");
  temp.push_back("d5.dll");
  temp.push_back("d6.dll");
  dllsTested.push_back(temp);
  temp.clear();
  std::vector<std::vector<std::string>> results;
  temp.push_back("passed");
  temp.push_back("failed");
  results.push_back(temp);
  temp.clear();
  temp.push_back("passed");
  temp.push_back("failed");
  temp.push_back("passed");
  temp.push_back("failed");
  results.push_back(temp);
  std::vector<std::vector<std::string>> logloc;
  temp.push_back("../../../");
  temp.push_back("../../../");
  logloc.push_back(temp);
  temp.clear();
  temp.push_back("./");
  temp.push_back("../");
  temp.push_back("../../");
  temp.push_back("../../../../");
  logloc.push_back(temp);

  display disp;
  disp.displayResult(testname,dllsTested,results,logloc);
}

#endif