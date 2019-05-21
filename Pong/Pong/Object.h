#pragma once
#include <memory>

class Object
{
protected:
	int top_left_x = 0;
	int top_left_y = 0;
	int width = 0;
	int height = 0;

public:
	Object(const int& top_left_x, const int& top_left_y, const int& width, const int& height);
	~Object();
	int top_collision_line() const;
	int botton_collision_line() const;
	int left_collision_line() const;
	int right_collision_line() const;
};
