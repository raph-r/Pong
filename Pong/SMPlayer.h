#pragma once
#include "SMovable.h"
#include "Constant.h"

/**
 * <EN>
 * Represents a Player object
 * <PT-Br>
 * Representa o objeto Jogador
*/
class SMPlayer : public SMovable
{
	private:
		unsigned int btn_to_up = 0;
		unsigned int btn_to_down = 0;
		unsigned int score = 0;

	public:

		/**
		 * <EN>
		 * Class constructor.
		 * @param[in] top_left_x
		 * @param[in] btn_to_up - Key that will be pressed to SMPlayer go to up
		 * @param[in] btn_to_down - Key that will be pressed to SMPlayer go to down
		 * @param[in] name
		 *
		 * <PT-Br>
		 * Construtor da classe.
		 * @param[in] top_left_x
		 * @param[in] btn_to_up - tecla que sera preciosanada para SMPlayer subir
		 * @param[in] btn_to_down - tecla que sera preciosanada para SMPlayer descer
		 * @param[in] name
		*/
		SMPlayer(const int& top_left_x, const unsigned int& btn_to_up, const unsigned int& btn_to_down, const char * name);

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~SMPlayer();

		/**
		 * <EN>
		 * Add 1 to score of SMPlayer
		 *
		 * <PT-Br>
		 * Adiciona 1 ao score de SMPlayer
		*/
		void add_score();

		/**
		 * <EN>
		 * Get the score of SMPlayer
		 * @return Score of SMPlayer
		 *
		 * <PT-Br>
		 * Captura o score de SMPlayer
		 * @return Score de SMPlayer
		*/
		int get_score() const;

		/**
		 * <EN>
		 * Set SMPlayer::score  equal to zero and call SMovable::reset_position, that will reverts
		 * all attributes, to the values that was defined at the moment of creation of object
		 *
		 * <PT-Br>
		 * Define SMPlayer::score igual a zero. Invoca o metodo SMovable::reset_position, que
		 * reverte todos os atributos para os valores definidos no momento da criacao do objeto
		*/
		void reset();

		/**
		 * <EN>
		 * if SMPlayer::btn_to_up or SMPlayer::btn_to_down were pressed and
		 * SMPlayer didn`t collided with upper_limit or lower_limit, moves SMPlayer
		 * @param[in] keys - Array of flags indicating the state of each key
		 * @param[in] upper_limit - Upper limit of screen
		 * @param[in] lower_limit - Lower limit of screen
		 *
		 * <PT-Br>
		 * Se SMPlayer::btn_to_up ou SMPlayer::btn_to_down foram pressionadas e
		 * SMPlayer nao colidiu com upper_limit ou lower_limit, efetua o movimento
		 * @param[in] keys - Array de bandeiras que identificam cada tecla
		 * @param[in] upper_limit - Limite superior da tela
		 * @param[in] lower_limit - Limite inferior da tela
		*/
		void move_player(const unsigned char * keys, const Square * upper_limit, const Square * lower_limit);
};

