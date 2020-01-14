#include "AFont.h"

AFont::AFont()
{
	this->font = al_create_builtin_font();
	Validate::object_was_initialized(this->font, "Font");
}

AFont::~AFont()
{
	al_destroy_font(this->font);
}

ALLEGRO_FONT * AFont::getFont()
{
	return this->font;
}
