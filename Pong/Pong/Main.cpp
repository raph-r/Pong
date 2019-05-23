#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include <iostream>
#include "OMPlayer.h"
#include "OMBall.h"
#define KEY_SEEN 1
#define KEY_RELEASED 2
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MARGIN_TOP 10
#define MARGIN_BOTTON 10
#define MARGIN_LEFT 30
#define MARGIN_RIGHT 30
#define HEIGHT_DIVISION ((SCREEN_HEIGHT - (MARGIN_TOP + MARGIN_BOTTON)) / 20)
#define HALF_HEIGHT (SCREEN_HEIGHT / 2)
#define HALF_WIDTH (SCREEN_WIDTH / 2)

void draw_field(const OMPlayer * p1, const OMPlayer * p2, OMBall * const ball, const Object * limit_top, const Object * limit_botton, const ALLEGRO_COLOR& ACWhite, const ALLEGRO_COLOR& ACBlack, const ALLEGRO_FONT * font)
{
	al_clear_to_color(ACBlack);

	// draw top limit
	al_draw_filled_rectangle(limit_top->collision_line_left(), limit_top->collision_line_top(), limit_top->collision_line_right(), limit_top->collision_line_botton(), ACWhite);

	// draw botton limit
	al_draw_filled_rectangle(limit_botton->collision_line_left(), limit_botton->collision_line_top(), limit_botton->collision_line_right(), limit_botton->collision_line_botton(), ACWhite);

	// draw division line
	for (unsigned int i = 2; i < 20; i++)
	{
		al_draw_filled_rectangle(HALF_WIDTH - 2, (i * HEIGHT_DIVISION), HALF_WIDTH + 2, ((i++) * HEIGHT_DIVISION), ACWhite);
	}

	// draw player1 (left player)
	al_draw_filled_rectangle(p1->collision_line_left(), p1->collision_line_top(), p1->collision_line_right(), p1->collision_line_botton(), ACWhite);

	// draw player2 (right player)
	al_draw_filled_rectangle(p2->collision_line_left(), p2->collision_line_top(), p2->collision_line_right(), p2->collision_line_botton(), ACWhite);

	// move and draw ball
	ball->move_ball(p1, p2, limit_top, limit_botton);
	al_draw_filled_rectangle(ball->collision_line_left(), ball->collision_line_top(), ball->collision_line_right(), ball->collision_line_botton(), ACWhite);

	// draw game score
	al_draw_textf(font, ACWhite, 2, 2, 0, "Player 1:%u - Player 2:%u", p1->get_score(), p2->get_score());
}

bool update_score(const OMBall * ball, OMPlayer * const p1, OMPlayer * const p2)
{
	//player 1 gol
	if (ball->collision_line_right() >= p2->collision_line_right())
	{
		p1->add_score();
		return true;
	}
	//player 2 gol
	else if (ball->collision_line_left() <= p1->collision_line_left())
	{
		p2->add_score();
		return true;
	}
	return false;
}

int main(int argn, char** argv)
{
	bool continue_to_play = true;
	bool draw = false;

	// Initialize the basics objects of Allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");

	// Initialize the object of Allegro that has encapsulation
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>(SCREEN_WIDTH, SCREEN_HEIGHT);
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	ALLEGRO_FONT * font = al_create_builtin_font();
	Validate::object_was_initialized(font, "Font");

	// add source to event queue
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_timer_event_source(UPATimer->getTimer()));
	al_register_event_source(UPAEventQueue->getEventQueue(), al_get_display_event_source(UPADisplay->getDisplay()));

	// color palettes
	ALLEGRO_COLOR ACBlack = al_map_rgba_f(0, 0, 0, 0);
	ALLEGRO_COLOR ACWhite = al_map_rgba_f(1, 1, 1, 1);

	//Players 
	OMPlayer p1(MARGIN_LEFT + 1, HALF_HEIGHT - (60 / 2), 10, 60, 4, 4, ALLEGRO_KEY_W, ALLEGRO_KEY_S);
	OMPlayer p2(SCREEN_WIDTH - MARGIN_RIGHT - 1, HALF_HEIGHT - (60 / 2), 10, 60, 4, 4, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN);

	//ball
	OMBall ball(HALF_WIDTH - 5, HALF_HEIGHT - 5, 10, 10, 3, 3);

	//limits
	Object limit_top(0, MARGIN_TOP + 1, SCREEN_WIDTH, HEIGHT_DIVISION);
	Object limit_botton(0, SCREEN_HEIGHT - HEIGHT_DIVISION - MARGIN_BOTTON - 1, SCREEN_WIDTH, HEIGHT_DIVISION);

	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	
	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				// Move players
				p1.move_player(key, &limit_top, &limit_botton);
				p2.move_player(key, &limit_top, &limit_botton);

				// Exist Game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				// Reset array of keys
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

		if (update_score(&ball, &p1, &p2))
		{
			p1.reset_position();
			p2.reset_position();
			ball.reset_position();
			ball.reverse_acceleration_y();
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			draw_field(&p1, &p2, &ball, &limit_top, &limit_botton, ACWhite, ACBlack, font);
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}