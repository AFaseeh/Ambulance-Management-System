#include "../headers/UI.h"
#include "../headers/Hospital.h"
#include "../headers/Organiser.h"
#include <iostream>
#include <conio.h>
using namespace std;

string UI::Loadfile()
{
	cout << "Enter File Name (enter \"-1\" for default file): ";
	string fname;
	cin >> fname;
	if (strcmp("-1", fname.c_str()) == 0)
	{
		fname = "Test1";
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
