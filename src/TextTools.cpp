#include "pch.h"
#include "TextTools.h"

std::string TextTools::getCenteredString(std::string text, int width)
{
	int length = int(text.length());
	if (width < length) {
		return text;
	}
	int lengthDifference = width - length;
	int leftPaddingLength = (lengthDifference - 1) / 2;
	int rightPaddingLength = lengthDifference - leftPaddingLength;
	std::string centeredString =
		std::string(leftPaddingLength, ' ') +
		text +
		std::string(rightPaddingLength, ' ');

	return centeredString;
}

std::string TextTools::getCenteredString(int number, int width)
{
	return TextTools::getCenteredString(std::to_string(number), width);
}

std::string TextTools::getPadding(int number, char character)
{
	return std::string(number, character);
}

std::string TextTools::getNewLines(int number)
{
	return std::string(number, '\n');
}