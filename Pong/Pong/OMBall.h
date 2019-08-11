#pragma once
#include "OMovable.h"
#include "OMPlayer.h"
#include "ASample.h"

class OMBall :
	public OMovable
{
private:

	unsigned int hits = 0;
	bool is_player_between_vertical_range(const OMPlayer * player);
	bool is_player_between_horizontal_range(const OMPlayer * player);
	bool is_player_collided_top(const OMPlayer * player);
	bool is_player_collided_botton(const OMPlayer * player);
	bool is_player_collided_left(const OMPlayer * player);
	bool is_player_collided_right(const OMPlayer * player);
	void move_ball();
	void try_increase_speed(OMPlayer * const p1, OMPlayer * const p2);

public:

	OMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const char * name);
	~OMBall();
	void move_ball(OMPlayer * const p1, OMPlayer * const p2, const Square * limit_top, const Square * limit_botton, ASample * const sample);
	void reset_position();
};

