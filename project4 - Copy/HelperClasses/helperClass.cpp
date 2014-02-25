

#include "helperClass.h"

using namespace helperClasses;

helperClass::helperClass()
{
}
// Function which will return vector of the string indicating the dll files which need 
// to be tested.
std::vector<std::string> helperClass::getdllPath(std::string& xmlMsg)
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



void main()

{

}