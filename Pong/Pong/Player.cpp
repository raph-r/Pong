#include "Player.h"

Player::Player(const int& btn_to_up, const int& btn_to_down, const int& top_left_x, const int& width, const int& height, const int& score)
{
	this->top_left_x = top_left_x;
	this->top_left_y = (SCREEN_HEIGHT / 2) - (height / 2);
	this->width = width;
	this->height = height;
	this->btn_to_up = btn_to_up;
	this->btn_to_down = btn_to_down;
	this->score = score;
	this->initial_position_x = this->top_left_x;
	this->initial_position_y = this->top_left_y;
}

Player::~Player(){}

void Player::reset_position()
{
	this->top_left_x = this->initial_position_x;
	this->top_left_y = this->initial_position_y;
}

int Player::top_collision_line() const
{
	return this->top_left_y;
}

int Player::botton_collision_line() const
{
	return this->top_left_y + this->height;
}

int Player::left_collision_line() const
{
	return this->top_left_x;
}

int Player::right_collision_line() const
{
	return this->top_left_x + this->width;
}

void Player::add_score()
{
	this->score++;
}

void Player::up()
{
	this->top_left_y -= 4;
}

void Player::down()
{
	this->top_left_y += 4;
}

int Player::get_score()
{
	return this->score;
}