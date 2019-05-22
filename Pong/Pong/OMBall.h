#pragma once
#include "OMovable.h"
#include "OMPlayer.h"

class OMBall :
	public OMovable
{
private:

	bool is_player_between_vertical_range(const OMPlayer * player);
	bool is_player_between_horizontal_range(const OMPlayer * player);
	bool is_player_collided_top(const OMPlayer * player);
	bool is_player_collided_botton(const OMPlayer * player);
	bool is_player_collided_left(const OMPlayer * player);
	bool is_player_collided_right(const OMPlayer * player);
	void move_ball();

public:

	OMBall(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y);
	~OMBall();
	void move_ball(const OMPlayer * p1, const OMPlayer * p2, const Object * limit_top, const Object * limit_botton);
};

