#ifndef HELPER_CLASS
#define HELPER_CLASS


#include <windows.h>
#include <iostream>
#include <vector>

//#include "BlockingQueue\BlockingQueue.h"
#include "XmlReader.h"
using namespace std;

namespace helperClasses {
class helperClass
{
public:
  helperClass();
  std::vector<std::string> getdllPath(std::string&);    // Function to determine the dlls and their respective paths.
  
private:
  //std::string testName;
  std::vector<std::string> dllToRunTest;
 
};

}
#endif

