#pragma once
#include "Object.h"
class OMovable :
	public Object
{
protected:
	int acceleration_x = 0;
	int acceleration_y = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;
	int initial_acceleration_x = 0;
	int initial_acceleration_y = 0;
public:
	OMovable(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const char * name);
	~OMovable();
	void reverse_acceleration_x();
	void reverse_acceleration_y();
	void up();
	void down();
	void right();
	void left();
	void add_acceleration_x();
	void add_acceleration_y();
	void subtract_acceleration_x();
	void subtract_acceleration_y();
	virtual void reset_position();

};

