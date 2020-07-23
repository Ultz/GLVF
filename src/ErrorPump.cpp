#include "ErrorPump.h"

void ErrorPump::reportError(GLVFResult result, std::string function, std::string message)
{
	GLVFError err;
	err.errorCode = result;
	err.pFunctionName = &function[0];
	err.pErrorMessage = &message[0];
	errors.push_back(err);
}

int32_t ErrorPump::getCount()
{
	return errors.size();
}

int32_t ErrorPump::get(int32_t num, GLVFError* output)
{
	size_t i;
	for (i = 0; i < num && i < errors.size(); i++)
	{
		output[i] = errors[i];
	}

	errors.erase(errors.begin(), errors.begin() + i);
	return i;
}
