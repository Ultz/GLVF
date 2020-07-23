#pragma once
#ifndef _EVENTPUMP_H
#define _EVENTPUMP_H
#include <glvf.h>
#include <string>
#include <vector>
#include "Instance.h"
class EventPump {
private:
	std::vector<GLVFEvent> events;
public:
	class View* view;
	bool waitEvents;
	int32_t getCount();
	int32_t get(int32_t num, GLVFEvent* output);
};
#endif