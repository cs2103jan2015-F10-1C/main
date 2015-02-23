#pragma once

#include "WiseManager.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <msclr\marshal_cppstd.h>
using namespace System;

static void ClrStringToStdString(std::string &outStr, System::String ^str) {
	IntPtr ansiStr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str); 
	outStr = (const char*)ansiStr.ToPointer(); 
	System::Runtime::InteropServices::Marshal::FreeHGlobal(ansiStr); 
}


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
			newManager->initialise();
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
	private: System::Windows::Forms::ListView^  displayBox;

	private: System::Windows::Forms::Button^  Exit;


	private:
		WiseManager* newManager;

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
			this->displayBox = (gcnew System::Windows::Forms::ListView());
			this->Exit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// CmdLineBox
			// 
			this->CmdLineBox->Location = System::Drawing::Point(12, 322);
			this->CmdLineBox->Multiline = true;
			this->CmdLineBox->Name = L"CmdLineBox";
			this->CmdLineBox->Size = System::Drawing::Size(587, 21);
			this->CmdLineBox->TabIndex = 1;
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
			this->dropdownBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Items to be done today", L"Sort by Date", L"Sort by Priority",
					L"Display Unbounded Tasks"
			});
			this->dropdownBox->Location = System::Drawing::Point(12, 11);
			this->dropdownBox->Name = L"dropdownBox";
			this->dropdownBox->Size = System::Drawing::Size(142, 20);
			this->dropdownBox->TabIndex = 3;
			// 
			// feedbackBox
			// 
			this->feedbackBox->Location = System::Drawing::Point(175, 12);
			this->feedbackBox->Multiline = true;
			this->feedbackBox->Name = L"feedbackBox";
			this->feedbackBox->Size = System::Drawing::Size(453, 305);
			this->feedbackBox->TabIndex = 4;
			this->feedbackBox->Text = L"This feedback box will give information on the datas available so that the user w"
				L"ill be able to make further commands in the CLI";
			// 
			// displayBox
			// 
			this->displayBox->Location = System::Drawing::Point(12, 36);
			this->displayBox->Name = L"displayBox";
			this->displayBox->Size = System::Drawing::Size(142, 281);
			this->displayBox->TabIndex = 5;
			this->displayBox->UseCompatibleStateImageBehavior = false;
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
			// 
			// WiseGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(721, 352);
			this->Controls->Add(this->Exit);
			this->Controls->Add(this->displayBox);
			this->Controls->Add(this->feedbackBox);
			this->Controls->Add(this->dropdownBox);
			this->Controls->Add(this->Enter);
			this->Controls->Add(this->CmdLineBox);
			this->Name = L"WiseGUI";
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
					 wchar_t lastElement = newCmd[size - 1];
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

					 string temp = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);

					 System::String^ text = CmdLineBox->Text;
					 std::string temp; 
					 ClrStringToStdString(temp, text);


					 newManager->executeCommand(temp);
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
				 }
	};
}