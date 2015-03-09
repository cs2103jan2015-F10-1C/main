#pragma once
#include"WiseManager.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <msclr\marshal_cppstd.h>

const int ADD_TYPE = 1;
const int DELETE_TYPE = 2;
const int VIEW_TYPE = 3;
const int EDIT_TYPE = 4;
const int SEARCH_TYPE = 5;
const int DISPLAY_TYPE = 6;
const int EXIT_TYPE = 7;
const int ERROR_TYPE = -1;

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
			dataBaseRead->open("dataBase.txt");
			dataBaseWrite->open("temp.txt");
			newManager->initialise(dataBaseRead, dataBaseWrite, "temp.txt");
			InitializeComponent();
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
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;

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
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// CmdLineBox
			// 
			this->CmdLineBox->Location = System::Drawing::Point(12, 322);
			this->CmdLineBox->Multiline = true;
			this->CmdLineBox->Name = L"CmdLineBox";
			this->CmdLineBox->Size = System::Drawing::Size(587, 21);
			this->CmdLineBox->TabIndex = 0;
			this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
			// 
			// Enter
			// 
			this->Enter->Location = System::Drawing::Point(634, 295);
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
			this->dropdownBox->Size = System::Drawing::Size(232, 20);
			this->dropdownBox->TabIndex = 3;
			this->dropdownBox->SelectedIndexChanged += gcnew System::EventHandler(this, &WiseGUI::dropdownBox_SelectedIndexChanged);
			// 
			// feedbackBox
			// 
			this->feedbackBox->Location = System::Drawing::Point(250, 38);
			this->feedbackBox->Multiline = true;
			this->feedbackBox->Name = L"feedbackBox";
			this->feedbackBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->feedbackBox->Size = System::Drawing::Size(378, 279);
			this->feedbackBox->TabIndex = 4;
			this->feedbackBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::feedbackBox_TextChanged);
			// 
			// Exit
			// 
			this->Exit->AllowDrop = true;
			this->Exit->Location = System::Drawing::Point(634, 322);
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
			this->displayBox->Size = System::Drawing::Size(232, 278);
			this->displayBox->TabIndex = 7;
			this->displayBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::displayBox_TextChanged);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WiseGUI::saveFileDialog1_FileOk);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(250, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(80, 21);
			this->textBox1->TabIndex = 8;
			this->textBox1->Text = L"Feedback Box";
			// 
			// WiseGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(721, 352);
			this->Controls->Add(this->textBox1);
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
					 newManager->executeCommand(temp, dataBaseWrite, commandType, outputMessage, "temp.txt");
					 if (*commandType == EXIT_TYPE){
						 Exit_Click(sender, e);
					 }
					 else if (*commandType == SEARCH_TYPE || *commandType == ADD_TYPE || *commandType == DELETE_TYPE
						 || *commandType == DISPLAY_TYPE || *commandType == EDIT_TYPE || *commandType == ERROR_TYPE
						 || *commandType == VIEW_TYPE){
						 String^ feedback = gcnew String(outputMessage->c_str());
						 feedbackBox->Text = feedback;
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

				 }
	private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e) {
				 dataBaseRead->close();
				 dataBaseWrite->close();
				 dataBaseRead->open("temp.txt");
				 dataBaseWrite->open("dataBase.txt");
				 newManager->transferData(dataBaseWrite, dataBaseRead);
				 dataBaseRead->close();
				 dataBaseWrite->close();
				 Application::Exit();
	}
private: System::Void feedbackBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void displayBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
}
};
}