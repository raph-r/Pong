#pragma once
#include <allegro5/allegro5.h>
#include "Validate.h"

class ATimer
{
private:
	ALLEGRO_TIMER * timer = nullptr;

public:
	ATimer(const float& fps);
	~ATimer();
	ALLEGRO_TIMER * getTimer() const;
};