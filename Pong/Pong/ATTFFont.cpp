#include "ATTFFont.h"

ATTFFont::ATTFFont(const char * path, const int& size)
{
	this->font = al_load_ttf_font(path, size, ALLEGRO_TTF_NO_KERNING);;
	Validate::object_was_initialized(this->font, "Font TTF");
}

ATTFFont::~ATTFFont()
{
	al_destroy_font(this->font);
}

ALLEGRO_FONT * ATTFFont::getFont() const
{
	return this->font;
}
