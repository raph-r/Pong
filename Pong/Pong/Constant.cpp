#include "Constant.h"

const unsigned int Constant::SCREEN_WIDTH = 640;
const unsigned int Constant::SCREEN_HEIGHT = 480;
const unsigned int Constant::HALF_SCREEN_WIDTH = Constant::SCREEN_WIDTH / 2;
const unsigned int Constant::HALF_SCREEN_HEIGHT = Constant::SCREEN_HEIGHT / 2;
const unsigned int Constant::KEY_SEEN = 1;
const unsigned int Constant::KEY_RELEASED = 2;

const unsigned int Constant::BALL_WIDTH = 10;
const unsigned int Constant::BALL_HEIGHT = 10;
const unsigned int Constant::BALL_POSITION_X = Constant::HALF_SCREEN_WIDTH - (Constant::BALL_WIDTH / 2);
const unsigned int Constant::BALL_POSITION_Y = Constant::HALF_SCREEN_HEIGHT - (Constant::BALL_HEIGHT / 2);
const unsigned int Constant::BALL_ACCELERATION_X = 3;
const unsigned int Constant::BALL_ACCELERATION_Y = 3;
const char Constant::BALL_NAME[] = "Ball";