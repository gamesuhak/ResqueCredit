#pragma once
#include <fmod.h>

typedef enum Sound
{
	SOUND_TITLE = 0,
	SOUND_ROOM,
	SOUND_CURSOR,
	SOUND_SELECT,
	SOUND_ARROW,
	SOUND_HIT,
	SOUND_CLEAR,
	SOUND_LOSE,
	SOUND_COUNT
} Sound;

void InitializeFMODSound();
void ReleaseFMODSound();
void PlayFMODSound(Sound number);
void StopFMODSound(Sound number);