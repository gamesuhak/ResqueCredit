#include "Sound.h"

#include <stdio.h>

FMOD_SYSTEM* g_System;
FMOD_SOUND* g_Sound[SOUND_COUNT];
FMOD_CHANNEL* g_Channel[SOUND_COUNT];

const char* SOUNDNAME[SOUND_COUNT] =
{
	"Title.mp3",
	"Room.mp3",
	"Cursor.wav",
	"Select.wav",
	"Arrow.wav",
	"Hit.wav",
	"Clear.wav",
	"Lose.wav"
};

void InitializeFMODSound()
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	for (int count = 0; count < SOUND_CURSOR; count++)
	{
		char name[50] = "Sound/";
		strcat(name, SOUNDNAME[count]);
		FMOD_System_CreateSound(g_System, name, FMOD_LOOP_NORMAL, 0, &g_Sound[count]);
	}

	for (int count = SOUND_CURSOR; count < SOUND_COUNT; count++)
	{
		char name[50] = "Sound/";
		strcat(name, SOUNDNAME[count]);
		FMOD_System_CreateSound(g_System, name, FMOD_DEFAULT, 0, &g_Sound[count]);
	}
}

void ReleaseFMODSound()
{
	for (int i = 0; i < SOUND_COUNT; i++)
	{
		FMOD_Sound_Release(g_Sound[i]);
	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

void PlayFMODSound(Sound number)
{
	FMOD_System_PlaySound(g_System, g_Sound[number], NULL, 0, &g_Channel[number]);
}

void StopFMODSound(Sound number)
{
	FMOD_Channel_Stop(g_Channel[number]);
}