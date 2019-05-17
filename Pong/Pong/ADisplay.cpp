#include "ADisplay.h"

ADisplay::ADisplay(const int & width, const int& height)
{
	this->display = al_create_display(width, height);
	Validate::object_was_initialized(this->display, "Display");
}

ADisplay::~ADisplay()
{
	al_destroy_display(this->display);
}

ALLEGRO_DISPLAY * ADisplay::getDisplay() const
{
	return this->display;
}
