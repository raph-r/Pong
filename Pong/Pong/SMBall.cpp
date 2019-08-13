#include "SMBall.h"

SMBall::SMBall():SMovable(
	Constant::BALL_POSITION_X,
	Constant::BALL_POSITION_Y,
	Constant::BALL_WIDTH,
	Constant::BALL_HEIGHT,
	Constant::BALL_ACCELERATION_X,
	Constant::BALL_ACCELERATION_Y,
	Constant::BALL_NAME
){}

SMBall::~SMBall(){}

bool SMBall::is_player_collided_top(const SMPlayer * player)
{
	if (this->top_left_y <= player->get_botton_line() && this->top_left_y + this->height >= player->get_botton_line())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_botton(const SMPlayer * player)
{
	if (this->top_left_y <= player->get_top_line() && this->top_left_y + this->height >= player->get_top_line())
	{
		return this->is_player_between_vertical_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_left(const SMPlayer * player)
{
	if (this->top_left_x <= player->get_right_line() && this->top_left_x + this->width >= player->get_right_line())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool SMBall::is_player_collided_right(const SMPlayer * player)
{
	if (this->top_left_x <= player->get_left_line() && this->top_left_x + this->width >= player->get_left_line())
	{
		return this->is_player_between_horizontal_range(player);
	}
	return false;
}

bool SMBall::is_player_between_vertical_range(const SMPlayer * player)
{
	return (this->top_left_x <= player->get_left_line() && this->top_left_x + width >= player->get_left_line())
		|| (this->top_left_x >= player->get_left_line() && this->top_left_x + this->width <= player->get_right_line())
		|| (this->top_left_x <= player->get_right_line() && this->top_left_x + width >= player->get_right_line());
}

bool SMBall::is_player_between_horizontal_range(const SMPlayer * player)
{
	return (this->top_left_y <= player->get_top_line() && this->top_left_y + this->height >= player->get_top_line())
		|| (this->top_left_y >= player->get_top_line() && this->top_left_y + this->height <= player->get_botton_line())
		|| (this->top_left_y <= player->get_botton_line() && this->top_left_y + this->height >= player->get_botton_line());
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
		|| this->get_botton_line() >= limit_botton->get_top_line() || this->get_top_line() <= limit_top->get_botton_line()) // limit collision
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
	this->top_left_x = Constant::BALL_POSITION_X;
	this->top_left_y = Constant::BALL_POSITION_Y;
	this->acceleration_y = Constant::BALL_ACCELERATION_Y;

	if ((this->acceleration_x > 0 && this->initial_acceleration_x > 0) || (this->acceleration_x < 0 && this->initial_acceleration_x < 0))
	{
		this->acceleration_x = this->initial_acceleration_x;
	}
	else 
	{
		this->acceleration_x = (this->initial_acceleration_x * -1);
	}
}