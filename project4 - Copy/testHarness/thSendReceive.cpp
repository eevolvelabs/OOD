
// This is main function of the test harness and here:
// a) Receiver socket is created on port 8000
// b) Sender socket is created on port 8001
// c) Based on type of message received from the testHarnessClient
//    i) if message is dll files then, those files are stored in the working directory
//    ii) if message is xml then, it is quequed in the message Blocking Q from where, test harness will read it and
//        shall create child thread there by creating child process to execute the test on configuration present in 
//        xml passed.
// d) It also sends back the result xml and result log files.
#include <iostream>
#include <vector>
#include "../Communicator/Comm.h"
#include "../Base64Encoding/Base64.h"
#include "../Message/Message.h"
#include "thHelperClass.h"
#include <vector>
#include <string>

//#include "testHarness.h"
//#include "display.h"
//#include "fileMgr.h"

using namespace SocketCommunicator;
void main()
{
  /////////////////////////
  std::cout << "\n  Starting ReceiverApp" <<"\n ======================\n";
	SocketCommunicator::Sender sndr;
	SocketCommunicator::Message Smsg;
	int tryCount = 0, MaxTries = 5;
  // Creating instance of helper class
  thHelperClass thH;
	std::string ip = "localhost";
	int port = 8010;   // Port on which test harness will connect to client for sending data from test harness to client
	while(++tryCount < MaxTries){
		if(sndr.connect(SocketCommunicator::EndPoint(ip,port))) break;
		Sleep(100);
		std::cout << "\n  failed attempt to connect to endpoint(" << ip.c_str() << ", " << port << ")";
	}
	try {
    SocketCommunicator::Receiver rcvr(8000);
		SocketCommunicator::Message msg, vmsg;
		std::string name;
    msg = rcvr.GetMsg();
    while(msg.body() != "strtTest")
		{
			if(msg.TypeToString().compare("text") == 0){ // Text message is received, here it will be config in form of string, later needs to change Message package to entertain "xml" type of message reception
				// Config XML received. Hence Q it 
        std::cout << "\nXML Message Received\n";
			}
			if(msg.getMsgType()==1){
			  // Received the dll files hence store those files into working directory
        
        thH.storeFiles(msg.body());

      }
		 msg = rcvr.GetMsg(); // Get the next message	
		}
    ///////////Running the testProcess thread///////////
    std::string outputStr = thH.executeTest();
    // Sending above string to the test client to display
    Smsg.getMsgType() = SocketCommunicator::Message:: text;
    Smsg.body() = outputStr;
    sndr.PostMsg(Smsg);
    ///////////////////////////////////////////////////
		std::cout << "\n\n  shutting down ReceiverApp Receiver";		
	}
	catch(std::exception& ex){
		std::cout << "\n\n  " << ex.what();
	}



  ////////////////

}