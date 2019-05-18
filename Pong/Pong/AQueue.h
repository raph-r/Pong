#pragma once
#include "allegro5/allegro5.h"
#include "Validate.h"

class AQueue
{
private:
	ALLEGRO_EVENT_QUEUE * event_queue = nullptr;

public:
	AQueue();
	~AQueue();
	ALLEGRO_EVENT_QUEUE * getEventQueue();
};