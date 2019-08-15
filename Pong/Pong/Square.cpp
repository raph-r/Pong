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

bool Square::pos_is_between_horizontal_borders(const int & pos) const
{
	return this->top_left_x <= pos && pos <= (this->top_left_x + this->width);
}

bool Square::pos_is_between_vertical_borders(const int & pos) const
{
	return this->top_left_y <= pos && pos <= (this->top_left_y + this->height);
}

bool Square::collided_on_top_of_other_square(const Square const * other_square)
{
	if (this->top_left_y + this->height >= other_square->top_left_y)
	{
		if (this->pos_is_between_horizontal_borders(other_square->top_left_x)
			|| other_square->pos_is_between_horizontal_borders(this->top_left_x)
			|| this->pos_is_between_horizontal_borders(other_square->top_left_x + other_square->width)
			|| other_square->pos_is_between_horizontal_borders(this->top_left_x + this->width))
		{
			return true;
		}
	}
	return false;
}

bool Square::collided_on_botton_of_other_square(const Square const * other_square)
{
	if (this->top_left_y <= other_square->top_left_y + other_square->height)
	{
		if (this->pos_is_between_horizontal_borders(other_square->top_left_x)
			|| other_square->pos_is_between_horizontal_borders(this->top_left_x)
			|| this->pos_is_between_horizontal_borders(other_square->top_left_x + other_square->width)
			|| other_square->pos_is_between_horizontal_borders(this->top_left_x + this->width))
		{
			return true;
		}
	}
	return false;
}

bool Square::collided_on_left_of_other_square(const Square const * other_square)
{
	if (this->top_left_x + this->width >= other_square->top_left_x)
	{
		if (this->pos_is_between_vertical_borders(other_square->top_left_y)
			|| other_square->pos_is_between_vertical_borders(this->top_left_y)
			|| this->pos_is_between_vertical_borders(other_square->top_left_y + other_square->height)
			|| other_square->pos_is_between_vertical_borders(this->top_left_y + this->height))
		{
			return true;
		}
	}
	return false;
}

bool Square::collided_on_right_of_other_square(const Square const * other_square)
{
	if (this->top_left_x <= other_square->top_left_x + other_square->width)
	{
		if (this->pos_is_between_vertical_borders(other_square->top_left_y)
			|| other_square->pos_is_between_vertical_borders(this->top_left_y)
			|| this->pos_is_between_vertical_borders(other_square->top_left_y + other_square->height)
			|| other_square->pos_is_between_vertical_borders(this->top_left_y + this->height))
		{
			return true;
		}
	}
	return false;
}

void Square::draw(ALLEGRO_COLOR * color)
{
	al_draw_filled_rectangle(this->top_left_x, this->top_left_y, (this->top_left_x + this->width), (this->top_left_y + this->height), *color);
}
