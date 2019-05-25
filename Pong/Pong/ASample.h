#pragma once
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Validate.h"

class ASample
{
private:
	ALLEGRO_SAMPLE * sample = nullptr;
	ALLEGRO_PLAYMODE playmode;

public:
	ASample(const char * path, const ALLEGRO_PLAYMODE playmode);
	void play_sample() const;
	~ASample();
};

