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
#include <sstream>

AutomatedTesting* autoTest = new AutomatedTesting;
vector<string> testCases;
string test = "";

string fileDirectory;  // Need to be modified later, it's better not put it as a global variable.

Date attainDate;
string date = attainDate.getDay() + " " + attainDate.getTodayDate() + "\r\n";



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
				 this->dateBox = (gcnew System::Windows::Forms::TextBox());
				 this->displayBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // CmdLineBox
				 // 
				 this->CmdLineBox->Location = System::Drawing::Point(12, 347);
				 this->CmdLineBox->Multiline = true;
				 this->CmdLineBox->Name = L"CmdLineBox";
				 this->CmdLineBox->Size = System::Drawing::Size(435, 19);
				 this->CmdLineBox->TabIndex = 0;
				 this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
				 // 
				 // displayBox
				 // 
				 this->displayBox->Location = System::Drawing::Point(12, 47);
				 this->displayBox->Multiline = true;
				 this->displayBox->Name = L"displayBox";
				 this->displayBox->ReadOnly = true;
				 this->displayBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->displayBox->Size = System::Drawing::Size(435, 224);
				 this->displayBox->TabIndex = 7;
				 // 
				 // dateBox
				 // 
				 this->dateBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dateBox->Location = System::Drawing::Point(12, 12);
				 this->dateBox->Name = L"dateBox";
				 this->dateBox->ReadOnly = true;
				 this->dateBox->Size = System::Drawing::Size(435, 29);
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
				 this->displayBox2->Size = System::Drawing::Size(435, 65);
				 this->displayBox2->TabIndex = 19;
				 // 
				 // pictureBox
				 // 
				 this->pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox.Image")));
				 this->pictureBox->Location = System::Drawing::Point(12, 371);
				 this->pictureBox->Name = L"pictureBox";
				 this->pictureBox->Size = System::Drawing::Size(435, 61);
				 this->pictureBox->TabIndex = 20;
				 this->pictureBox->TabStop = false;
				 // 
				 // WiseGUI
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::SystemColors::Menu;
				 this->ClientSize = System::Drawing::Size(459, 437);
				 this->Controls->Add(this->pictureBox);
				 this->Controls->Add(this->displayBox2);
				 this->Controls->Add(this->dateBox);
				 this->Controls->Add(this->displayBox);
				 this->Controls->Add(this->CmdLineBox);
				 this->ForeColor = System::Drawing::SystemColors::ControlText;
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->MaximizeBox = false;
				 this->Name = L"WiseGUI";
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Text = L"WiseManger";
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
					 string input2;

					 istringstream iss(input);
					 bool isHelp = false;
					 string commandType = "";

					 if (input.size() > 0){
						 iss >> commandType;
					 }

					 if (commandType[commandType.size() - 2] == '\r' && commandType[commandType.size() - 1] == '\n'){
						 commandType = commandType.substr(0, commandType.size() - 2);
					 }

					 if (input[input.size() - 2] == '\r' && input[input.size() - 1] == '\n'){
						 input2 = input.substr(0, input.size() - 2);
					 }

					 for (size_t i = 0; i < commandType.size(); i++){
						 commandType[i] = tolower(commandType[i]);
					 }

					 for (size_t i = 0; i < input2.size(); i++){
						 input2[i] = tolower(input2[i]);
					 }

					 if (commandType == "help"){
						 isHelp = true;
					 }
					 else if (commandType == "display" && input2 == "display"){
						 bool successful2 = false;
						 string temp = logic->handleInput("displaydropdown Display All Tasks", edited, successful2);
						 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
						 displayBox->Text = tasksToBeDisplayed;
						 return;
					 }

					 string result = logic->handleInput(input, edited, successful);
					 String^ feedback = gcnew String(result.c_str());

					 if (isHelp){
						 MessageBox::Show(feedback);
					 }
					 else if (!isHelp && successful){
						 displayBox->Text = feedback;
						 displayBox2->Text = "The command is carried out successfully.";
					 }
					 else if (!isHelp && !successful){
						 displayBox2->Text = feedback;
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