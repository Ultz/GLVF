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
	virtual void destroying();
	virtual GLVFViewStatus getState() = 0;
	virtual GLVFResult bootstrap(GLVFMainFunction fn) = 0;
	virtual GLVFResult getVisibility(GLVFBool* result) = 0;
	virtual GLVFResult getPosition(int32_t* result) = 0;
	virtual GLVFResult getSize(int32_t* result) = 0;
	virtual GLVFResult getTitle(int8_t** result) = 0;
	virtual GLVFResult getUI(GLVFUserInterface* result) = 0;
	virtual GLVFResult getWindowState(GLVFWindowState* result) = 0;
	virtual GLVFResult getVideoMode(GLVFVideoMode* result) = 0;
	virtual GLVFResult setVisibility(GLVFBool* value) = 0;
	virtual GLVFResult setPosition(int32_t* value) = 0;
	virtual GLVFResult setSize(int32_t* value) = 0;
	virtual GLVFResult setTitle(int8_t** value) = 0;
	virtual GLVFResult setUI(GLVFUserInterface* value) = 0;
	virtual GLVFResult setWindowState(GLVFWindowState* value) = 0;
	virtual GLVFResult setVideoMode(GLVFVideoMode* value) = 0;
	virtual GLVFResult makeCurrent() = 0;
	virtual GLVFResult swapBuffers() = 0;
	virtual GLVFResult swapInterval(int32_t interval) = 0;
};
#endif