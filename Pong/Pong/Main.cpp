#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "allegro5/allegro_primitives.h"

#include <memory>

int main(int argn, char** argv)
{
	//controla o loop de saida do jogo
	bool continue_to_play = true;

	//Inicializa os objetos basicos da allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");

	//Inicializa os da Allegro que foram encapsulados
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(640, 480);
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();

	//Adiciona as fontes de eventos a Queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	UPATimer->startTimer();

	ALLEGRO_EVENT event;
	bool draw = false;

	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			draw = true;
			//logic
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				continue_to_play = false;
			}
		default:
			break;
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;

			al_draw_filled_rectangle(100, 50, 115, 100, al_map_rgba_f(1, 1, 1, 1));
			al_flip_display();
		}
	}
	return 0;
}