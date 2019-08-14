#pragma once
#include <memory>
#include "Validate.h"
#include <iostream>

/**
 * <EN>
 * Abstract object that represents a square
 *
 * <PT-Br>
 * Objeto abstrato que representar um quadrado
*/
class Square
{
	protected:
		int top_left_x = 0;
		int top_left_y = 0;
		int width = 0;
		int height = 0;
		const char * name;

	public:

		/**
		 * <EN>
		 * Class constructor.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] name
		 *
		 * <PT-Br>
		 * Construtor da classe.
		 * @param[in] top_left_x
		 * @param[in] top_left_y
		 * @param[in] width
		 * @param[in] height
		 * @param[in] name
		*/
		Square(const int& top_left_x, const int& top_left_y, const int& width, const int& height, const char * name);

		/**
		 * <EN>
		 * Class desconstructor

		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~Square();

		/**
		 * <EN>
		 * Get the position of top line of square
		 * @return position of top line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha superior do quadrado
		 * @return posicao da linha superior do quadrado
		*/
		int get_top_line() const;

		/**
		 * <EN>
		 * Get the position of botton line of square
		 * @return position of botton line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha inferior do quadrado
		 * @return posicao da linha inferior do quadrado
		*/
		int get_botton_line() const;

		/**
		 * <EN>
		 * Get the position of left line of square
		 * @return position of left line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha esquerda do quadrado
		 * @return posicao da linha esquerda do quadrado
		*/
		int get_left_line() const;

		/**
		 * <EN>
		 * Get the position of right line of square
		 * @return position of right line of square
		 *
		 * <PT-Br>
		 * Captura a posicao da linha direita do quadrado
		 * @return posicao da linha direita do quadrado
		*/
		int get_right_line() const;

		/**
		 * <EN>
		 * Get the name of square
		 * @return name of square
		 *
		 * <PT-Br>
		 * Captura o nome do quadrado
		 * @return nome do quadrado
		*/
		const char * get_name();

		/**
		 * <EN>
		 * Verify if 'pos' is between the left line and right line of Square
		 * @param[in] pos - Position to verify
		 * @return True, if 'pos' is between left line and right line of Square. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se 'pos' esta entre a linha esquerda e a linha direita de Square
		 * @param[in] pos - Posicao para verificar
		 * @return True caso 'pos' esteja entre a linha esquerda e a linha direta de Square. Caso contrario, False
		*/
		bool pos_is_between_horizontal_borders(const int & pos) const;

		/**
		 * <EN>
		 * Verify if 'pos' is between the top line and botton line of Square
		 * @param[in] pos - Position to verify
		 * @return True, if 'pos' is between top line and botton line of Square. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se 'pos' esta entre a linha superior e a linha inferior de Square
		 * @param[in] pos - Posicao para verificar
		 * @return True caso 'pos' esteja entre a linha superior e a linha inferior de Square. Caso contrario, False
		*/
		bool pos_is_between_vertical_borders(const int & pos) const;

		/**
		 * <EN>
		 * Verify if the botton of this object collided with top of 'other_square'
		 * @param[in] other_square - Other Square to verify
		 * @return True, if has collided. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se houve colisao entre a parte inferior deste objeto com a parte superior de other_square
		 * @param[in] other_square - Outro Square para verificar
		 * @return True caso houve colisao. Caso contrario, False
		*/
		bool collided_on_top_of_other_square(const Square const * other_square);

		/**
		 * <EN>
		 * Verify if the top of this object collided with botton of 'other_square'
		 * @param[in] other_square - Other Square to verify
		 * @return True, if has collided. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se houve colisao entre a parte superior deste objeto com a parte inferior de other_square
		 * @param[in] other_square - Outro Square para verificar
		 * @return True caso houve colisao. Caso contrario, False
		*/
		bool collided_on_botton_of_other_square(const Square const * other_square);

		/**
		 * <EN>
		 * Verify if the right of this object collided with left of 'other_square'
		 * @param[in] other_square - Other Square to verify
		 * @return True, if has collided. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se houve colisao entre a parte direita deste objeto com a parte esquerda de other_square
		 * @param[in] other_square - Outro Square para verificar
		 * @return True caso houve colisao. Caso contrario, False
		*/
		bool collided_on_left_of_other_square(const Square const * other_square);

		/**
		 * <EN>
		 * Verify if the left of this object collided with right of 'other_square'
		 * @param[in] other_square - Other Square to verify
		 * @return True, if has collided. Otherwise, False
		 *
		 * <PT-Br>
		 * Verifica se houve colisao entre a parte esquerda deste objeto com a parte direta de other_square
		 * @param[in] other_square - Outro Square para verificar
		 * @return True caso houve colisao. Caso contrario, False
		*/
		bool collided_on_right_of_other_square(const Square const * other_square);
};
