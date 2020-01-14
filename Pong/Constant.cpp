#include "Constant.h"

const unsigned int Constant::SCREEN_WIDTH = 640;
const unsigned int Constant::SCREEN_HEIGHT = 480;
const unsigned int Constant::HALF_SCREEN_WIDTH = Constant::SCREEN_WIDTH / 2;
const unsigned int Constant::HALF_SCREEN_HEIGHT = Constant::SCREEN_HEIGHT / 2;
const unsigned int Constant::KEY_SEEN = 1;
const unsigned int Constant::KEY_RELEASED = 2;
const unsigned int Constant::HORIZONTAL_MARGIN = 30;
const unsigned int Constant::VERTICAL_MARGIN = 10;
const unsigned int Constant::HEIGHT_DIVISION = ((Constant::SCREEN_HEIGHT - (Constant::VERTICAL_MARGIN * 2)) / 20);
const unsigned int Constant::ACCELERATION = 3;
const int Constant::MAX_SCORE = 10;
const char Constant::MSG_PLAY_AGAIN[] = "Press Space to play again!";
const char Constant::MSG_PLAY_GAME[] = "Press Space to play";

const unsigned int Constant::BALL_WIDTH = 10;
const unsigned int Constant::BALL_HEIGHT = 10;
const unsigned int Constant::BALL_POSITION_X = Constant::HALF_SCREEN_WIDTH - (Constant::BALL_WIDTH / 2);
const unsigned int Constant::BALL_POSITION_Y = Constant::HALF_SCREEN_HEIGHT - (Constant::BALL_HEIGHT / 2);
const char Constant::BALL_NAME[] = "Ball";

const unsigned int Constant::PLAYER_WIDTH = 10;
const unsigned int Constant::PLAYER_HEIGHT = 60;
const unsigned int Constant::PLAYER_POSITION_Y = Constant::HALF_SCREEN_HEIGHT - (Constant::PLAYER_HEIGHT / 2);
const unsigned int Constant::PLAYER_1_POSITION_X = Constant::HORIZONTAL_MARGIN;
const unsigned int Constant::PLAYER_2_POSITION_X = Constant::SCREEN_WIDTH - Constant::HORIZONTAL_MARGIN - Constant::PLAYER_WIDTH;
const char Constant::WINNER_MSG_P1[] = "Player 1 Win!!!";
const char Constant::WINNER_MSG_P2[] = "Player 2 Win!!!";
const unsigned int Constant::HALF_OF_SIDE_PLAYER_1 = Constant::HALF_SCREEN_WIDTH / 2;
const unsigned int Constant::HALF_OF_SIDE_PLAYER_2 = Constant::HALF_SCREEN_WIDTH + (Constant::HALF_SCREEN_WIDTH / 2);
