#include "AQueue.h"

AQueue::AQueue()
{
	this->event_queue = al_create_event_queue();
	Validate::object_was_initialized(this->event_queue);
}

AQueue::~AQueue()
{
	al_destroy_event_queue(this->event_queue);
}

ALLEGRO_EVENT_QUEUE * AQueue::getEventQueue()
{
	return this->event_queue;
}
