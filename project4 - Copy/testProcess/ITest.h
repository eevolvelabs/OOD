#pragma once
///////////////////////////////////////////////////////////////////////
//  ITest.h          : Interface for the Test Wizard                 //  
//  Version          : 1.0                                           //
//  Language         : Visual C++, Visual Studio 2010, SP1           //
//  Platform         : Sony VIO, Win 7 Home Premium, SP1             //
//  Application      : Project 1, 2012                               //
//  Author           : Dhaval Malaviya, Syracuse University          //
//  Contact          : dmmalavi@syr.edu                              //
///////////////////////////////////////////////////////////////////////
/*
    class ITest:
    --------------------------------
    It provides the interface for 
    test wizard.

    Public Interface:
    -----------------
    static ITest* createTest();
    
    virtual bool test()=0;
                                       
    
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//                                                           //
//                                                           //
//  Building with Visual C++ , 2010, from command line:      //
//    cl -EHsc -                                             //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.0 : 1 FEB 2012
      - first release
*/

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

class TEST_API ITest
{
public:
  virtual ~ITest(void) {}
  static ITest* createTest();
  virtual bool test()=0;
};

