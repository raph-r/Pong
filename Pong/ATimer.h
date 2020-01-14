#pragma once
#include <allegro5/allegro5.h>
#include "Validate.h"

/**
 * <EN>
 * Encapsulate the ALLEGRO_TIMER class
 * <PT-Br>
 * Encapsula a classe ALLEGRO_TIMER
*/
class ATimer
{
	private:
		ALLEGRO_TIMER * timer = nullptr;// ALLEGRO_TIMER that instance represents

	public:

		/**
		 * <EN>
		 * Class constructor. Create a timer to game
		 * @param[in] fps - Frames per second
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria um timer para o jogo
		 * @param[in] fps - Quadros por segundo
		*/
		ATimer(const float& fps);

		/**
		 * <EN>
		 * Class desconstructor

		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~ATimer();

		/**
		 * <EN>
		 * Get the font that instance represents
		 * @return Pointer to ALLEGRO_TIMER
		 *
		 * <PT-Br>
		 * Captura a fonte que a instancia representa
		 * @return ponteiro para ALLEGRO_TIMER
		*/
		ALLEGRO_TIMER * getTimer() const;

		/**
		 * <EN>
		 * Initializes the timer
		 *
		 * <PT-Br>
		 * Inicializa o timer
		*/
		void startTimer();
};