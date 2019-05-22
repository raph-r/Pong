#pragma once
#include "Player.h"
#include "OMPlayer.h"

class Ball
{
private:
	int acceleration_x = 0;
	int acceleration_y = 0;
	int width = 0;
	int height = 0;
	int top_left_x = 0;
	int top_left_y = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;
public:
	Ball(const int& width, const int& height, const int& top_left_x, const int& top_left_y, const int& acceleration_x, const int& acceleration_y);
	~Ball();
	void reset_position();
	void move_ball(const int& height_division, const OMPlayer * p1, const OMPlayer * p2);
	void change_acceleration_x();
	void change_acceleration_y();
	void simple_move();
	bool is_collided_top(const OMPlayer * player);
	bool is_collided_botton(const OMPlayer * player);
	bool is_collided_left(const OMPlayer * player);
	bool is_collided_right(const OMPlayer * player);
	bool is_between_vertical_range(const OMPlayer * player);
	bool is_between_horizontal_range(const OMPlayer * player);
	int top_collision_line();
	int botton_collision_line();
	int left_collision_line();
	int right_collision_line();
};

