#include "SMovable.h"

SMovable::SMovable(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration, const char * name) :
	Square(top_left_x, top_left_y, width, height, name)
{
	this->acceleration = std::move(acceleration);
	this->initial_position_x = this->top_left_x;
	this->initial_position_y = this->top_left_y;
	this->initial_acceleration = this->acceleration;
}

SMovable::~SMovable(){}

void SMovable::up()
{
	this->top_left_y -= this->acceleration;
}

void SMovable::down()
{
	this->top_left_y += this->acceleration;
}

void SMovable::left()
{
	this->top_left_x -= this->acceleration;
}

void SMovable::right()
{
	this->top_left_x += this->acceleration;
}

void SMovable::reset_position()
{
	this->top_left_x = this->initial_position_x;
	this->top_left_y = this->initial_position_y;
	this->acceleration = this->initial_acceleration;
}

void SMovable::add_acceleration()
{
	this->acceleration++;
}

void SMovable::subtract_acceleration()
{
	this->acceleration--;
}
