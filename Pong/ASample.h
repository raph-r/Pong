#pragma once
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Validate.h"

/**
 * <EN>
 * Encapsulate the ALLEGRO_SAMPLE class
 * <PT-Br>
 * Encapsula a classe ALLEGRO_SAMPLE
*/
class ASample
{
	private:
		ALLEGRO_SAMPLE * sample = nullptr;
		ALLEGRO_PLAYMODE playmode;

	public:
		/**
		 * <EN>
		 * Class constructor. Create a sound sample
		 * @param[in] path - Path of saound
		 * @param[in] playmode - playback mode
		 *
		 * <PT-Br>
		 * Construtor da classe. Cria uma amostra de som
		 * @param[in] path - Caminho do som
		 * @param[in] playmode - modo de reproducao
		*/
		ASample(const char * path, const ALLEGRO_PLAYMODE playmode);

		/**
		 * <EN>
		 * Class desconstructor
		 *
		 * <PT-Br>
		 * Desconstrutor da classe
		*/
		~ASample();

		/**
		 * <EN>
		 * Plays the associated sound
		 *
		 * <PT-Br>
		 * Reproduz o som associado
		*/
		void play_sample() const;

};

