#pragma once
#ifndef _ERRORPUMP_H
#define _ERRORPUMP_H
#include <glvf.h>
#include <string>
#include <vector>
#include "Instance.h"
class ErrorPump {
private:
	std::vector<GLVFError> errors;
public:
	class Instance* parentInstance;
	void reportError(GLVFResult result, std::string message);
	int32_t getCount();
	int32_t get(int32_t num, GLVFError* output);
};
#endif