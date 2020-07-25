#include "EventPump.h"

int32_t EventPump::getCount()
{
	return events.size();
}

int32_t EventPump::get(int32_t num, GLVFEvent* output)
{
	size_t i;
	for (i = 0; i < num && i < events.size(); i++)
	{
		output[i] = events[i];
	}

	events.erase(events.begin(), events.begin() + i);
	return i;
}

void EventPump::enqueue(GLVFEvent val)
{
	events.push_back(val);
}
