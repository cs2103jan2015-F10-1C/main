#pragma once
#include"WiseManager.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <msclr\marshal_cppstd.h>

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


	private: System::Windows::Forms::Button^  Exit;


	private:
		WiseManager* newManager;
	private: System::Windows::Forms::TextBox^  displayBox;

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
			this->SuspendLayout();
			// 
			// CmdLineBox
			// 
			this->CmdLineBox->AcceptsReturn = true;
			this->CmdLineBox->Location = System::Drawing::Point(12, 322);
			this->CmdLineBox->Name = L"CmdLineBox";
			this->CmdLineBox->Size = System::Drawing::Size(587, 21);
			this->CmdLineBox->TabIndex = 0;
			this->CmdLineBox->UseWaitCursor = true;
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
				L"Display All Tasks", L"Items to be done today",
					L"Sort by Date", L"Sort by Priority", L"Display Unbounded Tasks"
			});
			this->dropdownBox->Location = System::Drawing::Point(12, 11);
			this->dropdownBox->Name = L"dropdownBox";
			this->dropdownBox->Size = System::Drawing::Size(142, 20);
			this->dropdownBox->TabIndex = 3;
			this->dropdownBox->SelectedIndexChanged += gcnew System::EventHandler(this, &WiseGUI::dropdownBox_SelectedIndexChanged);
			// 
			// feedbackBox
			// 
			this->feedbackBox->Location = System::Drawing::Point(175, 12);
			this->feedbackBox->Multiline = true;
			this->feedbackBox->Name = L"feedbackBox";
			this->feedbackBox->Size = System::Drawing::Size(453, 305);
			this->feedbackBox->TabIndex = 4;
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
			// displayBox
			// 
			this->displayBox->Location = System::Drawing::Point(12, 38);
			this->displayBox->Multiline = true;
			this->displayBox->Name = L"displayBox";
			this->displayBox->Size = System::Drawing::Size(157, 278);
			this->displayBox->TabIndex = 7;
			// 
			// WiseGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(721, 352);
			this->Controls->Add(this->displayBox);
			this->Controls->Add(this->Exit);
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
					 string temp = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);
					 newManager->executeCommand(temp); 

					/* ostringstream oss;
					 oss << "size="<< newManager->getNoOfTasks()<<endl;
					 string s = oss.str();
					 String^ t = gcnew String(s.c_str()); MessageBox::Show(t);
					 */
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