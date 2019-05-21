#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "Ball.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include <iostream>
#include "OMPlayer.h"
#define KEY_SEEN 1
#define KEY_RELEASED 2

void draw_field(const int& height_portion, const ALLEGRO_COLOR& ACWhite)
{
	//draw top line
	al_draw_filled_rectangle(0, MARGIN_TOP + 1, SCREEN_WIDTH, height_portion + 1, ACWhite);

	//draw botton line
	al_draw_filled_rectangle(0, SCREEN_HEIGHT - height_portion - 1, SCREEN_WIDTH, SCREEN_HEIGHT - MARGIN_BOTTON - 1, ACWhite);

	//draw division line
	for (unsigned int i = 1; i < 19; i++)
	{
		al_draw_filled_rectangle(
			(SCREEN_WIDTH / 2) - 2,
			MARGIN_TOP + MARGIN_BOTTON + (i * height_portion),
			(SCREEN_WIDTH / 2) + 2,
			MARGIN_TOP + MARGIN_BOTTON + ((i++) * height_portion),
			ACWhite
		);
	}
}

int main(int argn, char** argv)
{
	bool continue_to_play = true;

	// partição da altura da tela
	int height_division = (SCREEN_HEIGHT - (MARGIN_TOP + MARGIN_BOTTON)) / 20;

	Ball ball(10, 10, ((SCREEN_WIDTH / 2) - 5), ((SCREEN_HEIGHT / 2)) - 5, 3, 3);

	//Inicializa os objetos basicos da allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");

	//Inicializa os da Allegro que foram encapsulados
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	ALLEGRO_FONT * font = al_create_builtin_font();
	Validate::object_was_initialized(font, "Font");

	//Adiciona as fontes de eventos a Queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	// color palettes
	ALLEGRO_COLOR ACBlack = al_map_rgba_f(0, 0, 0, 0);
	ALLEGRO_COLOR ACWhite = al_map_rgba_f(1, 1, 1, 1);

	//Players 
	Player p1(ALLEGRO_KEY_W, ALLEGRO_KEY_S, MARGIN_LEFT + 1, 10, 60, 0);
	Player p2(ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, SCREEN_WIDTH - MARGIN_RIGHT - 10 - 1, 10, 60, 0);

	
	//OMPlayer p1(MARGIN_LEFT + 1, (SCREEN_HEIGHT / 2) - (60 / 2), 10, 60, 4, 4, ALLEGRO_KEY_W, ALLEGRO_KEY_S);

	bool reset_objects_position = false;

	ALLEGRO_EVENT event;
	bool draw = false;

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	
	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:

				// move player 1			
				if (key[ALLEGRO_KEY_W] && p1.top_collision_line() > height_division) // limite superior
				{
					p1.up();
				}
				if (key[ALLEGRO_KEY_S] && p1.botton_collision_line() < (SCREEN_HEIGHT - height_division)) // limite inferior
				{
					p1.down();
				}

				// move player 2
				if (key[ALLEGRO_KEY_UP] && p2.top_collision_line() > height_division) // limite superior
				{
					p2.up();
				}
				if (key[ALLEGRO_KEY_DOWN] && p2.botton_collision_line() < (SCREEN_HEIGHT - height_division)) // limite inferior
				{
					p2.down();
				}

				// exit game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				for (unsigned int i = 0; i < ALLEGRO_KEY_MAX; i++)
				{
					key[i] &= KEY_SEEN;
				}
				draw = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				continue_to_play = false;
				break;
			default:
				break;
		}
		
		//player 1 gol
		if (ball.right_collision_line() >= p2.right_collision_line())
		{
			p1.add_score();
			reset_objects_position = true;
		}
		//player 2 gol
		else if (ball.left_collision_line() <= p1.left_collision_line())
		{
			p2.add_score();
			reset_objects_position = true;
		}

		if (reset_objects_position)
		{
			p1.reset_position();
			p2.reset_position();
			ball.reset_position();
			ball.change_acceleration_y();
			reset_objects_position = false;
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			al_clear_to_color(ACBlack);
			
			// draw player1 (left player)
			al_draw_filled_rectangle(
				p1.left_collision_line(),
				p1.top_collision_line(),
				p1.right_collision_line(),
				p1.botton_collision_line(),
				ACWhite
			);

			//draw player2 (right player)
			al_draw_filled_rectangle(
				p2.left_collision_line(),
				p2.top_collision_line(),
				p2.right_collision_line(),
				p2.botton_collision_line(),
				ACWhite
			);

			//draw ball
			ball.move_ball(height_division, &p1, &p2);
			al_draw_filled_rectangle(
				ball.left_collision_line(),
				ball.top_collision_line(),
				ball.right_collision_line(),
				ball.botton_collision_line(),
				ACWhite
			);

			al_draw_textf(font, ACWhite, 2, 2, 0, "Player 1:%u - Player 2:%u", p1.get_score(), p2.get_score());
			
			draw_field(height_division, ACWhite);
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}