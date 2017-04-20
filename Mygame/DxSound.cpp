#include "DxSound.h"


bool DxSound::initializeSound()
{
	if (fmodSystem == NULL) {
		result = FMOD::System_Create(&fmodSystem);
		if (result != FMOD_OK) {
			MessageBox(NULL, "ERROR", "Could not create fmodsystem!", MB_ICONERROR);
			return false;

		}
	}

	result = fmodSystem->init(NUM_CHANNELS, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not initiaize fmodsystem!", MB_ICONERROR);
		return false;
	}
	return true;
}

void DxSound::updateSound()
{
	result = fmodSystem->update();

	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not update fmod!", MB_ICONERROR);
	}
}

void DxSound::loadSounds()
{


	result = fmodSystem->createSound("sounds//clickSoundEffect.mp3", FMOD_DEFAULT, 0, &clickSound); //File name * Path, Behaviour of sound
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load clickSoundEffect.mp3", MB_ICONERROR);
	}
	clickSound->setMode(FMOD_LOOP_OFF);  // No loop

	result = fmodSystem->createStream("sounds//mainMenuMusic.mp3", FMOD_DEFAULT, 0, &mainmenuMusic);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load mainMenuMusic.mp3", MB_ICONERROR);
	}
	mainmenuMusic->setMode(FMOD_LOOP_NORMAL);

	result = fmodSystem->createStream("sounds\\mainMenuMusic2.mp3", FMOD_DEFAULT, 0, &mainmenuMusic2);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load mainMenuMusic2.mp3", MB_ICONERROR);
	}
	mainmenuMusic2->setMode(FMOD_LOOP_NORMAL);

	result = fmodSystem->createStream("sounds\\Level1Music.mp3", FMOD_DEFAULT, 0, &level1Music);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load Level1Music.mp3", MB_ICONERROR);
	}
	level1Music->setMode(FMOD_LOOP_NORMAL);


	result = fmodSystem->createStream("sounds\\Level2Music.mp3", FMOD_DEFAULT, 0, &level2Music);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load Level2Music.mp3", MB_ICONERROR);
	}
	level2Music->setMode(FMOD_LOOP_NORMAL);

	result = fmodSystem->createStream("sounds//failMusic.mp3", FMOD_DEFAULT, 0, &failMusic);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load failMusic.mp3", MB_ICONERROR);
	}
	failMusic->setMode(FMOD_LOOP_OFF);

	result = fmodSystem->createStream("sounds//playerWinMusic.mp3", FMOD_DEFAULT, 0, &playerWinMusic);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load playerWinMusic.mp3", MB_ICONERROR);
	}
	playerWinMusic->setMode(FMOD_LOOP_NORMAL);

	result = fmodSystem->createStream("sounds//jumpSound.mp3", FMOD_DEFAULT, 0, &playjumpSound);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load jumpSound", MB_ICONERROR);
	}
	playjumpSound->setMode(FMOD_LOOP_OFF);


	result = fmodSystem->createStream("sounds//deathSound.mp3", FMOD_DEFAULT, 0, &deathSound);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load deathSound", MB_ICONERROR);
	}
	deathSound->setMode(FMOD_LOOP_OFF);

	result = fmodSystem->createStream("sounds//explodeSound.mp3", FMOD_DEFAULT, 0, &explodeSound);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load boomSound", MB_ICONERROR);
	}
	deathSound->setMode(FMOD_LOOP_OFF);


	result = fmodSystem->createStream("sounds//erapowerup.mp3", FMOD_DEFAULT, 0, &pickUpKeySound);
	if (result != FMOD_OK) {
		MessageBox(NULL, "ERROR", "Could not load pickup Sound", MB_ICONERROR);
	}
	deathSound->setMode(FMOD_LOOP_OFF);

}

void DxSound::playMainMenuMusic()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, mainmenuMusic, false, &channel);

}

void DxSound::playMainMenuMusic2()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, mainmenuMusic2, false, &channel);

}

void DxSound::playLevel1Music()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, level1Music, false, &channel);
}

void DxSound::playLevel2Music()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, level2Music, false, &channel);
}

void DxSound::playClickSound()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, clickSound, false, &channel);
}

void DxSound::playPlayerWinMusic()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, playerWinMusic, false, &channel);
}

void DxSound::playJumpSound()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, playjumpSound, false , &channel);
}

void DxSound::playDeathSound()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, deathSound, false, &channel);
}

void DxSound::playFailMusic()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, failMusic, false, &channel);
}

void DxSound::playExplosionSound()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, explodeSound, false, &channel);
}

void DxSound::playPickUpKeySound()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, pickUpKeySound, false, &channel);
}

void DxSound::pauseLevel1Music()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, level1Music, true, &channel);
}

void DxSound::pauseLevel2Music()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, level2Music, true, &channel);
}

void DxSound::pauseMainMenuMusic()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, mainmenuMusic, true, &channel);
}

void DxSound::pauseMainMenuMusic2()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, mainmenuMusic2, true, &channel);
}


void DxSound::pausePlayerWinMusic()
{
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, playerWinMusic, true, &channel);
}


DxSound::DxSound()
{
}


DxSound::~DxSound()
{
	fmodSystem->release();
}
