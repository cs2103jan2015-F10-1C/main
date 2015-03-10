#pragma once
#include"WiseManager.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <msclr\marshal_cppstd.h>

const string MESSAGE_WELCOME = "Welcome to Wise Manager V0.1! \n";
const int ADD_TYPE = 1;
const int DELETE_TYPE = 2;
const int VIEW_TYPE = 3;
const int EDIT_TYPE = 4;
const int SEARCH_TYPE = 5;
const int DISPLAY_TYPE = 6;
const int EXIT_TYPE = 7;
const int CHANGE_DIRECTORY_TYPE = 8;
const int HELP_TYPE = 9;
const int ERROR_TYPE = -1;

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
			newManager = new WiseManager;
			dataBaseRead = new ifstream;
			dataBaseWrite = new ofstream;

			fileDirectory = newManager->getFileDirectory("fileNameStorage.txt");

			dataBaseRead->open(fileDirectory);
			dataBaseWrite->open("temp.txt");
			newManager->initialise(dataBaseRead, dataBaseWrite, "temp.txt");
			InitializeComponent();
			String^ feedback = gcnew String(MESSAGE_WELCOME.c_str());
			feedbackBox->Text = feedback;

			SavingDirectoryBox->Text = gcnew String(fileDirectory.c_str());;
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

	protected:


	private: System::Windows::Forms::ComboBox^  dropdownBox;
	private: System::Windows::Forms::TextBox^  feedbackBox;


	private: System::Windows::Forms::Button^  Exit;


	private:
		WiseManager* newManager;
		ifstream* dataBaseRead;
		ofstream* dataBaseWrite;

	private: System::Windows::Forms::TextBox^  displayBox;
	private: System::Windows::Forms::TextBox^  Feedback;
	private: System::Windows::Forms::TextBox^  Command;
	private: System::Windows::Forms::TextBox^  SavingDirectory;
	private: System::Windows::Forms::TextBox^  SavingDirectoryBox;





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
			this->Feedback = (gcnew System::Windows::Forms::TextBox());
			this->Command = (gcnew System::Windows::Forms::TextBox());
			this->SavingDirectory = (gcnew System::Windows::Forms::TextBox());
			this->SavingDirectoryBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// CmdLineBox
			// 
			this->CmdLineBox->Location = System::Drawing::Point(81, 418);
			this->CmdLineBox->Multiline = true;
			this->CmdLineBox->Name = L"CmdLineBox";
			this->CmdLineBox->Size = System::Drawing::Size(516, 21);
			this->CmdLineBox->TabIndex = 0;
			this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
			// 
			// Enter
			// 
			this->Enter->Location = System::Drawing::Point(634, 417);
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
			this->feedbackBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->feedbackBox->Size = System::Drawing::Size(413, 299);
			this->feedbackBox->TabIndex = 4;
			// 
			// Exit
			// 
			this->Exit->AllowDrop = true;
			this->Exit->Location = System::Drawing::Point(746, 418);
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
			this->displayBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->displayBox->Size = System::Drawing::Size(376, 374);
			this->displayBox->TabIndex = 7;
			// 
			// Feedback
			// 
			this->Feedback->Location = System::Drawing::Point(408, 12);
			this->Feedback->Name = L"Feedback";
			this->Feedback->Size = System::Drawing::Size(80, 21);
			this->Feedback->TabIndex = 8;
			this->Feedback->Text = L"Feedback Box";
			// 
			// Command
			// 
			this->Command->Location = System::Drawing::Point(12, 418);
			this->Command->Name = L"Command";
			this->Command->Size = System::Drawing::Size(72, 21);
			this->Command->TabIndex = 9;
			this->Command->Text = L"Command: //";
			// 
			// SavingDirectory
			// 
			this->SavingDirectory->Location = System::Drawing::Point(408, 343);
			this->SavingDirectory->Name = L"SavingDirectory";
			this->SavingDirectory->Size = System::Drawing::Size(123, 21);
			this->SavingDirectory->TabIndex = 10;
			this->SavingDirectory->Text = L"Current Saving File";
			// 
			// SavingDirectoryBox
			// 
			this->SavingDirectoryBox->Location = System::Drawing::Point(408, 370);
			this->SavingDirectoryBox->Multiline = true;
			this->SavingDirectoryBox->Name = L"SavingDirectoryBox";
			this->SavingDirectoryBox->Size = System::Drawing::Size(413, 42);
			this->SavingDirectoryBox->TabIndex = 11;
			// 
			// WiseGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(834, 451);
			this->Controls->Add(this->SavingDirectoryBox);
			this->Controls->Add(this->SavingDirectory);
			this->Controls->Add(this->Command);
			this->Controls->Add(this->Feedback);
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
				 int* commandType = new int;
				 string* outputMessage= new string("");
				 if (CmdLineBox->Text == "\r\n"){
					 MessageBox::Show("Wrong Input, re-enter:");
				 }
				 else{
					 string temp = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);
					 newManager->executeCommand(temp, dataBaseRead, dataBaseWrite, commandType, outputMessage, "temp.txt", fileDirectory); 
					 MessageBox::Show(gcnew String(gcnew String(to_string(*commandType).c_str())));
					 
					 if (*commandType == EXIT_TYPE){
						 Exit_Click(sender, e);
					 }
					 else if (*commandType == SEARCH_TYPE || *commandType == ADD_TYPE || *commandType == DELETE_TYPE
						 || *commandType == DISPLAY_TYPE || *commandType == EDIT_TYPE || *commandType == ERROR_TYPE
						 || *commandType == VIEW_TYPE || *commandType == HELP_TYPE){
						 String^ feedback = gcnew String(outputMessage->c_str());
						 feedbackBox->Text = feedback;
					 }
					 else if (*commandType == CHANGE_DIRECTORY_TYPE){
	
						 String^ feedback = gcnew String(outputMessage->c_str());
						 feedbackBox->Text = feedback;
						 
						 SavingDirectoryBox->Text = gcnew String(fileDirectory.c_str());
					 }
	
					 if (*commandType == ADD_TYPE || *commandType == DELETE_TYPE || *commandType == EDIT_TYPE){
						 string temp = newManager->displayAllTask();
						 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
						 dropdownBox->SelectedItem = "Display All Tasks";
						 displayBox->Text = tasksToBeDisplayed;
					 }
				 }
				 return;
	}
	private: System::Void dropdownBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 Object^ selection = dropdownBox->SelectedItem; 
				 if (selection == "Display All Tasks"){
					 string temp = newManager->displayAllTask();
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
					 }
				 else if (selection == "Tasks to be done today"){
					 string temp = newManager->getTodayTask();
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Sort by Date"){
					 string temp = newManager->sortTasksByDate();
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Sort by Priority"){
					 string temp = newManager->sortTasksPriority();
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 else if (selection == "Display Unbounded Tasks"){
					 string temp = newManager->getUnboundedTasks();
					 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
					 displayBox->Text = tasksToBeDisplayed;
				 }
				 
				 }
	private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e) {
				 dataBaseRead->close();
				 dataBaseWrite->close();
				 dataBaseRead->open("temp.txt");
				 dataBaseWrite->open(fileDirectory);
				 newManager->transferData(dataBaseWrite, dataBaseRead);
				 dataBaseRead->close();
				 dataBaseWrite->close();
				 Application::Exit();
	}

};
}