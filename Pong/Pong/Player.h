#pragma once
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MARGIN_TOP 10
#define MARGIN_BOTTON 10
#define MARGIN_LEFT 30
#define MARGIN_RIGHT 30

class Player
{
private:
	unsigned int btn_to_up = 0;
	unsigned int btn_to_down = 0;
	unsigned int score = 0;
	int top_left_x = 0;
	int top_left_y = 0;
	int width = 0;
	int height = 0;
	int initial_position_x = 0;
	int initial_position_y = 0;
public:
	Player(const int& btn_to_up, const int& btn_to_down, const int& top_left_x, const int& width, const int& height, const int& score);
	~Player();
	void reset_position();
	int top_collision_line() const;
	int botton_collision_line() const;
	int left_collision_line() const;
	int right_collision_line() const;
	void add_score();
	void down();
	void up();
	int get_score();
};

