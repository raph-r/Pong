#pragma once
#include "SMovable.h"
#include "SMPlayer.h"
#include "ASample.h"

class SMBall :
	public SMovable
{
private:

	unsigned int hits = 0;
	bool is_player_between_vertical_range(const SMPlayer * player);
	bool is_player_between_horizontal_range(const SMPlayer * player);
	bool is_player_collided_top(const SMPlayer * player);
	bool is_player_collided_botton(const SMPlayer * player);
	bool is_player_collided_left(const SMPlayer * player);
	bool is_player_collided_right(const SMPlayer * player);
	void move_ball();
	void try_increase_speed(SMPlayer * const p1, SMPlayer * const p2);

public:

	SMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const char * name);
	~SMBall();
	void move_ball(SMPlayer * const p1, SMPlayer * const p2, const Square * limit_top, const Square * limit_botton, ASample * const sample);
	void reset_position();
};

