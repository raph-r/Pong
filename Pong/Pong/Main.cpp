#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "ASample.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include "SMPlayer.h"
#include "SMBall.h"

void draw_player_winner_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& msg_top_x, const char * const winner_msg)
{
	al_draw_text(font, ACWhite, msg_top_x, (Constant::HALF_SCREEN_HEIGHT / 2) - Constant::HORIZONTAL_MARGIN, 0, winner_msg);
}

void draw_press_key_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& msg_top_x)
{
	al_draw_text(font, ACWhite, msg_top_x, (Constant::HALF_SCREEN_HEIGHT / 2) - Constant::HORIZONTAL_MARGIN + (al_get_font_line_height(font) * 2), 0, Constant::MSG_PLAY_AGAIN);
}

void draw_winner_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& half_width_of_winner_side, const char * const winner_msg)
{
	draw_player_winner_msg(ACWhite, font, half_width_of_winner_side - (al_get_text_width(font, winner_msg) / 2), winner_msg);
	draw_press_key_msg(ACWhite, font, half_width_of_winner_side - (al_get_text_width(font, Constant::MSG_PLAY_AGAIN) / 2));
}

void draw_objects(SMPlayer * p1, SMPlayer * p2, SMBall * ball, Square * upper_limit, Square * lower_limit, ALLEGRO_COLOR * ACWhite, ALLEGRO_FONT * font)
{
	upper_limit->draw(ACWhite);
	lower_limit->draw(ACWhite);
	p1->draw(ACWhite);
	p2->draw(ACWhite);
	ball->draw(ACWhite);

	// Division line
	for (unsigned int i = 2; i < 20; i++)
	{
		al_draw_filled_rectangle(Constant::HALF_SCREEN_WIDTH - 2, (i * Constant::HEIGHT_DIVISION), Constant::HALF_SCREEN_WIDTH + 2, ((i++) * Constant::HEIGHT_DIVISION), *ACWhite);
	}

	// draw game score
	al_draw_textf(font, *ACWhite, 2, 2, 0, "%s:%u - %s:%u", p1->get_name(), p1->get_score(), p2->get_name(), p2->get_score());
}

void draw_starter_menu(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font)
{
	al_draw_textf(font, ACWhite, Constant::HALF_SCREEN_WIDTH - (al_get_text_width(font, Constant::MSG_PLAY_GAME) / 2), Constant::HALF_SCREEN_HEIGHT - al_get_font_line_height(font) / 2, 0, Constant::MSG_PLAY_GAME);
}

bool update_score(const SMBall * ball, SMPlayer * const p1, SMPlayer * const p2)
{
	//player 1 gol
	if (ball->get_right_line() >= p2->get_right_line())
	{
		p1->add_score();
		return true;
	}
	//player 2 gol
	else if (ball->get_left_line() <= p1->get_left_line())
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
	bool has_winner = false;

	// Initialize the basics objects of Allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_install_audio(), "Audio");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");
	Validate::object_was_initialized(al_init_acodec_addon(), "Allegro Codec");

	// Initialize the object of Allegro that has encapsulation
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>();
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
	SMPlayer p1(Constant::PLAYER_1_POSITION_X, ALLEGRO_KEY_W, ALLEGRO_KEY_S, "Player 1");
	SMPlayer p2(Constant::PLAYER_2_POSITION_X, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, "Player 2");

	//ball
	SMBall ball;

	//limits
	Square limit_top(0, Constant::VERTICAL_MARGIN, Constant::SCREEN_WIDTH, Constant::HEIGHT_DIVISION, "Upper limit");
	Square limit_botton(0, Constant::SCREEN_HEIGHT - Constant::HEIGHT_DIVISION - Constant::VERTICAL_MARGIN, Constant::SCREEN_WIDTH, Constant::HEIGHT_DIVISION, "Lower limit");

	// Audio Sample
	al_reserve_samples(2);
	ASample collision_sample("collision.wav", ALLEGRO_PLAYMODE_ONCE);
	ASample goal_sample("goal.wav", ALLEGRO_PLAYMODE_ONCE);
	
	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	int scene = 1;

	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				// Exist Game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				if (scene == 2)
				{
					// Move players
					if (!has_winner)
					{
						p1.move_player(key, &limit_top, &limit_botton);
						p2.move_player(key, &limit_top, &limit_botton);
						ball.move_ball(&p1, &p2, &limit_top, &limit_botton, &collision_sample);
					}
					// reload game, if it has a winner and space bar is pressed
					else if (key[ALLEGRO_KEY_SPACE])
					{
						has_winner = false;
						p1.reset();
						p2.reset();
						ball.inverts_horizontal_direction();
					}
				}
				else if (scene == 1 && key[ALLEGRO_KEY_SPACE])
				{
					scene++;
				}

				// Reset array of keys
				for (unsigned int i = 0; i < ALLEGRO_KEY_MAX; i++)
				{
					key[i] &= Constant::KEY_SEEN;
				}

				draw = true;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				key[event.keyboard.keycode] = Constant::KEY_SEEN | Constant::KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_KEY_UP:
				key[event.keyboard.keycode] &= Constant::KEY_RELEASED;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				continue_to_play = false;
				break;
			default:
				break;
		}

		if (update_score(&ball, &p1, &p2))
		{
			goal_sample.play_sample();
			p1.reset_position();
			p2.reset_position();
			ball.reset();
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			al_clear_to_color(ACBlack);
			
			if(scene == 2)
			{
				draw_objects(&p1, &p2, &ball, &limit_top, &limit_botton, &ACWhite, font);

				// draw winner msg, if the game has a winner
				if (p1.get_score() >= Constant::MAX_SCORE)
				{
					draw_winner_msg(ACWhite, font, (Constant::Constant::HALF_SCREEN_WIDTH / 2), "Player 1 Win!!!");
					has_winner = true;
				}
				else if (p2.get_score() >= Constant::MAX_SCORE)
				{
					draw_winner_msg(ACWhite, font, (Constant::HALF_SCREEN_WIDTH + (Constant::HALF_SCREEN_WIDTH / 2)), "Player 2 Win!!!");
					has_winner = true;
				}
			}
			else if (scene == 1)
			{
				draw_starter_menu(ACWhite, font);
			}

			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}