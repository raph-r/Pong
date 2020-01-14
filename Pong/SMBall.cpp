#include "SMBall.h"

SMBall::SMBall():SMovable(
	Constant::BALL_POSITION_X,
	Constant::BALL_POSITION_Y,
	Constant::BALL_WIDTH,
	Constant::BALL_HEIGHT,
	Constant::ACCELERATION,
	Constant::BALL_NAME
){}

SMBall::~SMBall(){}

void SMBall::move_ball()
{
	if (this->to_right)
	{
		this->right();
	}
	else
	{
		this->left();
	}

	if (this->to_down)
	{
		this->down();
	}
	else
	{
		this->up();
	}
}

void SMBall::move_ball(SMPlayer * const p1, SMPlayer * const p2, Square const * const upper_limit, Square const * const lower_limit, ASample const * const sample)
{
	// player collision
	if (this->collided_on_right_of_other_square(p1) || this->collided_on_left_of_other_square(p2))
	{
		this->inverts_horizontal_direction();
		sample->play_sample();
		this->try_increase_speed(p1, p2);
	}
	
	// square limits collision
	if (this->collided_on_top_of_other_square(lower_limit) || this->collided_on_botton_of_other_square(upper_limit))
	{
		this->inverts_vertical_direction();
		sample->play_sample();
		this->try_increase_speed(p1, p2);
	}
	
	this->move_ball();
}

void SMBall::try_increase_speed(SMPlayer * const p1, SMPlayer * const p2)
{
	if (++this->hits >= 4)
	{
		this->acceleration++;
		this->hits = std::move(0);

		// add player acceleration
		p1->add_acceleration();
		p2->add_acceleration();
	}
}

void SMBall::reset()
{
	this->hits = std::move(0);
	SMovable::reset_position();
}

void SMBall::inverts_horizontal_direction()
{
	this->to_right = std::move(!this->to_right);
}

void SMBall::inverts_vertical_direction()
{
	this->to_down = std::move(!this->to_down);
}