#pragma once
#include "allegro5/allegro5.h"
#include "Validate.h"

/**
 * <EN>
 * Encapsulate the ALLEGRO_EVENT_QUEUE class
 * <PT-Br>
 * Encapsula a classe ALLEGRO_EVENT_QUEUE
*/
class AEventQueue
{
	private:
		ALLEGRO_EVENT_QUEUE * event_queue = nullptr; // ALLEGRO_EVENT_QUEUE that instance represents

	public:

		/**
		 * <EN>
		 * Class constructor. Create a event queue to game
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria uma fila de evento para o jogo
		*/
		AEventQueue();

		/**
		 * <EN>
		 * Class desconstructor

		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~AEventQueue();

		/**
		 * <EN>
		 * Get the font that instance represents
		 * @return Pointer to ALLEGRO_EVENT_QUEUE
		 *
		 * <PT-Br>
		 * Captura a fonte que a instancia representa
		 * @return ponteiro para ALLEGRO_EVENT_QUEUE
		*/
		ALLEGRO_EVENT_QUEUE * getEventQueue();
};