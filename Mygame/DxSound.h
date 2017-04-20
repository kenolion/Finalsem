#ifndef DXSOUND_H
#define DXSOUND_H

#ifndef NUM_CHANNELS
#define NUM_CHANNELS 6
#endif // !NUM_CHANNELS
#include <fmod.hpp>
#include <Windows.h>
class DxSound
{


public:
	FMOD::System *fmodSystem;
	FMOD_RESULT result;
	FMOD::Channel *channel;
	// =============================== ADD NEW SOUNDS UNDER HERE =============================================

	FMOD::Sound *mainmenuMusic;
	FMOD::Sound *clickSound;
	FMOD::Sound *playerWinMusic;
	FMOD::Sound *playjumpSound;
	FMOD::Sound *deathSound;
	FMOD::Sound *mainmenuMusic2;
	FMOD::Sound *failMusic;
	FMOD::Sound *explodeSound;
	FMOD::Sound *pickUpKeySound;

	FMOD::Sound *level1Music;
	FMOD::Sound *level2Music;

	// =======================================================================================================
	bool initializeSound();
	void updateSound();
	void loadSounds();
	
	// =============================== ADD PLAYER MUSIC FUNCTIONS IN HERE ====================================

	void playMainMenuMusic();
	void playClickSound();
	void playPlayerWinMusic();
	void playJumpSound();
	void playDeathSound();
	void playMainMenuMusic2();
	void playLevel1Music();
	void playLevel2Music();
	void playFailMusic();
	void playExplosionSound();
	void playPickUpKeySound();

	void pauseLevel1Music();
	void pauseLevel2Music();

	void pauseMainMenuMusic();
	void pauseMainMenuMusic2();
	void pausePlayerWinMusic();

	// =======================================================================================================

	DxSound();
	~DxSound();
};

#endif // !DXSOUND_H
