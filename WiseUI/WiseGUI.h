#pragma once
#include "Global.h"
#include "logic.h"
#include "Storage.h"
#include "Parser.h"
#include "Executor.h"
#include "ExecuteAdd.h"
#include "ExecuteDelete.h"
#include "ExecuteEdit.h"
#include "ExecuteSearch.h"
#include "ExecuteDisplay.h"
#include "ExecuteDropDown.h"
#include "ExecuteDropDown.h"
#include "ExecuteHelp.h"
#include "ExtDataBase.h"
#include "ExecuteDirectory.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <time.h>
#include <cassert>
#include "AutomatedTesting.h"
#include <msclr\marshal_cppstd.h>
#include "CurrentDate.h"

AutomatedTesting* autoTest = new AutomatedTesting;
vector<string> testCases;
string test = "";

string fileDirectory;  // Need to be modified later, it's better not put it as a global variable.

CurrentDate todayDate;
string date = "Today is " + todayDate.getCurrentDate() + ".\r\n";


namespace WiseUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WiseGUI
	/// </summary>
	public ref class WiseGUI : public System::Windows::Forms::Form
	{
	public:
		WiseGUI(void)
		{
			logic = new Logic;

			InitializeComponent();
			String^ dateDisplayed = gcnew String(date.c_str());
			dateBox->Text = dateDisplayed;

			bool edited = false;
			bool successful = false;
			string temp = logic->handleInput("displaydropdown Display All Tasks", edited, successful);
			String^ tasksToBeDisplayed = gcnew String(temp.c_str());
			displayBox->Text = tasksToBeDisplayed;

/*
			testCases = autoTest->getTestCases();
			for (int i = 0; i < testCases.size(); i++){
				test = testCases[i]+"\r\n";
				String^ testMStr = gcnew String(test.c_str());
				CmdLineBox->Text = testMStr;
				test = "";
			}
*/
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WiseGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  CmdLineBox;
	protected:



	protected: Logic* logic;
	private: System::Windows::Forms::TextBox^  displayBox;
	protected:















	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  dateBox;


	private: System::Windows::Forms::TextBox^  displayBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox;










			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WiseGUI::typeid));
				 this->CmdLineBox = (gcnew System::Windows::Forms::TextBox());
				 this->displayBox = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->dateBox = (gcnew System::Windows::Forms::TextBox());
				 this->displayBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // CmdLineBox
				 // 
				 this->CmdLineBox->Location = System::Drawing::Point(117, 416);
				 this->CmdLineBox->Multiline = true;
				 this->CmdLineBox->Name = L"CmdLineBox";
				 this->CmdLineBox->Size = System::Drawing::Size(325, 29);
				 this->CmdLineBox->TabIndex = 0;
				 this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
				 // 
				 // displayBox
				 // 
				 this->displayBox->BackColor = System::Drawing::SystemColors::Control;
				 this->displayBox->Location = System::Drawing::Point(12, 47);
				 this->displayBox->Multiline = true;
				 this->displayBox->Name = L"displayBox";
				 this->displayBox->ReadOnly = true;
				 this->displayBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->displayBox->Size = System::Drawing::Size(430, 224);
				 this->displayBox->TabIndex = 7;
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->label3->Location = System::Drawing::Point(8, 416);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(109, 22);
				 this->label3->TabIndex = 14;
				 this->label3->Text = L"Command://";
				 // 
				 // dateBox
				 // 
				 this->dateBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dateBox->Location = System::Drawing::Point(12, 12);
				 this->dateBox->Name = L"dateBox";
				 this->dateBox->ReadOnly = true;
				 this->dateBox->Size = System::Drawing::Size(430, 29);
				 this->dateBox->TabIndex = 15;
				 this->dateBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 // 
				 // displayBox2
				 // 
				 this->displayBox2->Location = System::Drawing::Point(12, 277);
				 this->displayBox2->Multiline = true;
				 this->displayBox2->Name = L"displayBox2";
				 this->displayBox2->ReadOnly = true;
				 this->displayBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->displayBox2->Size = System::Drawing::Size(430, 124);
				 this->displayBox2->TabIndex = 19;
				 // 
				 // pictureBox
				 // 
				 this->pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox.Image")));
				 this->pictureBox->Location = System::Drawing::Point(12, 451);
				 this->pictureBox->Name = L"pictureBox";
				 this->pictureBox->Size = System::Drawing::Size(437, 65);
				 this->pictureBox->TabIndex = 20;
				 this->pictureBox->TabStop = false;
				 // 
				 // WiseGUI
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(454, 518);
				 this->Controls->Add(this->pictureBox);
				 this->Controls->Add(this->displayBox2);
				 this->Controls->Add(this->dateBox);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->displayBox);
				 this->Controls->Add(this->CmdLineBox);
				 this->MaximizeBox = false;
				 this->Name = L"WiseGUI";
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Text = L"WiseGUI";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
	private: System::Void CmdLineBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 String^ newCmd = CmdLineBox->Text;
				 int size = newCmd->Length;
				 if (size == 0){
				 }
				 else{
					 char lastElement = newCmd[size - 1];
					 if (lastElement == '\n'){
						 Enter_Click(sender, e);
						 CmdLineBox->Clear();
					 }
				 }
	}
	private: System::Void Enter_Click(System::Object^  sender, System::EventArgs^  e) {
				 bool edited = false;
				 bool successful = false;

				 if (CmdLineBox->Text == "\r\n"){
					 MessageBox::Show("Wrong Input, re-enter:");
				 }
				 else{
					 string input = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);
					 string result = logic->handleInput(input, edited, successful);
					 String^ feedback = gcnew String(result.c_str());

					 if (!successful){
						 displayBox2->Text = feedback;
					 }
					 else{
						 displayBox->Text = feedback;
						 displayBox2->Text = "The command is carried out successfully.";
					 }
				 }
				 /*
				 if (edited){
					 string temp = logic->handleInput("displaydropdown Display All Tasks", edited, successful);
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				
		*/
				 return;
	}

};
}