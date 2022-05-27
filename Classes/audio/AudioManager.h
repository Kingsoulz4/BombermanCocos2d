#pragma once


#include "SimpleAudioEngine.h"

class AudioManger
{
public:

	static AudioManger* _audioManager ;
	int PLAYER_WALK_SOUND =0;
	int PLAYER_PLACE_BOMB_SOUND =0;

	AudioManger();
	~AudioManger();
	static AudioManger* getInstance();

	void playBomberPlaceBomb();
	void playBombExplode();
	void playBomberWalk();
	void playGameOver();
	void playItemCollected();
	void playIntroductionSound();
	void stopIntroductionSound();
	void disableAllEffects();
	void disableMusic();
	void enableAllEffects();
	void enableMusic();
	void playVictory();


private:

};


