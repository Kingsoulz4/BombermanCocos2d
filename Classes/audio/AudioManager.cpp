#include "AudioManager.h"

AudioManger* AudioManger::_audioManager = nullptr;



AudioManger::AudioManger()
{
}

AudioManger::~AudioManger()
{
}

AudioManger* AudioManger::getInstance()
{
	if (_audioManager == nullptr)
	{
		return new AudioManger();
	}
	return _audioManager;
}

void AudioManger::playBomberWalk()
{
	PLAYER_WALK_SOUND = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/PLAYER_WALK.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/PLAYER_WALK.wav");

}

void AudioManger::playBomberPlaceBomb()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(PLAYER_WALK_SOUND);
	PLAYER_PLACE_BOMB_SOUND = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/BOM_SET.wav");
}

void AudioManger::playBombExplode()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/BOM_11_L.wav");
}

void AudioManger::playGameOver()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/gameOver.wav");

}

void AudioManger::playIntroductionSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audios/AirRaid.wav");
}

void AudioManger::stopIntroductionSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void AudioManger::enableAllEffects()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
}

void AudioManger::enableMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1);
}

void AudioManger::playVictory()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/Winner.wav");
}

void AudioManger::disableAllEffects()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);
}

void AudioManger::disableMusic()
{
	stopIntroductionSound();
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
}

void AudioManger::playItemCollected()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audios/ITEM_GET.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->
}


