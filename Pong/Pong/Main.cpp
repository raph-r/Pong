#include "ATimer.h"
#include "ADisplay.h"
#include "AEventQueue.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include <memory>
#include <iostream>
#define KEY_SEEN 1
#define KEY_RELEASED 2
#define MARGIN_TOP 10
#define MARGIN_BOTTON 10
#define MARGIN_LEFT 30
#define MARGIN_RIGHT 30
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


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

struct Block
{
	int width = 0;
	int height = 0;

	Block(const int& width, const int& height)
	{
		this->width = width;
		this->height = height;
	}
};

struct Player
{
	unsigned int btn_to_up = 0;
	unsigned int btn_to_down = 0;
	unsigned int score = 0;
	int top_left_x = 0;
	int top_left_y = 0;
	int width = 0;
	int height = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;

	Player(const int& btn_to_up, const int& btn_to_down, const int& top_left_x, const int& width,const int& height, const int& score)
	{
		this->top_left_x = top_left_x;
		this->top_left_y = (SCREEN_HEIGHT / 2) - (height / 2);
		this->width = width;
		this->height = height;
		this->btn_to_up = btn_to_up;
		this->btn_to_down = btn_to_down;
		this->score = score;
		this->initial_position_x = this->top_left_x;
		this->initial_position_y = this->top_left_y;
	}

	void reset_position()
	{
		this->top_left_x = this->initial_position_x;
		this->top_left_y = this->initial_position_y;
	}

	int horizontal_top_collision_line() const
	{
		return this->top_left_y;
	}
	int horizontal_botton_collision_line() const
	{
		return this->top_left_y + this->height;
	}
	int vertical_left_collision_line() const
	{
		return this->top_left_x;
	}
	int vertical_right_collision_line() const
	{
		return this->top_left_x + this->width;
	}
};

struct Ball
{
	int acceleration_x = 0;
	int acceleration_y = 0;
	int width = 0;
	int height = 0;
	int top_left_x = 0;
	int top_left_y = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;

	Ball(const int& width, const int& height, const int& top_left_x, const int& top_left_y, const int& acceleration_x, const int& acceleration_y)
	{
		this->width = width;
		this->height = height;
		this->top_left_x = top_left_x;
		this->top_left_y = top_left_y;
		this->acceleration_x = acceleration_x;
		this->acceleration_y = acceleration_y;
		initial_position_x = this->top_left_x;
		initial_position_y = this->top_left_y;
	}

	void reset_position()
	{
		this->top_left_x = this->initial_position_x;
		this->top_left_y = this->initial_position_y;
	}

	void move_ball(const int& height_division, const Player * p1, const Player * p2)
	{
		if (this->is_collided_left(p1) || this->is_collided_right(p2))
		{
			this->change_acceleration_x();
			this->simple_move();
		}

		if (this->is_collided_botton(p1) || this->is_collided_botton(p2) || this->is_collided_top(p1) || this->is_collided_top(p2))
		{
			this->change_acceleration_y();
			this->simple_move();
		}
		
		if (this->top_left_y >= SCREEN_HEIGHT - MARGIN_TOP - height_division - this->height || this->top_left_y <= MARGIN_TOP + height_division)
		{
			this->change_acceleration_y();
			this->simple_move();
		}

		this->simple_move();
	}

	void change_acceleration_x()
	{
		this->acceleration_x *= -1;
	}

	void change_acceleration_y()
	{
		this->acceleration_y *= -1;
	}

	void simple_move()
	{
		this->top_left_y += this->acceleration_y;
		this->top_left_x += this->acceleration_x;
	}

	bool is_collided_top(const Player * player)
	{
		if (this->top_left_y <= player->horizontal_botton_collision_line() && this->top_left_y + this->height >= player->horizontal_botton_collision_line())
		{
			return this->is_between_vertical_range(player);
		}
		return false;
	}

	bool is_collided_botton(const Player * player)
	{
		if (this->top_left_y <= player->horizontal_top_collision_line() && this->top_left_y + this->height >= player->horizontal_top_collision_line())
		{
			return this->is_between_vertical_range(player);
		}
		return false;
	}

	bool is_collided_left(const Player * player)
	{
		if (this->top_left_x <= player->vertical_right_collision_line() && this->top_left_x + this->width >= player->vertical_right_collision_line())
		{
			return this->is_between_horizontal_range(player);
		}
		return false;
	}

	bool is_collided_right(const Player * player)
	{
		if (this->top_left_x <= player->vertical_left_collision_line() && this->top_left_x + this->width >= player->vertical_left_collision_line())
		{
			return this->is_between_horizontal_range(player);
		}
		return false;
	}

	bool is_between_vertical_range(const Player * player)
	{
		return (this->top_left_x <= player->vertical_left_collision_line() && this->top_left_x + width >= player->vertical_left_collision_line())
			|| (this->top_left_x >= player->vertical_left_collision_line() && this->top_left_x + this->width <= player->vertical_right_collision_line())
			|| (this->top_left_x <= player->vertical_right_collision_line() && this->top_left_x + width >= player->vertical_right_collision_line());
	}

	bool is_between_horizontal_range(const Player * player)
	{
		return (this->top_left_y <= player->horizontal_top_collision_line() && this->top_left_y + this->height >= player->horizontal_top_collision_line())
			|| (this->top_left_y >= player->horizontal_top_collision_line() && this->top_left_y + this->height <= player->horizontal_botton_collision_line())
			|| (this->top_left_y <= player->horizontal_botton_collision_line() && this->top_left_y + this->height >= player->horizontal_botton_collision_line());
	}
};

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
				if (key[ALLEGRO_KEY_W] && p1.top_left_y > height_division) // limite superior
				{
					p1.top_left_y -= 4;
				}
				if (key[ALLEGRO_KEY_S] && p1.top_left_y < (SCREEN_HEIGHT - p1.height - height_division)) // limite inferior
				{
					p1.top_left_y += 4;
				}

				// move player 2
				if (key[ALLEGRO_KEY_UP] && p2.top_left_y > height_division) // limite superior
				{
					p2.top_left_y -= 4;
				}
				if (key[ALLEGRO_KEY_DOWN] && p2.top_left_y < (SCREEN_HEIGHT - p2.height - height_division)) // limite inferior
				{
					p2.top_left_y += 4;
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
		if (ball.top_left_x >= p2.vertical_right_collision_line())
		{
			p1.score++;
			reset_objects_position = true;
		}
		//player 2 gol
		else if (ball.top_left_x + ball.width <= p1.vertical_left_collision_line())
		{
			p2.score++;
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
				p1.top_left_x,
				p1.top_left_y,
				p1.top_left_x + p1.width,
				p1.top_left_y + p1.height,
				ACWhite
			);

			//draw player2 (right player)
			al_draw_filled_rectangle(
				p2.top_left_x,
				p2.top_left_y,
				p2.top_left_x + p2.width,
				p2.top_left_y + p2.height,
				ACWhite
			);

			//draw ball
			ball.move_ball(height_division, &p1, &p2);
			al_draw_filled_rectangle(
				ball.top_left_x,
				ball.top_left_y,
				ball.top_left_x + ball.width, 
				ball.top_left_y + ball.height,
				ACWhite
			);

			al_draw_textf(font, ACWhite, 2, 2, 0, "Player 1:%u - Player 2:%u", p1.score, p2.score);
			
			draw_field(height_division, ACWhite);
			al_flip_display();
		}
	}
	al_destroy_font(font);
	return 0;
}