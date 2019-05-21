#include "OMPlayer.h"

OMPlayer::OMPlayer(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const unsigned int& btn_to_up, const unsigned int& btn_to_down)
	:OMovable(top_left_x, top_left_y, width, height, acceleration_x, acceleration_y)
{
	this->btn_to_up = std::move(btn_to_up);
	this->btn_to_down = std::move(btn_to_down);
}

OMPlayer::~OMPlayer(){}

void OMPlayer::add_score()
{
	this->score++;
}

int OMPlayer::get_score()
{
	return this->score;
}