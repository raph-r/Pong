#include "Ball.h"

Ball::Ball(const int& width, const int& height, const int& top_left_x, const int& top_left_y, const int& acceleration_x, const int& acceleration_y)
{
	this->width = width;
	this->height = height;
	this->top_left_x = top_left_x;
	this->top_left_y = top_left_y;
	this->acceleration_x = acceleration_x;
	this->acceleration_y = acceleration_y;
	this->initial_position_x = this->top_left_x;
	this->initial_position_y = this->top_left_y;
}

Ball::~Ball(){}

void Ball::reset_position()
{
	this->top_left_x = this->initial_position_x;
	this->top_left_y = this->initial_position_y;
}

void Ball::move_ball(const int& height_division, const OMPlayer * p1, const OMPlayer * p2)
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

void Ball::change_acceleration_x()
{
	this->acceleration_x *= -1;
}

void Ball::change_acceleration_y()
{
	this->acceleration_y *= -1;
}

void Ball::simple_move()
{
	this->top_left_y += this->acceleration_y;
	this->top_left_x += this->acceleration_x;
}

bool Ball::is_collided_top(const OMPlayer * player)
{
	if (this->top_left_y <= player->botton_collision_line() && this->top_left_y + this->height >= player->botton_collision_line())
	{
		return this->is_between_vertical_range(player);
	}
	return false;
}

bool Ball::is_collided_botton(const OMPlayer * player)
{
	if (this->top_left_y <= player->top_collision_line() && this->top_left_y + this->height >= player->top_collision_line())
	{
		return this->is_between_vertical_range(player);
	}
	return false;
}

bool Ball::is_collided_left(const OMPlayer * player)
{
	if (this->top_left_x <= player->right_collision_line() && this->top_left_x + this->width >= player->right_collision_line())
	{
		return this->is_between_horizontal_range(player);
	}
	return false;
}

bool Ball::is_collided_right(const OMPlayer * player)
{
	if (this->top_left_x <= player->left_collision_line() && this->top_left_x + this->width >= player->left_collision_line())
	{
		return this->is_between_horizontal_range(player);
	}
	return false;
}

bool Ball::is_between_vertical_range(const OMPlayer * player)
{
	return (this->top_left_x <= player->left_collision_line() && this->top_left_x + width >= player->left_collision_line())
		|| (this->top_left_x >= player->left_collision_line() && this->top_left_x + this->width <= player->right_collision_line())
		|| (this->top_left_x <= player->right_collision_line() && this->top_left_x + width >= player->right_collision_line());
}

bool Ball::is_between_horizontal_range(const OMPlayer * player)
{
	return (this->top_left_y <= player->top_collision_line() && this->top_left_y + this->height >= player->top_collision_line())
		|| (this->top_left_y >= player->top_collision_line() && this->top_left_y + this->height <= player->botton_collision_line())
		|| (this->top_left_y <= player->botton_collision_line() && this->top_left_y + this->height >= player->botton_collision_line());
}

int Ball::top_collision_line()
{
	return this->top_left_y;
}

int Ball::botton_collision_line()
{
	return this->top_left_y + this->height;
}

int Ball::left_collision_line()
{
	return this->top_left_x;
}

int Ball::right_collision_line()
{
	return this->top_left_x + this->width;
}