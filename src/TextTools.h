#pragma once
#include <iostream>
#include <iomanip>
#include <string>
class TextTools
{
public:
	static std::string getCenteredString(std::string text, int width=0);
	static std::string getCenteredString(int number, int width = 0);
	static std::string getPadding(int number, char character = ' ');
	static std::string getNewLines(int number);
};

