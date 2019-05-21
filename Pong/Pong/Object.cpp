#include "Object.h"

Object::Object(const int& top_left_x, const int& top_left_y, const int& width, const int& height)
{
	this->top_left_x = std::move(top_left_x);
	this->top_left_y = std::move(top_left_y);
	this->width = std::move(width);
	this->height = std::move(height);
}

Object::~Object(){}

int Object::top_collision_line() const
{
	return this->top_left_y;
}

int Object::botton_collision_line() const
{
	return this->top_left_y + this->height;
}

int Object::left_collision_line() const
{
	return this->top_left_x;
}

int Object::right_collision_line() const
{
	return this->top_left_x + this->width;
}