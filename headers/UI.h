#pragma once
#include <iostream>
#include <fstream>

class UI
{
public:
	std::string Loadfile();
	void Error(std::string errorMessage);
};

