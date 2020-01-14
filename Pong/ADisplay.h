#pragma once
#include "Validate.h"
#include "Constant.h"
#include "allegro5/allegro5.h"

/**
 * <EN>
 * Encapsulate the ALLEGRO_DISPLAY class
 * <PT-Br>
 * Encapsula a classe ALLEGRO_DISPLAY
*/
class ADisplay
{
	private:
		ALLEGRO_DISPLAY * display = nullptr; // ALEGRO_DISPLAY that instance represents

	public:

		/**
		 * <EN>
		 * Class constructor. Create a screen to game
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria uma tela para o jogo
		*/
		ADisplay();

		/**
		 * <EN>
		 * Class desconstructor

		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~ADisplay();

		/**
		 * <EN>
		 * Get the font that instance represents
		 * @return Pointer to ALLEGRO_DISPLAY
		 *
		 * <PT-Br>
		 * Captura a fonte que a instancia representa
		 * @return ponteiro para ALLEGRO_DISPLAY
		*/
		ALLEGRO_DISPLAY * getDisplay() const;
};
