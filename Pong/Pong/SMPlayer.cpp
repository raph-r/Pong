#include "SMPlayer.h"

SMPlayer::SMPlayer(const int& top_left_x, const unsigned int& btn_to_up, const unsigned int& btn_to_down, const char * name)
	:SMovable(top_left_x, Constant::PLAYER_POSITION_Y, Constant::PLAYER_WIDTH, Constant::PLAYER_HEIGHT, Constant::ACCELERATION, name)
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

void SMPlayer::move_player(const unsigned char * keys, const Square * upper_limit, const Square * lower_limit)
{
	if (keys[this->btn_to_up] && !this->collided_on_botton_of_other_square(upper_limit)) // upper_limit
	{
		this->up();
	}
	else if (keys[this->btn_to_down] && !this->collided_on_top_of_other_square(lower_limit)) // lower limit
	{
		this->down();
	}
}

void SMPlayer::reset()
{
	this->score = 0;
	SMovable::reset_position();
}