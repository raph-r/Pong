#pragma once
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "Validate.h"
/**
 * <EN>
 * Encapsulate the ALLEGRO_FONT class - TTF
 *
 * <PT-Br>
 * Encapsula a classe ALLEGRO_FONT - TTF
*/
class ATTFFont
{
private:
	ALLEGRO_FONT * font = nullptr; // ALEGRO_FONT that instance represents

public:
	/**
	 * <EN>
	 * Class constructor. Load a TTF font, with specific size
	 * @param[in] path - Filepath of font
	 * @param[in] size - Size of font
	 *
	 * <PT-Br>
	 * Construtor da classe. Carregar a fonte TTF, com o tamanho especifico
	 * @param[in] path - Caminho da fonte
	 * @param[in] size - Tamanho da fontes
	*/
	ATTFFont(const char * path, const int& size);

	/**
	 * <EN>
	 * Class desconstructor
	 *
	 * <PT-Br>
	 * Desconstrutor da classe
	*/
	~ATTFFont();

	/**
	 * <EN>
	 * Get the font that instance represents
	 * @return Pointer to ALLEGRO_FONT
	 *
	 * <PT-Br>
	 * Captura a fonte que a instancia representa
	 * @return ponteiro para ALLEGRO_FONT
	*/
	ALLEGRO_FONT * getFont() const;
};
