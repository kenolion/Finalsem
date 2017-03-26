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

	void pauseMainMenuMusic();
	void pausePlayerWinMusic();

	// =======================================================================================================

	DxSound();
	~DxSound();
};

#endif // !DXSOUND_H
