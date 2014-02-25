#pragma once

#include "../Base64Encoding/Base64.h"
#include "../Communicator/Comm.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include "stdafx.h"


//using namespace cliext;
//using namespace std;
namespace testHarnessClient {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::Text;
  using namespace System::Threading;
  using namespace System::IO;


  /// <summary>
  /// Summary for Form1
  /// </summary>
  public ref class Form1 : public System::Windows::Forms::Form
  {
  public:
    Form1(void)
    {
      InitializeComponent();
      connected = false;
      int recPort = 8010;  // Port to receive from peer connection
      recvPtr = new SocketCommunicator::Receiver(recPort);
      pRcvrThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &Form1::run)); 
      pRcvrThread->IsBackground = true;
      pRcvrThread->Start();
      //
      //TODO: Add the constructor code here
      //
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }

  private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
  private: System::Windows::Forms::ListBox^  listBox1;
  private: System::Windows::Forms::Button^  button2;
  private: System::Windows::Forms::StatusStrip^  statusStrip1;
  private: bool xmlFound;
  private: bool dllFound;
  private: bool connected;
  private: array<String^>^ dlls;
  private: array<String^>^ Files;

  private: int port;
  private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
  private: System::Windows::Forms::Button^  button3;
  private: System::Windows::Forms::ListBox^  listBox2;

  private: System::Threading::Thread^ pRcvrThread;
  private: SocketCommunicator::Sender* sendPtr;
  private: SocketCommunicator::Receiver* recvPtr;
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::TextBox^  textBox1;


  protected: 

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
      this->listBox1 = (gcnew System::Windows::Forms::ListBox());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
      this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
      this->button3 = (gcnew System::Windows::Forms::Button());
      this->listBox2 = (gcnew System::Windows::Forms::ListBox());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->statusStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // listBox1
      // 
      this->listBox1->FormattingEnabled = true;
      this->listBox1->Location = System::Drawing::Point(35, 30);
      this->listBox1->Name = L"listBox1";
      this->listBox1->Size = System::Drawing::Size(292, 108);
      this->listBox1->TabIndex = 1;
      this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(369, 30);
      this->button2->Name = L"button2";
      this->button2->Size = System::Drawing::Size(246, 23);
      this->button2->TabIndex = 2;
      this->button2->Text = L"Step 1: Browse for test Config folder";
      this->button2->UseVisualStyleBackColor = true;
      this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
      // 
      // statusStrip1
      // 
      this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
      this->statusStrip1->Location = System::Drawing::Point(0, 468);
      this->statusStrip1->Name = L"statusStrip1";
      this->statusStrip1->Size = System::Drawing::Size(639, 22);
      this->statusStrip1->TabIndex = 3;
      this->statusStrip1->Text = L"Status";
      this->statusStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::statusStrip1_ItemClicked);
      // 
      // toolStripStatusLabel1
      // 
      this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
      this->toolStripStatusLabel1->Size = System::Drawing::Size(285, 17);
      this->toolStripStatusLabel1->Text = L"Browse To Select Folder Containing Test Config XML";
      // 
      // button3
      // 
      this->button3->Enabled = false;
      this->button3->Location = System::Drawing::Point(369, 160);
      this->button3->Name = L"button3";
      this->button3->Size = System::Drawing::Size(246, 28);
      this->button3->TabIndex = 4;
      this->button3->Text = L"Step 2: Browse for DLL files folder";
      this->button3->UseVisualStyleBackColor = true;
      this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
      // 
      // listBox2
      // 
      this->listBox2->FormattingEnabled = true;
      this->listBox2->Location = System::Drawing::Point(35, 160);
      this->listBox2->Name = L"listBox2";
      this->listBox2->Size = System::Drawing::Size(292, 95);
      this->listBox2->TabIndex = 5;
      // 
      // button1
      // 
      this->button1->Enabled = false;
      this->button1->Location = System::Drawing::Point(369, 283);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(246, 23);
      this->button1->TabIndex = 6;
      this->button1->Text = L"Step 3: Connect and Send Files To Test Harness";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
      // 
      // textBox1
      // 
      this->textBox1->Location = System::Drawing::Point(12, 285);
      this->textBox1->Multiline = true;
      this->textBox1->Name = L"textBox1";
      this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
      this->textBox1->Size = System::Drawing::Size(332, 101);
      this->textBox1->TabIndex = 7;
      this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_2);
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(639, 490);
      this->Controls->Add(this->textBox1);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->listBox2);
      this->Controls->Add(this->button3);
      this->Controls->Add(this->statusStrip1);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->listBox1);
      this->Name = L"Form1";
      this->Text = L"Project 4: Remote Test Harness";
      this->statusStrip1->ResumeLayout(false);
      this->statusStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
    /////////////////////////////////////////////////////////////////////////////////////////
    //----< helper string conversion functions >-----------------------
    /////////////////////////////////////////////////////////////////////////////////////////
    std::string convert(System::String^ str)  // Helper function which converts System type string into std string
    {
      std::string temp;
      for(int i=0; i<str->Length; ++i)
        temp += (char)str[i];
      return temp;
    }

    // Helper Function which will convert the std string into the System string
    System::String^ convert(std::string& str)
    {
      StringBuilder^ temp = gcnew StringBuilder("");
      for(size_t i=0; i<str.size(); ++i)
        temp->Append((wchar_t)str[i]);
      return temp->ToString();
    }

    // Helper function which will send out the data of particular type over the socket
    void sendOnSocket(String^ fileToBeSent,std::string type)
    {
      String^ _filename = (String^)fileToBeSent;   // Getting the file name along with the path into the String^ type variable
      std::string filename_ = convert(_filename);  // Convert String^ into std string
      SocketCommunicator::Message msg;             // Creating instance of msg
      if(type.compare("file") != 0) 
      { msg.getMsgType() = SocketCommunicator::Message::text; }   //Send a xml in form of text to server
      else 
      { msg.getMsgType() = SocketCommunicator::Message::file; }             // Send file
      std::string filestr =Base64::encodeFromFile(filename_);
      int pos = filename_.find_last_of("\\");
      std::string file_name = filename_.substr(pos+1,filename_.length()-1);
      file_name.append("$");
      file_name.append(filestr);
      msg.body()=file_name;
      sendPtr->PostMsg(msg);
    }


    // Receiver thread implementation.
    /////////////////////////////////////////////////////////////////////////////////////////
    //----< thread processing function >-------------------------------
	/////////////////////////////////////////////////////////////////////////////////////////
    void run()
    {
      try
      {
        SocketCommunicator::Message msg, vmsg;
        do
        {
          msg = recvPtr->GetMsg();
          String^ temp = convert(msg.body());
          if(msg.getMsgType()==0)											// Text xml which is informal information from the test harness
          {
            
            // this is example, but need to invoke function which will display the data on the GUI...this->Invoke(_user_valid,gcnew array<System::Object^,1>{});
          }

          if(msg.getMsgType()==1)												//Files
          {
            //this is example, but need to put code which will store the received data in the form of files...this->Invoke(display, gcnew array<System::Object^,1> {temp} );
          }
          
        } while(msg.body() != "quit");
      }
      catch(std::exception& ex)
      {
        System::Windows::Forms::MessageBox::Show(convert(std::string(ex.what())));
      }
    }
    ///////////////////////////////////////////
    /*private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
    }*/
  private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
           }
  private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)   // Browse button action
           {
             toolStripStatusLabel1->Text = "BROWSE TO SELECT FOLDER CONTAINING TEST CONFIG XML";
             this->button3->Enabled = false;

             folderBrowserDialog1 = gcnew FolderBrowserDialog();
             folderBrowserDialog1->ShowNewFolderButton = false;
             folderBrowserDialog1->SelectedPath = Directory::GetCurrentDirectory();
             System::Windows::Forms::DialogResult result;
             result = folderBrowserDialog1->ShowDialog();
             if(result == System::Windows::Forms::DialogResult::OK)
             {
               this->button3->Enabled = true;
               Directory::SetCurrentDirectory(folderBrowserDialog1->SelectedPath);
               //textBox1->Text = Directory::GetCurrentDirectory();
               listBox1->Items->Clear();
               ///////////////
               // get a list of files in the folder
               Files = Directory::GetFiles(folderBrowserDialog1->SelectedPath);
               // Check if there is xml files in the folder.
               xmlFound = false;
               for(int i=0; i<Files->Length; ++i)
               {
                 String^ pExt = Path::GetExtension(Files[i]);
                 String^ fileName = Path::GetFileName(Files[i]);
                 if(pExt->IndexOf(L".xml") != -1)
                 {
                   toolStripStatusLabel1->Text = "HINT: Press Step 2 Button to send required dll files to test harness";
                   listBox1->Items->Add(fileName);
                   //std::ifstream inputXMLString (convert(Files[i]));

                   //// Converting the content of the xml file read into 
                   //// string
                   //std::string content( (std::istreambuf_iterator<char>(inputXMLString) ),
                   //   (std::istreambuf_iterator<char>()    ) );
                   //std::vector<std::string> testvector = phc->getdllPath(content);
                   xmlFound = true;
                   this->button1->Enabled = true;
                 }
               }
               if(xmlFound == false)
               {

                 this->button3->Enabled = false;
                 toolStripStatusLabel1->Text = "ERROR: NO TEST CONFIG XML AT THE SELECTED PATH";
               }


               //////////////
             }
           }
  private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
           }
  private: System::Void statusStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
           }
  private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
           {

           }
  private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
           }
  private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
           {
             toolStripStatusLabel1->Text = "BROWSE TO SELECT FOLDER CONTAINING TEST DLLS";
             //this->button3->Enabled = false;
             folderBrowserDialog1 = gcnew FolderBrowserDialog();
             folderBrowserDialog1->ShowNewFolderButton = false;
             folderBrowserDialog1->SelectedPath = Directory::GetCurrentDirectory();
             System::Windows::Forms::DialogResult result;
             result = folderBrowserDialog1->ShowDialog();
             if(result == System::Windows::Forms::DialogResult::OK)
             {
               //this->button3->Enabled = true;
               Directory::SetCurrentDirectory(folderBrowserDialog1->SelectedPath);
               //textBox1->Text = Directory::GetCurrentDirectory();
               listBox2->Items->Clear();
               ///////////////
               // get a list of files in the folder
               dlls = Directory::GetFiles(folderBrowserDialog1->SelectedPath);
               // Check if there is xml files in the folder.
               dllFound = false;
               for(int i=0; i<dlls->Length; ++i)
               {

                 String^ pExt = Path::GetExtension(dlls[i]);
                 String^ fileName = Path::GetFileName(dlls[i]);
                 if(pExt->IndexOf(L".dll") != -1)
                 {
                   toolStripStatusLabel1->Text = "TRYING TO SEND REQUIRED DLLS";
                   listBox2->Items->Add(fileName);

                   dllFound = true;
                 }
               }
               if(dllFound == false)
               {
                 //this->button3->Enabled = false;
                 toolStripStatusLabel1->Text = "ERROR: NO TEST DLL FOUND AT THE SELECTED PATH";
               }


               //////////////
             }
           }
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
           {
             this->button1->Enabled = false;
             //toolStripStatusLabel1->Text = "Trying to connect to Remote Test Harness";
             // Trying to connect to the Test Harness Server
             if(connected == false)
             {
               std::string addr = "localhost"; // = convert(textBox1->Text);
               port = 8000;      //System::Convert::ToInt32(textBox2->Text);
               try
               {
                 sendPtr = new SocketCommunicator::Sender;
                 SocketCommunicator::EndPoint ep(addr,port);
                 if(!sendPtr->connect(ep))
                 { toolStripStatusLabel1->Text = "CANNOT CONNECT TO TEST HARNESS SERVER. TRY AGAIN";
                 this->button1->Enabled = true; return;  }
                 connected = true;
                 this->button1->Enabled = false;
                 toolStripStatusLabel1->Text = "CONNECTED TO THE TEST HARNESS SERVER.";
               }
               catch(std::exception& /*ex*/)
               {
                 toolStripStatusLabel1->Text = "CANNOT CONNECT TO TEST HARNESS SERVER. TRY AGAIN"; this->button1->Enabled = true; return; }
             }
             if(connected == true)
             { // code which will send the files and xml strings to the server
               if(dllFound == true)
               {for(int i=0; i<dlls->Length; ++i) // First sending the dlls to the test harness server
               { try { std::string type = "file"; toolStripStatusLabel1->Text = "SENDING....";sendOnSocket(dlls[i],type);}
               catch(std::exception& /*ex*/)
               {	toolStripStatusLabel1->Text = "Lost Connection";	connected = false;}
               } }
               for(int i=0; i<Files->Length; ++i) // First sending the dlls to the test harness server
               { try { std::string type = "file"; toolStripStatusLabel1->Text = "SENDING....";sendOnSocket(Files[i],type);}
               catch(std::exception& /*ex*/)
               {	toolStripStatusLabel1->Text = "Lost Connection";	connected = false;}
               }
               // Now send signal to start the test

             }
             SocketCommunicator::Message startTestMsg;
             startTestMsg.getMsgType() = SocketCommunicator::Message::text;
             startTestMsg.body()= "strtTest";
             sendPtr->PostMsg(startTestMsg);
             toolStripStatusLabel1->Text = "Required Data Sent Successfully. Waiting For Results...";
           }



  private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
           }
private: System::Void textBox1_TextChanged_2(System::Object^  sender, System::EventArgs^  e) {
         }
};
}


