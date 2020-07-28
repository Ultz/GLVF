#include "ErrorPump.h"

void ErrorPump::reportError(GLVFResult result, std::string message)
{
	GLVFError err;
	err.errorCode = result;
	for (size_t i = 0; i < 1024 && i < message.size(); i++)
	{
		err.pErrorMessage[i] = message[i];
	}
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
