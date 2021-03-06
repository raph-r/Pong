#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "ASample.h"
#include "ATTFFont.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include "SMPlayer.h"
#include "SMBall.h"

/**
 * <EN>
 * Draws the winner's message
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 * @param[in] winner_msg - msg that will be draw
 * @param[in] middle_of_winner_side - Position X, that represents the middle of winner's side
 *
 * <PT-Br>
 * Desenha a mensagem de ganhador
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para a escrita
 * @param[in] winner_msg - mensagem que ser� desenhada
 * @param[in] middle_of_winner_side - Posicao X, que representa o meio do lado do vencedor
*/
void draw_winner_msg(ALLEGRO_COLOR * color, const std::shared_ptr<const ATTFFont> font, const char * const winner_msg, const int & middle_of_winner_side)
{
	al_draw_textf(font->getFont(), *color, middle_of_winner_side, Constant::HALF_SCREEN_HEIGHT - al_get_font_line_height(font->getFont()), ALLEGRO_ALIGN_CENTER, winner_msg);
	al_draw_textf( font->getFont(), *color, middle_of_winner_side, Constant::HALF_SCREEN_HEIGHT, ALLEGRO_ALIGN_CENTER, Constant::MSG_PLAY_AGAIN);
}

/**
 * <EN>
 * Draws all objects of game. Including game score
 * @param[in] p1 - Pointer to Player 1
 * @param[in] p2 - Pointer to Player 2
 * @param[in] ball - SMBall that represents the ball of game
 * @param[in] upper_limit - Pointer to Object that represents the top limit of screen
 * @param[in] lower_limit - Pointer to Object that represents the botton limit of screen
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 *
 * <PT-Br>
 * Desenha todos os objetos do jogo. Incluindo o placar do jogo
 * @param[in] p1 - Ponteiro para Player 1
 * @param[in] p2 - Ponteiro para Player 2
 * @param[in] ball - SMBall que representa a bola do jogo
 * @param[in] upper_limit - Ponteiro para o objeto que representa o limite superior da tela
 * @param[in] lower_limit - Ponteiro para o objeto que representa o limite inferior da tela
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para a escrita
*/
void draw_objects(SMPlayer * p1, SMPlayer * p2, SMBall * ball, Square * upper_limit, Square * lower_limit, ALLEGRO_COLOR * color, const std::shared_ptr<const ATTFFont> font)
{
	upper_limit->draw(color);
	lower_limit->draw(color);
	p1->draw(color);
	p2->draw(color);
	ball->draw(color);

	// Division line
	for (unsigned int i = 2; i < 20; i++)
	{
		al_draw_filled_rectangle(Constant::HALF_SCREEN_WIDTH - 2, (i * Constant::HEIGHT_DIVISION), Constant::HALF_SCREEN_WIDTH + 2, ((i++) * Constant::HEIGHT_DIVISION), *color);
	}

	// draw game score
	al_draw_textf(font->getFont(), *color, Constant::HALF_SCREEN_WIDTH - 60, 60 - (al_get_font_line_height(font->getFont()) / 2), ALLEGRO_ALIGN_CENTER, "%u", p1->get_score());
	al_draw_textf(font->getFont(), *color, Constant::HALF_SCREEN_WIDTH + 60, 60 - (al_get_font_line_height(font->getFont()) / 2), ALLEGRO_ALIGN_CENTER, "%u", p2->get_score());
}

/**
 * <EN>
 * Draw the initial scene of game
 * @param[in] color - Color that will be used to draw
 * @param[in] font - ATTFFont that will be used to draw
 *
 * <PT-Br>
 * Desenha a cena inicial do jogo
 * @param[in] color - Cor que devera ser utilizada para desenhar
 * @param[in] font - ATTFFont que sera utilizada para desenhar
*/
void draw_initial_scene(const ALLEGRO_COLOR& color, const std::shared_ptr<const ATTFFont> font)
{
	al_draw_textf(font->getFont(), color, Constant::HALF_SCREEN_WIDTH, Constant::HALF_SCREEN_HEIGHT - (al_get_font_line_height(font->getFont()) / 2), ALLEGRO_ALIGN_CENTER, Constant::MSG_PLAY_GAME);
}

/**
 * <EN>
 * Verify if someone scored and add a point for who scored
 * @param[in] ball - SMBall that represents the ball of game
 * @param[in] p1 - Pointer to Player 1
 * @param[in] p2 - Pointer to Player 2
 * @return True if someone scored. Otherwise false
 *
 * <PT-Br>
 * Verifica se foi efetuado algum gol no jogo e adiciona o ponto ao marcador
 * @param[in] ball - SMBall que representa a bola do jogo
 * @param[in] p1 - Ponteiro para Player 1
 * @param[in] p2 - Ponteiro para Player 2
 * @return True caso tenha sido efetuado um gol. Caso contrario False
*/
bool update_score(const SMBall * ball, SMPlayer * const p1, SMPlayer * const p2)
{
	//Player 1 goal
	if (ball->pos_is_between_horizontal_borders(Constant::SCREEN_WIDTH - Constant::HORIZONTAL_MARGIN))
	{
		p1->add_score();
		return true;
	}
	//Player 2 goal
	else if (ball->pos_is_between_horizontal_borders(Constant::HORIZONTAL_MARGIN))
	{
		p2->add_score();
		return true;
	}
	return false;
}

int main(int argn, char** argv)
{
	int scene = 1;
	bool continue_to_play = true;
	bool draw = false;
	bool p1_winner = false;
	bool p2_winner = false;

	// Initialize the basics objects of Allegro
	Validate::object_was_initialized(al_init(), "Allegro");
	Validate::object_was_initialized(al_install_keyboard(), "Keyboard");
	Validate::object_was_initialized(al_install_audio(), "Audio");
	Validate::object_was_initialized(al_init_font_addon(), "Font Addon");
	Validate::object_was_initialized(al_init_ttf_addon(), "Font TTF Addon");
	Validate::object_was_initialized(al_init_primitives_addon(), "Primitives");
	Validate::object_was_initialized(al_init_acodec_addon(), "Allegro Codec");

	// Initialize the object of Allegro that has encapsulation
	std::unique_ptr<ATimer> UPATimer = std::make_unique<ATimer>(1.0 / 60);
	std::unique_ptr<ADisplay> UPADisplay = std::make_unique<ADisplay>();
	std::unique_ptr<AEventQueue> UPAEventQueue = std::make_unique<AEventQueue>();
	std::shared_ptr<ATTFFont> SPFont_24 = std::make_shared<ATTFFont>("Oswald-Medium.ttf", 24);
	std::shared_ptr<ATTFFont> SPFont_18 = std::make_shared<ATTFFont>("Oswald-Medium.ttf", 18);

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
	Square upper_limit(0, Constant::VERTICAL_MARGIN, Constant::SCREEN_WIDTH, Constant::HEIGHT_DIVISION, "Upper limit");
	Square lower_limit(0, Constant::SCREEN_HEIGHT - Constant::HEIGHT_DIVISION - Constant::VERTICAL_MARGIN, Constant::SCREEN_WIDTH, Constant::HEIGHT_DIVISION, "Lower limit");

	// Audio Sample
	al_reserve_samples(2);
	ASample collision_sample("collision.wav", ALLEGRO_PLAYMODE_ONCE);
	ASample goal_sample("goal.wav", ALLEGRO_PLAYMODE_ONCE);
	
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
				// Exit Game
				if (key[ALLEGRO_KEY_ESCAPE])
				{
					continue_to_play = false;
				}

				// Scene loop
				if (scene == 2)
				{
					if (!p1_winner && !p2_winner)
					{
						// verify if has a winner
						if (p1.get_score() >= Constant::MAX_SCORE)
						{
							p1_winner = true;
						}
						else if (p2.get_score() >= Constant::MAX_SCORE)
						{
							p2_winner = true;
						}
						else
						{
							// Move objects
							p1.move_player(key, &upper_limit, &lower_limit);
							p2.move_player(key, &upper_limit, &lower_limit);
							ball.move_ball(&p1, &p2, &upper_limit, &lower_limit, &collision_sample);

							// Update game score
							if (update_score(&ball, &p1, &p2))
							{
								goal_sample.play_sample();
								p1.reset_position();
								p2.reset_position();
								ball.reset();
							}
						}
					}
					// reload game, if it has a winner and space bar is pressed
					else if (key[ALLEGRO_KEY_SPACE])
					{
						p1_winner = false;
						p2_winner = false;
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

		if (draw && al_is_event_queue_empty(UPAEventQueue->getEventQueue()))
		{
			draw = false;
			al_clear_to_color(ACBlack);
			
			// Draw second scene
			if(scene == 2)
			{
				draw_objects(&p1, &p2, &ball, &upper_limit, &lower_limit, &ACWhite, SPFont_24);
				// if has a winner, draw msg
				if (p1_winner)
				{
					draw_winner_msg(&ACWhite, SPFont_18, Constant::WINNER_MSG_P1, Constant::HALF_OF_SIDE_PLAYER_1);
				}
				else if (p2_winner)
				{
					draw_winner_msg(&ACWhite, SPFont_18, Constant::WINNER_MSG_P2, Constant::HALF_OF_SIDE_PLAYER_2);
				}
			}
			// Draw first scene
			else if (scene == 1)
			{
				draw_initial_scene(ACWhite, SPFont_24);
			}

			al_flip_display();
		}
	}
	return 0;
}