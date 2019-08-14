#include "SMPlayer.h"

SMPlayer::SMPlayer(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const unsigned int& btn_to_up, const unsigned int& btn_to_down, const char * name)
	:SMovable(top_left_x, top_left_y, width, height, acceleration_x, name)
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
	if (keys[this->btn_to_up] && this->get_top_line() > limit_top->get_botton_line()) // limite superior
	{
		this->up();
	}
	if (keys[this->btn_to_down] && this->get_botton_line() < limit_botton->get_top_line()) // limite inferior
	{
		this->down();
	}
}

void SMPlayer::reset_score()
{
	this->score = 0;
}