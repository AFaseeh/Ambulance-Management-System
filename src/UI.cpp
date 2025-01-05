#include "../headers/UI.h"
#include "../headers/Hospital.h"
#include "../headers/Organiser.h"
#include <iostream>
#include <conio.h>
using namespace std;


UI::UI()
	: mode(UI_MODE::INTERACTIVE)
{
}

string UI::Loadfile()
{
	cout << "Enter File Name (enter \"-1\" for default file): ";
	string fname;
	cin >> fname;
	if (strcmp("-1", fname.c_str()) == 0)
	{
		fname = "testcase1";
	}

	return ("./TextFiles/Input/" + fname + ".txt");
}

void UI::Error(std::string errorMessage)
{
	cout << errorMessage << endl;
	return;
}

void UI::PrintTimeStep(Organiser* org, int time, Hospital* hospital, string message)
{
	if (mode == UI_MODE::SILENT)
	{
		return;
	}

	system("cls"); // Clears window
	cout << "Current Timestep: " << time << endl;
	cout << message;
	cout << *hospital;


	org->PrintInfo();
	cout << "Enter any value to continue" << endl;

	char ch = _getch();

}


void UI::PrintMessage(string message)
{
	cout << message << endl;
}

void UI::EnterProgramMode()
{
	int input_mode = -1;
	do 
	{
		cout << "Please select mode of operation: 0 for Interactive Mode, 1 for Silent Mode: ";
		cin >> input_mode;
	} while ((input_mode == 0 || input_mode == 1) == false);

	switch (input_mode)
	{
	case 1:
		mode = SILENT;
		break;
	default:
		mode = INTERACTIVE;
		break;
	}
}

UI_MODE UI::GetProgramMode() const
{
	return mode;
}
