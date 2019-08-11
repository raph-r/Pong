#include "SMovable.h"

SMovable::SMovable(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const char * name) :
	Square(top_left_x, top_left_y, width, height, name)
{
	this->acceleration_x = std::move(acceleration_x);
	this->acceleration_y = std::move(acceleration_y);
	this->initial_position_x = this->top_left_x;
	this->initial_position_y = this->top_left_y;
	this->initial_acceleration_x = this->acceleration_x;
	this->initial_acceleration_y = this->acceleration_y;
}

SMovable::~SMovable(){}

void SMovable::reverse_acceleration_x()
{
	this->acceleration_x *= -1;
}

void SMovable::reverse_acceleration_y()
{
	this->acceleration_y *= -1;
}

void SMovable::up()
{
	this->top_left_y -= this->acceleration_y;
}

void SMovable::down()
{
	this->top_left_y += this->acceleration_y;
}

void SMovable::left()
{
	this->top_left_x -= this->acceleration_x;
}

void SMovable::right()
{
	this->top_left_x += this->acceleration_x;
}

void SMovable::reset_position()
{
	this->top_left_x = this->initial_position_x;
	this->top_left_y = this->initial_position_y;
	this->acceleration_x = this->initial_acceleration_x;
	this->acceleration_y = this->initial_acceleration_y;
}

void SMovable::add_acceleration_x()
{
	this->acceleration_x++;
}

void SMovable::add_acceleration_y()
{
	this->acceleration_y++;
}

void SMovable::subtract_acceleration_x()
{
	this->acceleration_x--;
}

void SMovable::subtract_acceleration_y()
{
	this->acceleration_y--;
}