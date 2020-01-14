#pragma once
#include "SMovable.h"
#include "SMPlayer.h"
#include "ASample.h"
#include "Constant.h"

/**
 * <EN>
 * Represents the ball of game
 * <PT-Br>
 * Representa a bola do jogo
*/
class SMBall : public SMovable
{
	private:

		bool to_right = true;
		bool to_down = true;
		unsigned int hits = 0;

		/**
		 * <EN>
		 * Move the object
		 *
		 * <PT-Br>
		 * Movimenta o objeto
		*/
		void move_ball();

		/**
		 * <EN>
		 * If the quantity of SMBall::hits was been reached, adds acceleration to SMBall and players
		 * @param[in] p1 - Pointer to Player 1
		 * @param[in] p2 - Pointer to Player 2
		 * <PT-Br>
		 * Caso a quantidade de SMBall::hits tenha sido alcancada, aumenta a velocidade de momento de SMBall e dos players
		 * @param[in] p1 - Ponteiro para Player 1
		 * @param[in] p2 - Ponteiro para Player 2
		*/
		void try_increase_speed(SMPlayer * const p1, SMPlayer * const p2);

	public:

		/**
		 * <EN>
		 * Class constructor. Create a screen to game
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria uma tela para o jogo
		*/
		SMBall();

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~SMBall();

		/**
		 * <EN>
		 * Verify if SMBall collided with some object and change the directions of your movements
		 * @param[in] p1 - Pointer to Player 1
		 * @param[in] p2 - Pointer to Player 2
		 * @param[in] upper_limit - Pointer to Object that represents the top limit of screen
		 * @param[in] lower_limit - Pointer to Object that represents the botton limit of screen
		 * @param[in] sample - Pointer to sample that will be played when some collision happens
		 * <PT-Br>
		 * Verifica se SMBall colidiu com algum objeto e altera a direcao dos movimentos, de acordo com cada resultado
		 * @param[in] p1 - Ponteiro para Player 1
		 * @param[in] p2 - Ponteiro para Player 2
		 * @param[in] upper_limit - Ponteiro para o objeto que representa o limite superior da tela
		 * @param[in] lower_limit - Ponteiro para o objeto que representa o limite inferior da tela
		 * @param[in] sample - Ponteiro para o som que devera ser tocado, caso a SMBall tenha colidido com alguma coisa
		*/
		void move_ball(SMPlayer * const p1, SMPlayer * const p2, Square const * const upper_limit, Square const * const lower_limit, ASample const * const sample);

		/**
		 * <EN>
		 * Reverts all attributes, to the values that was defined at the moment of creation of object
		 *
		 * <PT-Br>
		 * Reverte todos os atributos para os valores definidos no momento da criacao do objeto
		*/
		void reset();

		/**
		 * <EN>
		 * Inverts the horizontal direction of movement 
		 *
		 * <PT-Br>
		 * Inverte a direcao horizontal do movimento
		*/
		void inverts_horizontal_direction();

		/**
		 * <EN>
		 * Inverts the vertical direction of movement
		 *
		 * <PT-Br>
		 * Inverte a direcao vertical do movimento
		*/
		void inverts_vertical_direction();
};

