#include "OMBall.h"

OMBall::OMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y)
	:OMovable(top_left_x, top_left_y, width, height, acceleration_x, acceleration_y){}

OMBall::~OMBall(){}

bool OMBall::is_player_collided_top(const OMPlayer * player)
{
	if (this->top_left_y <= player->botton_collision_line() && this->top_left_y + this->height >= player->botton_collision_line())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_botton(const OMPlayer * player)
{
	if (this->top_left_y <= player->top_collision_line() && this->top_left_y + this->height >= player->top_collision_line())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_left(const OMPlayer * player)
{
	if (this->top_left_x <= player->right_collision_line() && this->top_left_x + this->width >= player->right_collision_line())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool OMBall::is_player_collided_right(const OMPlayer * player)
{
	if (this->top_left_x <= player->left_collision_line() && this->top_left_x + this->width >= player->left_collision_line())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool OMBall::is_player_between_vertical_range(const OMPlayer * player)
{
	return (this->top_left_x <= player->left_collision_line() && this->top_left_x + width >= player->left_collision_line())
		|| (this->top_left_x >= player->left_collision_line() && this->top_left_x + this->width <= player->right_collision_line())
		|| (this->top_left_x <= player->right_collision_line() && this->top_left_x + width >= player->right_collision_line());
}

bool OMBall::is_player_between_horizontal_range(const OMPlayer * player)
{
	return (this->top_left_y <= player->top_collision_line() && this->top_left_y + this->height >= player->top_collision_line())
		|| (this->top_left_y >= player->top_collision_line() && this->top_left_y + this->height <= player->botton_collision_line())
		|| (this->top_left_y <= player->botton_collision_line() && this->top_left_y + this->height >= player->botton_collision_line());
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
	
	if (this->top_left_y >= limit_botton->top_collision_line() || this->top_left_y <= limit_top->botton_collision_line())
	{
		this->reverse_acceleration_y();
		this->move_ball();
	}

	this->move_ball();
}