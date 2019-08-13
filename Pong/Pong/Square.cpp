#include "Square.h"

Square::Square(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name)
{
	this->top_left_x = std::move(top_left_x);
	this->top_left_y = std::move(top_left_y);
	this->width = std::move(width);
	this->height = std::move(height);
	this->name = name;
}

Square::~Square(){}

int Square::get_top_line() const
{
	return this->top_left_y;
}

int Square::get_botton_line() const
{
	return this->top_left_y + this->height;
}

int Square::get_left_line() const
{
	return this->top_left_x;
}

int Square::get_right_line() const
{
	return this->top_left_x + this->width;
}

const char * Square::get_name()
{
	return this->name;
}