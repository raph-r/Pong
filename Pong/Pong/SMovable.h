#pragma once
#include "Square.h"


/**
 * <EN>
 * Represents a movable square
 * <PT-Br>
 * Representa uma Square movel
*/
class SMovable : public Square
{
	protected:
		int acceleration = 0;
		int initial_position_x = 0;
		int initial_position_y = 0;
		int initial_acceleration = 0;
	public:

		/**
		 * <EN>
		 * Class constructor.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] acceleration
		 * @param[in] name
		 *
		 * <PT-Br>
		 * Construtor da classe.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] acceleration
		 * @param[in] name
		*/
		SMovable(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const int& acceleration, const char * name);

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~SMovable();

		/**
		 * <EN>
		 * Moves SMovable to top, using SMovable::acceleration
		 *
		 * <PT-Br>
		 * Movimenta SMovable para cima, usando SMovable::acceleration
		*/
		void up();

		/**
		 * <EN>
		 * Moves SMovable to down, using SMovable::acceleration
		 *
		 * <PT-Br>
		 * Movimenta SMovable para baixo, usando SMovable::acceleration
		*/
		void down();

		/**
		 * <EN>
		 * Moves SMovable to right, using SMovable::acceleration
		 *
		 * <PT-Br>
		 * Movimenta SMovable para direita, usando SMovable::acceleration
		*/
		void right();

		/**
		 * <EN>
		 * Moves SMovable to left, using SMovable::acceleration
		 *
		 * <PT-Br>
		 * Movimenta SMovable para esquerda, usando SMovable::acceleration
		*/
		void left();

		/**
		 * <EN>
		 * Add 1 to acceleration of SMovable
		 *
		 * <PT-Br>
		 * Adiciona 1 a aceleracao de SMovable
		*/
		void add_acceleration();

		/**
		 * <EN>
		 * Reverts all attributes, to the values that was defined at the moment of creation of object
		 *
		 * <PT-Br>
		 * Reverte todos os atributos para os valores definidos no momento da criacao do objeto
		*/
		virtual void reset_position();
};

