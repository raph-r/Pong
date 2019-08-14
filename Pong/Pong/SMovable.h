#pragma once
#include "Square.h"
class SMovable :
	public Square
{
protected:
	int acceleration = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;
	int initial_acceleration = 0;
public:
	SMovable(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration, const char * name);
	~SMovable();
	void up();
	void down();
	void right();
	void left();
	void add_acceleration();
	void subtract_acceleration();
	virtual void reset_position();

};

