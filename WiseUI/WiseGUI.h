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
#include <cassert>
#include <msclr\marshal_cppstd.h>


string fileDirectory;  // Need to be modified later, it's better not put it as a global variable.

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
			String^ feedback = gcnew String(MESSAGE_WELCOME.c_str());
			feedbackBox->Text = feedback;

			string temp = logic->getCurrentDirectory();
			String^ directory = gcnew String(temp.c_str());
			SavingDirectoryBox->Text = directory;

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

	private: System::Windows::Forms::Button^  Enter;

	protected: Logic* logic;


	private: System::Windows::Forms::ComboBox^  dropdownBox;
	private: System::Windows::Forms::TextBox^  feedbackBox;


	private: System::Windows::Forms::Button^  Exit;

	private: System::Windows::Forms::TextBox^  displayBox;

	private: System::Windows::Forms::TextBox^  Command;

	private: System::Windows::Forms::TextBox^  SavingDirectoryBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;





			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->CmdLineBox = (gcnew System::Windows::Forms::TextBox());
				 this->Enter = (gcnew System::Windows::Forms::Button());
				 this->dropdownBox = (gcnew System::Windows::Forms::ComboBox());
				 this->feedbackBox = (gcnew System::Windows::Forms::TextBox());
				 this->Exit = (gcnew System::Windows::Forms::Button());
				 this->displayBox = (gcnew System::Windows::Forms::TextBox());
				 this->Command = (gcnew System::Windows::Forms::TextBox());
				 this->SavingDirectoryBox = (gcnew System::Windows::Forms::TextBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->SuspendLayout();
				 // 
				 // CmdLineBox
				 // 
				 this->CmdLineBox->Location = System::Drawing::Point(81, 418);
				 this->CmdLineBox->Multiline = true;
				 this->CmdLineBox->Name = L"CmdLineBox";
				 this->CmdLineBox->Size = System::Drawing::Size(696, 21);
				 this->CmdLineBox->TabIndex = 0;
				 this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
				 // 
				 // Enter
				 // 
				 this->Enter->Location = System::Drawing::Point(783, 419);
				 this->Enter->Name = L"Enter";
				 this->Enter->Size = System::Drawing::Size(75, 21);
				 this->Enter->TabIndex = 2;
				 this->Enter->Text = L"Enter";
				 this->Enter->UseVisualStyleBackColor = true;
				 this->Enter->Click += gcnew System::EventHandler(this, &WiseGUI::Enter_Click);
				 // 
				 // dropdownBox
				 // 
				 this->dropdownBox->FormattingEnabled = true;
				 this->dropdownBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
					 L"Display All Tasks", L"Tasks to be done today",
						 L"Sort by Date", L"Sort by Priority", L"Display Unbounded Tasks"
				 });
				 this->dropdownBox->Location = System::Drawing::Point(12, 11);
				 this->dropdownBox->Name = L"dropdownBox";
				 this->dropdownBox->Size = System::Drawing::Size(376, 20);
				 this->dropdownBox->TabIndex = 3;
				 this->dropdownBox->SelectedIndexChanged += gcnew System::EventHandler(this, &WiseGUI::dropdownBox_SelectedIndexChanged);
				 // 
				 // feedbackBox
				 // 
				 this->feedbackBox->Location = System::Drawing::Point(408, 38);
				 this->feedbackBox->Multiline = true;
				 this->feedbackBox->Name = L"feedbackBox";
				 this->feedbackBox->ReadOnly = true;
				 this->feedbackBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->feedbackBox->Size = System::Drawing::Size(531, 299);
				 this->feedbackBox->TabIndex = 4;
				 this->feedbackBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::feedbackBox_TextChanged);
				 // 
				 // Exit
				 // 
				 this->Exit->AllowDrop = true;
				 this->Exit->Location = System::Drawing::Point(864, 419);
				 this->Exit->Name = L"Exit";
				 this->Exit->Size = System::Drawing::Size(75, 21);
				 this->Exit->TabIndex = 6;
				 this->Exit->Text = L"E&xit";
				 this->Exit->UseVisualStyleBackColor = true;
				 this->Exit->Click += gcnew System::EventHandler(this, &WiseGUI::Exit_Click);
				 // 
				 // displayBox
				 // 
				 this->displayBox->Location = System::Drawing::Point(12, 38);
				 this->displayBox->Multiline = true;
				 this->displayBox->Name = L"displayBox";
				 this->displayBox->ReadOnly = true;
				 this->displayBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->displayBox->Size = System::Drawing::Size(376, 374);
				 this->displayBox->TabIndex = 7;
				 // 
				 // Command
				 // 
				 this->Command->Location = System::Drawing::Point(12, 418);
				 this->Command->Name = L"Command";
				 this->Command->Size = System::Drawing::Size(72, 21);
				 this->Command->TabIndex = 9;
				 this->Command->Text = L"Command: //";
				 // 
				 // SavingDirectoryBox
				 // 
				 this->SavingDirectoryBox->Location = System::Drawing::Point(408, 370);
				 this->SavingDirectoryBox->Multiline = true;
				 this->SavingDirectoryBox->Name = L"SavingDirectoryBox";
				 this->SavingDirectoryBox->ReadOnly = true;
				 this->SavingDirectoryBox->Size = System::Drawing::Size(531, 42);
				 this->SavingDirectoryBox->TabIndex = 11;
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(406, 355);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(149, 12);
				 this->label1->TabIndex = 12;
				 this->label1->Text = L"Current Saving Directory";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(406, 19);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(77, 12);
				 this->label2->TabIndex = 13;
				 this->label2->Text = L"Feedback Box";
				 // 
				 // WiseGUI
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(951, 451);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->SavingDirectoryBox);
				 this->Controls->Add(this->Command);
				 this->Controls->Add(this->displayBox);
				 this->Controls->Add(this->Exit);
				 this->Controls->Add(this->feedbackBox);
				 this->Controls->Add(this->dropdownBox);
				 this->Controls->Add(this->Enter);
				 this->Controls->Add(this->CmdLineBox);
				 this->MaximizeBox = false;
				 this->Name = L"WiseGUI";
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Text = L"WiseGUI";
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

				 if (CmdLineBox->Text == "\r\n"){
					 MessageBox::Show("Wrong Input, re-enter:");
				 }
				 else{
					 string input = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);
					 string result = logic->handleInput(input);
					 String^ feedback = gcnew String(result.c_str());
					 feedbackBox->Text = feedback;
				 }

				 string temp = logic->handleInput("displaydropdown Display All Tasks");
				 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
				 dropdownBox->SelectedItem = "Display All Tasks";
				 displayBox->Text = tasksToBeDisplayed;
				
				 string temp2 = logic->getCurrentDirectory();
				 String^ directory = gcnew String(temp2.c_str());
				 SavingDirectoryBox->Text = directory;
				 return;
	}
	private: System::Void dropdownBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 Object^ selection = dropdownBox->SelectedItem;
				 if (selection == "Display All Tasks"){
					 string temp = logic->handleInput("displaydropdown Display All Tasks");
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Tasks to be done today"){
					 string temp = logic->handleInput("displaydropdown Tasks to be done today");
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Sort by Date"){
					 string temp = logic->handleInput("displaydropdown Sort by Date");
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Sort by Priority"){
					 string temp = logic->handleInput("displaydropdown Sort by Priority");
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Display Unbounded Tasks"){
					 string temp = logic->handleInput("displaydropdown Display Unbounded Tasks");
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }

	}
	private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e) {
				 logic->handleInput("exit");
	}

	private: System::Void feedbackBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}