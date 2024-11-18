#include "../headers/UI.h"
#include <iostream>
using namespace std;

string UI::Loadfile()
{
	cout << "Enter File Name: ";
	string fname;
	cin >> fname;

	return ("./TextFiles/Input/" + fname + ".txt");
}

void UI::Error(std::string errorMessage)
{
	cout << errorMessage << endl;
	return;
}
