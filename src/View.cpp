#include "View.h"

GLVFResult View::createEventPump(const GLVFEventPumpCreateInfo* info)
{
	if (eventPump != nullptr)
	{
		return GLVF_ERROR_DUPLICATE;
	}

	eventPump = new EventPump();
	eventPump->view = this;
	eventPump->waitEvents = info->isEventDriven;
	return GLVF_OK;
}

void View::destroyEventPump()
{
	delete eventPump;
	eventPump = nullptr;
}

void View::destroying()
{
}
