#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "ASample.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include "SMPlayer.h"
#include "SMBall.h"
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
#define MAX_SCORE 10
#define MSG_PLAY_AGAIN "Press Space to play again!"
#define MSG_PLAY_GAME "Press Space to play"

void draw_player_winner_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& msg_top_x, const char * const winner_msg)
{
	al_draw_text(font, ACWhite, msg_top_x, (HALF_HEIGHT / 2) - MARGIN_LEFT, 0, winner_msg);
}

void draw_press_key_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& msg_top_x)
{
	al_draw_text(font, ACWhite, msg_top_x, (HALF_HEIGHT / 2) - MARGIN_LEFT + (al_get_font_line_height(font) * 2), 0, MSG_PLAY_AGAIN);
}

void draw_winner_msg(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, const int& half_width_of_winner_side, const char * const winner_msg)
{
	draw_player_winner_msg(ACWhite, font, half_width_of_winner_side - (al_get_text_width(font, winner_msg) / 2), winner_msg);
	draw_press_key_msg(ACWhite, font, half_width_of_winner_side - (al_get_text_width(font, MSG_PLAY_AGAIN) / 2));
}

void draw_field(SMPlayer * const p1, SMPlayer * const p2, SMBall * const ball, const Square * limit_top, const Square * limit_botton, const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font, bool& has_winner, ASample * const collision_sample)
{
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
	if(!has_winner)
	{
		ball->move_ball(p1, p2, limit_top, limit_botton, collision_sample);
	}
	
	al_draw_filled_rectangle(ball->collision_line_left(), ball->collision_line_top(), ball->collision_line_right(), ball->collision_line_botton(), ACWhite);

	// draw game score
	al_draw_textf(font, ACWhite, 2, 2, 0, "%s:%u - %s:%u", p1->get_name(), p1->get_score(), p2->get_name(), p2->get_score());

	// draw winner msg, if the game has a winner
	if (p1->get_score() >= MAX_SCORE)
	{
		draw_winner_msg(ACWhite, font, (HALF_WIDTH / 2), "Player 1 Win!!!");
		has_winner = true;
	}
	else if (p2->get_score() >= MAX_SCORE)
	{
		draw_winner_msg(ACWhite, font, (HALF_WIDTH + (HALF_WIDTH / 2)), "Player 2 Win!!!");
		has_winner = true;
	}
}

void draw_starter_menu(const ALLEGRO_COLOR& ACWhite, const ALLEGRO_FONT * font)
{
	al_draw_textf(font, ACWhite, HALF_WIDTH - (al_get_text_width(font, MSG_PLAY_GAME) / 2), HALF_HEIGHT - al_get_font_line_height(font) / 2, 0, MSG_PLAY_GAME);
}

bool update_score(const SMBall * ball, SMPlayer * const p1, SMPlayer * const p2)
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
	SMPlayer p1(MARGIN_LEFT + 1, HALF_HEIGHT - (60 / 2), 10, 60, 4, 4, ALLEGRO_KEY_W, ALLEGRO_KEY_S, "Player 1");
	SMPlayer p2(SCREEN_WIDTH - MARGIN_RIGHT - 1, HALF_HEIGHT - (60 / 2), 10, 60, 4, 4, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, "Player 2");

	//ball
	SMBall ball(HALF_WIDTH - 5, HALF_HEIGHT - 5, 10, 10, 3, 3, "Ball");

	//limits
	Square limit_top(0, MARGIN_TOP + 1, SCREEN_WIDTH, HEIGHT_DIVISION, "Limit Top");
	Square limit_botton(0, SCREEN_HEIGHT - HEIGHT_DIVISION - MARGIN_BOTTON - 1, SCREEN_WIDTH, HEIGHT_DIVISION, "Limit Botton");

	// Audio Sample
	al_reserve_samples(2);
	ASample collision_sample("collision.wav", ALLEGRO_PLAYMODE_ONCE);
	ASample goal_sample("goal.wav", ALLEGRO_PLAYMODE_ONCE);
	
	//captures the current event
	ALLEGRO_EVENT event;
	
	//user input
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	bool starter_menu = true;

	UPATimer->startTimer();
	while (continue_to_play)
	{
		al_wait_for_event(UPAEventQueue->getEventQueue(), &event);

		switch (event.type)
		{
			case ALLEGRO_EVENT_TIMER:
				// Move players
				if (!has_winner)
				{
					p1.move_player(key, &limit_top, &limit_botton);
					p2.move_player(key, &limit_top, &limit_botton);
				}

				// Exist Game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				// reload game, if it has a winner and space bar is pressed
				if (has_winner && key[ALLEGRO_KEY_SPACE])
				{
					has_winner = false;
					p1.reset_score();
					p2.reset_score();
					ball.reverse_acceleration_x();
				}
				//starter menu
				else if (starter_menu && key[ALLEGRO_KEY_SPACE])
				{
					starter_menu = false;
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
			goal_sample.play_sample();
			p1.reset_position();
			p2.reset_position();
			ball.reset_position();
		}

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			al_clear_to_color(ACBlack);
			if (starter_menu)
			{
				draw_starter_menu(ACWhite, font);
			}
			else
			{
				draw_field(&p1, &p2, &ball, &limit_top, &limit_botton, ACWhite, font, has_winner, &collision_sample);
			}
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}