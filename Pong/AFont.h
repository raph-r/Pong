#pragma once
#include "allegro5/allegro_font.h"
#include "Validate.h"

class AFont
{
private:
	ALLEGRO_FONT * font = nullptr;

public:
	AFont();
	~AFont();
	ALLEGRO_FONT * getFont();

};
