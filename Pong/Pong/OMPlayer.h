#pragma once
#include "OMovable.h"
class OMPlayer :
	public OMovable
{
private:
	unsigned int btn_to_up = 0;
	unsigned int btn_to_down = 0;
	unsigned int score = 0;
public:
	OMPlayer(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration_x, const int& acceleration_y, const unsigned int& btn_to_up, const unsigned int& btn_to_down, const char * name);
	OMPlayer() = delete;
	~OMPlayer();

	void add_score();
	int get_score() const;
	void reset_score();
	void move_player(const unsigned char * keys, const Square * limit_top, const Square * limit_botton);
};

