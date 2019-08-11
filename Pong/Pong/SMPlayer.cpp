#include "SMPlayer.h"

SMPlayer::SMPlayer(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const unsigned int& btn_to_up, const unsigned int& btn_to_down, const char * name)
	:SMovable(top_left_x, top_left_y, width, height, acceleration_x, acceleration_y, name)
{
	this->btn_to_up = std::move(btn_to_up);
	this->btn_to_down = std::move(btn_to_down);
}

SMPlayer::~SMPlayer(){}

void SMPlayer::add_score()
{
	this->score++;
}

int SMPlayer::get_score() const
{
	return this->score;
}

void SMPlayer::move_player(const unsigned char * keys, const Square * limit_top, const Square * limit_botton)
{
	if (keys[this->btn_to_up] && this->collision_line_top() > limit_top->collision_line_botton()) // limite superior
	{
		this->up();
	}
	if (keys[this->btn_to_down] && this->collision_line_botton() < limit_botton->collision_line_top()) // limite inferior
	{
		this->down();
	}
}

void SMPlayer::reset_score()
{
	this->score = 0;
}