
#include "HelperFn.h"
#include <iostream>
#include <string>
using namespace std;

bool IsValue(string input)
{
	int i = 0;
	bool hasdigit = false, hasdecimal = false;
	if (input[i] == '-' || input[i] == '+')
		i++;
	while (i < input.length())
	{
		if (isdigit(input[i]))
			hasdigit = true;
		else if (input[i] == '.')
		{
			if (hasdecimal)
				return false;

			hasdecimal = true;
		}
		else
		{
			return false;
		}

		i++;



	}



	return hasdigit;
}

bool IsVariable(string input)
{
		if (!(('A' <= input[0] && input[0] <= 'Z') || ('a' <= input[0] && input[0] <= 'z') || input[0] == '_'))
			return false;

		for (int i = 0; i < input.length(); i++)
		{
			if (!(('A' <= input[i] && input[i] <= 'Z') || ('a' <= input[i] && input[i] <= 'z') || input[i] == '_' || ('0' <= input[i] && input[i] <= '9')))
				return false;
		}
		return true;
	}

OpType ValueOrVariable (string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	if (IsValue(input))
		return VALUE_OP;
	if (IsVariable(input))
		return VARIABLE_OP;

	return INVALID_OP;
}
