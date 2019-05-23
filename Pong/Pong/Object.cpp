#include "Object.h"

Object::Object(const int& top_left_x, const int& top_left_y, const int& width, const int& height)
{
	this->top_left_x = std::move(top_left_x);
	this->top_left_y = std::move(top_left_y);
	this->width = std::move(width);
	this->height = std::move(height);
}

Object::~Object(){}

int Object::collision_line_top() const
{
	return this->top_left_y;
}

int Object::collision_line_botton() const
{
	return this->top_left_y + this->height;
}

int Object::collision_line_left() const
{
	return this->top_left_x;
}

int Object::collision_line_right() const
{
	return this->top_left_x + this->width;
}