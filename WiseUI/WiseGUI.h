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
#include "ExecuteHelp.h"
#include "ExtDataBase.h"
#include "ExecuteDirectory.h"
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include <time.h>
#include <cassert>
#include <msclr\marshal_cppstd.h>
#include "CurrentDate.h"
#include "Log.h"
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

string test = "";
Log* _log;
string fileDirectory;
Date attainDate;
string date = attainDate.getDateDetails(attainDate.getTodayDate());
string date7daysLater = attainDate.getDateDetails(attainDate.getXDaysLaterDate(6));

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

//@author A0093863U
		WiseGUI(void)
		{
			logic = new Logic;
			_log = new Log;
			InitializeComponent();

			String^ dateDisplayed = gcnew String(date.c_str());
			dateBox->Text = dateDisplayed;

			bool isOutdated = false;
			string outdated = MESSAGE_OUTDATED + logic->realTimeCheck(isOutdated);
			String^ outdatedDisplayed = gcnew String(outdated.c_str());
			if (isOutdated){
				bool successful = false;
				bool edited = false;
				string temp = logic->handleInput("display", edited, successful);
				string overall = outdated + "\r\n" + temp;
				String^ tasksToBeDisplayed = gcnew String(overall.c_str());
				displayBox->Text = tasksToBeDisplayed;
			}
			else{
				bool successful = false;
				bool edited = false;
				string temp = logic->handleInput("display", edited, successful);
				String^ tasksToBeDisplayed = gcnew String(temp.c_str());
				displayBox->Text = tasksToBeDisplayed;
			}
		}

	protected:
		~WiseGUI()
		{
			if (components)
			{
				delete components;
			}
		}

//@author generated
	private: System::Windows::Forms::TextBox^  CmdLineBox;
	protected:

	protected: Logic* logic;

	protected:

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  dateBox;
	private: System::Drawing::Icon^ ico;
	private: System::Windows::Forms::NotifyIcon^  WiseManager;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  showWindowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hideWindowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::RichTextBox^  displayBox2;
	private: System::Windows::Forms::RichTextBox^  displayBox;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;

	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WiseGUI::typeid));
				 this->CmdLineBox = (gcnew System::Windows::Forms::TextBox());
				 this->dateBox = (gcnew System::Windows::Forms::TextBox());
				 this->WiseManager = (gcnew System::Windows::Forms::NotifyIcon(this->components));
				 this->contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->showWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->hideWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
				 this->displayBox2 = (gcnew System::Windows::Forms::RichTextBox());
				 this->displayBox = (gcnew System::Windows::Forms::RichTextBox());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->panel2 = (gcnew System::Windows::Forms::Panel());
				 this->contextMenuStrip->SuspendLayout();
				 this->panel1->SuspendLayout();
				 this->panel2->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // CmdLineBox
				 // 
				 this->CmdLineBox->BackColor = System::Drawing::Color::White;
				 this->CmdLineBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->CmdLineBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->CmdLineBox->Location = System::Drawing::Point(14, 492);
				 this->CmdLineBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->CmdLineBox->Multiline = true;
				 this->CmdLineBox->Name = L"CmdLineBox";
				 this->CmdLineBox->Size = System::Drawing::Size(587, 23);
				 this->CmdLineBox->TabIndex = 0;
				 this->CmdLineBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::CmdLineBox_TextChanged);
				 // 
				 // dateBox
				 // 
				 this->dateBox->BackColor = System::Drawing::Color::White;
				 this->dateBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->dateBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dateBox->ForeColor = System::Drawing::Color::Black;
				 this->dateBox->Location = System::Drawing::Point(12, 13);
				 this->dateBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->dateBox->Name = L"dateBox";
				 this->dateBox->ReadOnly = true;
				 this->dateBox->Size = System::Drawing::Size(589, 22);
				 this->dateBox->TabIndex = 15;
				 this->dateBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
				 this->dateBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::dateBox_TextChanged);
				 // 
				 // WiseManager
				 // 
				 this->WiseManager->ContextMenuStrip = this->contextMenuStrip;
				 this->WiseManager->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"WiseManager.Icon")));
				 this->WiseManager->Text = L"WiseManager";
				 this->WiseManager->Visible = true;
				 this->WiseManager->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &WiseGUI::WiseManager_MouseDoubleClick);
				 // 
				 // contextMenuStrip
				 // 
				 this->contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->showWindowToolStripMenuItem,
						 this->hideWindowToolStripMenuItem, this->exitToolStripMenuItem
				 });
				 this->contextMenuStrip->Name = L"contextMenuStrip";
				 this->contextMenuStrip->Size = System::Drawing::Size(159, 70);
				 // 
				 // showWindowToolStripMenuItem
				 // 
				 this->showWindowToolStripMenuItem->Name = L"showWindowToolStripMenuItem";
				 this->showWindowToolStripMenuItem->Size = System::Drawing::Size(158, 22);
				 this->showWindowToolStripMenuItem->Text = L"Show Window";
				 this->showWindowToolStripMenuItem->Click += gcnew System::EventHandler(this, &WiseGUI::showWindowToolStripMenuItem_Click);
				 // 
				 // hideWindowToolStripMenuItem
				 // 
				 this->hideWindowToolStripMenuItem->Name = L"hideWindowToolStripMenuItem";
				 this->hideWindowToolStripMenuItem->Size = System::Drawing::Size(158, 22);
				 this->hideWindowToolStripMenuItem->Text = L"Hide Window";
				 this->hideWindowToolStripMenuItem->Click += gcnew System::EventHandler(this, &WiseGUI::hideWindowToolStripMenuItem_Click);
				 // 
				 // exitToolStripMenuItem
				 // 
				 this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
				 this->exitToolStripMenuItem->Size = System::Drawing::Size(158, 22);
				 this->exitToolStripMenuItem->Text = L"Exit";
				 this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &WiseGUI::exitToolStripMenuItem_Click);
				 // 
				 // richTextBox1
				 // 
				 this->richTextBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
					 static_cast<System::Int32>(static_cast<System::Byte>(238)));
				 this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->richTextBox1->ForeColor = System::Drawing::Color::Gray;
				 this->richTextBox1->Location = System::Drawing::Point(70, 442);
				 this->richTextBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->richTextBox1->Name = L"richTextBox1";
				 this->richTextBox1->ReadOnly = true;
				 this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
				 this->richTextBox1->Size = System::Drawing::Size(475, 42);
				 this->richTextBox1->TabIndex = 21;
				 this->richTextBox1->Text = L"     add, delete, edit, mark, undo, search, display, help, directory, exit\n      "
					 L"                              F1 - System Tray, ESC - Exit";
				 this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &WiseGUI::richTextBox1_TextChanged);
				 // 
				 // displayBox2
				 // 
				 this->displayBox2->BackColor = System::Drawing::Color::White;
				 this->displayBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->displayBox2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->displayBox2->ForeColor = System::Drawing::Color::Black;
				 this->displayBox2->Location = System::Drawing::Point(7, 5);
				 this->displayBox2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->displayBox2->Name = L"displayBox2";
				 this->displayBox2->ReadOnly = true;
				 this->displayBox2->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
				 this->displayBox2->Size = System::Drawing::Size(570, 48);
				 this->displayBox2->TabIndex = 22;
				 this->displayBox2->Text = L"";
				 this->displayBox2->TextChanged += gcnew System::EventHandler(this, &WiseGUI::displayBox2_TextChanged);
				 // 
				 // displayBox
				 // 
				 this->displayBox->BackColor = System::Drawing::Color::White;
				 this->displayBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->displayBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->displayBox->ForeColor = System::Drawing::Color::Black;
				 this->displayBox->Location = System::Drawing::Point(58, 54);
				 this->displayBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->displayBox->Name = L"displayBox";
				 this->displayBox->ReadOnly = true;
				 this->displayBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
				 this->displayBox->Size = System::Drawing::Size(472, 222);
				 this->displayBox->TabIndex = 23;
				 this->displayBox->Text = L"";
				 this->displayBox->TextChanged += gcnew System::EventHandler(this, &WiseGUI::displayBox_TextChanged);
				 // 
				 // panel1
				 // 
				 this->panel1->BackColor = System::Drawing::Color::Black;
				 this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
				 this->panel1->Controls->Add(this->displayBox);
				 this->panel1->Location = System::Drawing::Point(12, 44);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(589, 327);
				 this->panel1->TabIndex = 24;
				 this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &WiseGUI::panel1_Paint);
				 // 
				 // panel2
				 // 
				 this->panel2->BackColor = System::Drawing::Color::Black;
				 this->panel2->Controls->Add(this->displayBox2);
				 this->panel2->Location = System::Drawing::Point(12, 377);
				 this->panel2->Name = L"panel2";
				 this->panel2->Size = System::Drawing::Size(585, 58);
				 this->panel2->TabIndex = 25;
				 // 
				 // WiseGUI
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::Color::White;
				 this->ClientSize = System::Drawing::Size(611, 528);
				 this->Controls->Add(this->dateBox);
				 this->Controls->Add(this->richTextBox1);
				 this->Controls->Add(this->CmdLineBox);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->panel2);
				 this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ForeColor = System::Drawing::SystemColors::ControlText;
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->KeyPreview = true;
				 this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
				 this->MaximizeBox = false;
				 this->Name = L"WiseGUI";
				 this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
				 this->Text = L"WiseManger";
				 this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &WiseGUI::WiseGUI_FormClosing);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &WiseGUI::WiseGUI_KeyDown);
				 this->contextMenuStrip->ResumeLayout(false);
				 this->panel1->ResumeLayout(false);
				 this->panel2->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }

//@author A0093863U
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

				 try{
					 if (CmdLineBox->Text == "\r\n"){
						 throw false;
					 }
					 else{
						 string input = msclr::interop::marshal_as<std::string>(CmdLineBox->Text);
						 _log->logInfo(input);

						 if (input[input.length() - 1] == '\r' && input[input.length()] == '\n') {
							 input = input.substr(0, input.length() - 2);
						 }

						 bool successful = false;
						 string result = logic->handleInput(input, edited, successful);
						 ostringstream message;
						 message << SUCCESSFUL_LOG << endl;
						 _log->logInfo(message.str());

						 bool isOutdated = false;
						 string outdated = MESSAGE_OUTDATED + logic->realTimeCheck(isOutdated);

						 String^ feedback = gcnew String(result.c_str());

						 for (size_t i = 0; i < input.size(); i++){
							 input[i] = tolower(input[i]);
						 }

						 istringstream iss(input);
						 string cmd = "";

						 if (input.size() > 0){
							 iss >> cmd;
						 }

						 if (cmd == "help") {
							 MessageBox::Show(feedback);
						 }
						 else if (cmd == "display" && result != MESSAGE_ERROR) {
							 dateBox->Text = gcnew String(date.c_str());
							 displayBox2->Clear();
							 if (input == "display week\r\n") {
								 string toShow = date + " to " + date7daysLater;
								 dateBox->Text = gcnew String(toShow.c_str());
							 }
							 displayBox->Text = feedback;
						 }
						 else {
							 displayBox2->Text = feedback;
						 }

						 if (edited){

							 dateBox->Text = gcnew String(date.c_str());
							 string temp;
							 bool successful = false;
							 bool isOutdated = false;
							 string outdated = MESSAGE_OUTDATED + logic->realTimeCheck(isOutdated);
							 String^ outdatedDisplayed = gcnew String(outdated.c_str());
							 if (cmd == "search") {
								 temp = logic->handleInput("display search", edited, successful);
							 }
							 else {
								 temp = logic->handleInput("display", edited, successful);
							 }
							 if (isOutdated){
								 string overall = outdated + "\r\n" + temp;
								 String^ tasksToBeDisplayed = gcnew String(overall.c_str());
								 displayBox->Text = tasksToBeDisplayed;
							 }
							 else{
								 String^ tasksToBeDisplayed = gcnew String(temp.c_str());
								 displayBox->Text = tasksToBeDisplayed;
							 }
						 }
					 }
				 }
				 catch (bool e){
					 MessageBox::Show("Wrong Input, re-enter");
				 }
				 return;
	}

	private: System::Void WiseManager_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->Show();
	}

	private: System::Void showWindowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Show(); 
	}

	private: System::Void hideWindowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Hide();
	}

	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 bool successful = false;
				 bool edited = false;
				 logic->handleInput("exit\r\n", edited, successful);
				 this->Close();
	}

	private: System::Void WiseGUI_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if ((e->KeyCode == System::Windows::Forms::Keys::F1)){
				 this->Hide();
				 WiseManager->ShowBalloonTip(1000, "Dear user:", "WiseManager now is running in system tray.", ToolTipIcon::None);
			 }
			 else if ((e->KeyCode == System::Windows::Forms::Keys::Escape)){
				 bool successful = false;
				 bool edited = false;
				 logic->handleInput("exit\r\n", edited, successful);
				 this->Close();
			 }
			 else{
			 }
		 return;
	}

private: System::Void WiseGUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 bool successful = false;
			 bool edited = false;
			 logic->handleInput("exit\r\n", edited, successful);
			 this->Close();
}
private: System::Void displayBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void dateBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void displayBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}