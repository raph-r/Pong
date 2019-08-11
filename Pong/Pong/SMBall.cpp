#include "SMBall.h"

SMBall::SMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const char * name)
	:SMovable(top_left_x, top_left_y, width, height, acceleration_x, acceleration_y, name){}

SMBall::~SMBall(){}

bool SMBall::is_player_collided_top(const SMPlayer * player)
{
	if (this->top_left_y <= player->collision_line_botton() && this->top_left_y + this->height >= player->collision_line_botton())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_botton(const SMPlayer * player)
{
	if (this->top_left_y <= player->collision_line_top() && this->top_left_y + this->height >= player->collision_line_top())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_left(const SMPlayer * player)
{
	if (this->top_left_x <= player->collision_line_right() && this->top_left_x + this->width >= player->collision_line_right())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_right(const SMPlayer * player)
{
	if (this->top_left_x <= player->collision_line_left() && this->top_left_x + this->width >= player->collision_line_left())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool SMBall::is_player_between_vertical_range(const SMPlayer * player)
{
	return (this->top_left_x <= player->collision_line_left() && this->top_left_x + width >= player->collision_line_left())
		|| (this->top_left_x >= player->collision_line_left() && this->top_left_x + this->width <= player->collision_line_right())
		|| (this->top_left_x <= player->collision_line_right() && this->top_left_x + width >= player->collision_line_right());
}

bool SMBall::is_player_between_horizontal_range(const SMPlayer * player)
{
	return (this->top_left_y <= player->collision_line_top() && this->top_left_y + this->height >= player->collision_line_top())
		|| (this->top_left_y >= player->collision_line_top() && this->top_left_y + this->height <= player->collision_line_botton())
		|| (this->top_left_y <= player->collision_line_botton() && this->top_left_y + this->height >= player->collision_line_botton());
}

void SMBall::move_ball()
{
	this->down();
	this->right();
}

void SMBall::move_ball(SMPlayer * const p1, SMPlayer * const p2, const Square * limit_top, const Square * limit_botton, ASample * const sample)
{
	if (this->is_player_collided_left(p1) || this->is_player_collided_right(p2))
	{
		sample->play_sample();
		this->try_increase_speed(p1, p2);
		this->reverse_acceleration_x();
		this->move_ball();
	}

	
	if (this->is_player_collided_botton(p1) || this->is_player_collided_botton(p2) || this->is_player_collided_top(p1) || this->is_player_collided_top(p2) // player collision
		|| this->collision_line_botton() >= limit_botton->collision_line_top() || this->collision_line_top() <= limit_top->collision_line_botton()) // limit collision
	{
		sample->play_sample();
		this->try_increase_speed(p1, p2);
		this->reverse_acceleration_y();
		this->move_ball();
	}
	
	this->move_ball();
}

void SMBall::try_increase_speed(SMPlayer * const p1, SMPlayer * const p2)
{
	if (++this->hits >= 4)
	{
		if (this->acceleration_x > 0)
		{
			this->add_acceleration_x();
		}
		else
		{
			this->subtract_acceleration_x();
		}

		if (this->acceleration_y > 0)
		{
			this->add_acceleration_y();
		}
		else
		{
			this->subtract_acceleration_y();
		}
		this->hits = 0;
		
		// add player acceleration
		p1->add_acceleration_y();
		p2->add_acceleration_y();
	}
}

void SMBall::reset_position()
{
	this->hits = 0;
	this->top_left_x = this->initial_position_x;
	this->top_left_y = this->initial_position_y;
	this->acceleration_y = this->initial_acceleration_y;

	if ((this->acceleration_x > 0 && this->initial_acceleration_x > 0) || (this->acceleration_x < 0 && this->initial_acceleration_x < 0))
	{
		this->acceleration_x = this->initial_acceleration_x;
	}
	else 
	{
		this->acceleration_x = (this->initial_acceleration_x * -1);
	}
}