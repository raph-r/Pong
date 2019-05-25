#pragma once
#include <memory>

class Object
{
protected:
	int top_left_x = 0;
	int top_left_y = 0;
	int width = 0;
	int height = 0;
	const char * name;

public:
	Object(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);
	~Object();
	int collision_line_top() const;
	int collision_line_botton() const;
	int collision_line_left() const;
	int collision_line_right() const;
	const char * get_name();
};
