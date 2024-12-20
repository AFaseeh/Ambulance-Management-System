#pragma once
#include <iostream>
#include <fstream>
#include "Hospital.h"

class Organiser;

enum UI_MODE
{
	INTERACTIVE, 
	SILENT
};

class UI
{
	UI_MODE mode;
public:
	UI();
	std::string Loadfile();
	void Error(std::string errorMessage);
	void PrintTimeStep(Organiser* org, int time, Hospital* hospital, string message);
	void PrintMessage(string message);
	void EnterProgramMode();
	UI_MODE GetProgramMode() const;
};

