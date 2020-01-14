#include "ADisplay.h"

ADisplay::ADisplay()
{
	this->display = al_create_display(Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT);
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
