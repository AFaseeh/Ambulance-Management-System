#pragma once
#include <iostream>
#include <fstream>
#include "Hospital.h"

class Organiser;

class UI
{
public:
	std::string Loadfile();
	void Error(std::string errorMessage);
	void PrintTimeStep(Organiser* org, int time, Hospital* hospital, string message);
	void PrintMessage(string message);
};

