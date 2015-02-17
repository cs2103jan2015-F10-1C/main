#pragma once
#include "WiseManager.h"

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
			this->CmdLineBox->AcceptsReturn = true;
			this->CmdLineBox->Location = System::Drawing::Point(12, 349);
			this->CmdLineBox->Name = L"CmdLineBox";
			this->CmdLineBox->Size = System::Drawing::Size(587, 20);
			this->CmdLineBox->TabIndex = 0;
			this->CmdLineBox->Text = L"Insert CLI command here";
			this->CmdLineBox->UseWaitCursor = true;
			this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::textBox1_TextChanged);
			// 
			// Enter
			// 
			this->Enter->Location = System::Drawing::Point(634, 320);
			this->Enter->Name = L"Enter";
			this->Enter->Size = System::Drawing::Size(75, 23);
			this->Enter->TabIndex = 2;
			this->Enter->Text = L"Enter";
			this->Enter->UseVisualStyleBackColor = true;
			this->Enter->Click += gcnew System::EventHandler(this, &WiseGUI::button1_Click);
			// 
			// dropdownBox
			// 
			this->dropdownBox->FormattingEnabled = true;
			this->dropdownBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Items to be done today", L"Sort by Date", L"Sort by Priority",
					L"Display Unbounded Tasks"
			});
			this->dropdownBox->Location = System::Drawing::Point(12, 12);
			this->dropdownBox->Name = L"dropdownBox";
			this->dropdownBox->Size = System::Drawing::Size(142, 21);
			this->dropdownBox->TabIndex = 3;
			this->dropdownBox->SelectedIndexChanged += gcnew System::EventHandler(this, &WiseGUI::dropdownBox_SelectedIndexChanged);
			// 
			// feedbackBox
			// 
			this->feedbackBox->Location = System::Drawing::Point(175, 13);
			this->feedbackBox->Multiline = true;
			this->feedbackBox->Name = L"feedbackBox";
			this->feedbackBox->Size = System::Drawing::Size(453, 330);
			this->feedbackBox->TabIndex = 4;
			this->feedbackBox->Text = L"This feedback box will give information on the datas available so that the user w"
				L"ill be able to make further commands in the CLI";
			this->feedbackBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::feedbackBox_TextChanged);
			// 
			// displayBox
			// 
			this->displayBox->Location = System::Drawing::Point(12, 39);
			this->displayBox->Name = L"displayBox";
			this->displayBox->Size = System::Drawing::Size(142, 304);
			this->displayBox->TabIndex = 5;
			this->displayBox->UseCompatibleStateImageBehavior = false;
			// 
			// Exit
			// 
			this->Exit->AllowDrop = true;
			this->Exit->Location = System::Drawing::Point(634, 349);
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(75, 23);
			this->Exit->TabIndex = 6;
			this->Exit->Text = L"E&xit";
			this->Exit->UseVisualStyleBackColor = true;
			this->Exit->Click += gcnew System::EventHandler(this, &WiseGUI::button2_Click);
			// 
			// WiseGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(721, 381);
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
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void List_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void dropdownBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void feedbackBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
