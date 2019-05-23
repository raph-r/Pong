#include "OMBall.h"

OMBall::OMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y)
	:OMovable(top_left_x, top_left_y, width, height, acceleration_x, acceleration_y){}

OMBall::~OMBall(){}

bool OMBall::is_player_collided_top(const OMPlayer * player)
{
	if (this->top_left_y <= player->collision_line_botton() && this->top_left_y + this->height >= player->collision_line_botton())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_botton(const OMPlayer * player)
{
	if (this->top_left_y <= player->collision_line_top() && this->top_left_y + this->height >= player->collision_line_top())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_left(const OMPlayer * player)
{
	if (this->top_left_x <= player->collision_line_right() && this->top_left_x + this->width >= player->collision_line_right())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_right(const OMPlayer * player)
{
	if (this->top_left_x <= player->collision_line_left() && this->top_left_x + this->width >= player->collision_line_left())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool OMBall::is_player_between_vertical_range(const OMPlayer * player)
{
	return (this->top_left_x <= player->collision_line_left() && this->top_left_x + width >= player->collision_line_left())
		|| (this->top_left_x >= player->collision_line_left() && this->top_left_x + this->width <= player->collision_line_right())
		|| (this->top_left_x <= player->collision_line_right() && this->top_left_x + width >= player->collision_line_right());
}

bool OMBall::is_player_between_horizontal_range(const OMPlayer * player)
{
	return (this->top_left_y <= player->collision_line_top() && this->top_left_y + this->height >= player->collision_line_top())
		|| (this->top_left_y >= player->collision_line_top() && this->top_left_y + this->height <= player->collision_line_botton())
		|| (this->top_left_y <= player->collision_line_botton() && this->top_left_y + this->height >= player->collision_line_botton());
}

void OMBall::move_ball()
{
	this->down();
	this->right();
}

void OMBall::move_ball(const OMPlayer * p1, const OMPlayer * p2, const Object * limit_top, const Object * limit_botton)
{
	if (this->is_player_collided_left(p1) || this->is_player_collided_right(p2))
	{
		this->reverse_acceleration_x();
		this->move_ball();
	}

	if (this->is_player_collided_botton(p1) || this->is_player_collided_botton(p2) || this->is_player_collided_top(p1) || this->is_player_collided_top(p2))
	{
		this->reverse_acceleration_y();
		this->move_ball();
	}
	
	if (this->top_left_y >= limit_botton->collision_line_top() || this->top_left_y <= limit_top->collision_line_botton())
	{
		this->reverse_acceleration_y();
		this->move_ball();
	}

	this->move_ball();
}