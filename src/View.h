#pragma once
#ifndef _VIEW_H
#define _VIEW_H
#include <glvf.h>
#include "EventPump.h"
class View {
public:
	class Instance* instance;
	class EventPump* eventPump;
	GLVFResult createEventPump(const GLVFEventPumpCreateInfo* info);
	void destroyEventPump();
	GLVFViewState getState();
	GLVFResult bootstrap(GLVFMainFunction fn);
};
#endif