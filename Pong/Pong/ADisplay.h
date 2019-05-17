#pragma once
#include "Validate.h"
#include "allegro5/allegro5.h"

class ADisplay
{
private:
	ALLEGRO_DISPLAY * display = nullptr;

public:
	ADisplay(const int& width, const int& height);
	~ADisplay();
	ALLEGRO_DISPLAY * getDisplay() const;
};
