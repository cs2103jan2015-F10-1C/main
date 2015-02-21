#include"WiseGUI.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	WiseUI::WiseGUI mainWindow;
	Application::Run(%mainWindow);
}