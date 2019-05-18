#pragma once
#include "allegro5/allegro5.h"
#include "Validate.h"

class AEventQueue
{
private:
	ALLEGRO_EVENT_QUEUE * event_queue = nullptr;

public:
	AEventQueue();
	~AEventQueue();
	ALLEGRO_EVENT_QUEUE * getEventQueue();
};