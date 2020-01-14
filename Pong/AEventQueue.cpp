#include "AEventQueue.h"

AEventQueue::AEventQueue()
{
	this->event_queue = al_create_event_queue();
	Validate::object_was_initialized(this->event_queue, "Event Queue");
}

AEventQueue::~AEventQueue()
{
	al_destroy_event_queue(this->event_queue);
}

ALLEGRO_EVENT_QUEUE * AEventQueue::getEventQueue()
{
	return this->event_queue;
}
