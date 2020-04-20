#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include <list>

#include "j1Module.h"

using namespace std;

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	// Save
	bool Save(pugi::xml_node&) const;

	// Load
	bool Load(pugi::xml_node&);

public:
	uint generalVolume = 0;
	int VolumeMusic;
	bool PlayingMenuMusic;
	bool PlayingIngameAudio;
	bool PlayingLoseMusic;
	bool PlayingWinMusic;
	bool PlayingLogoMusic;



	//AUDIO CHUNKS
	Mix_Chunk* Click_Button_Sound;
	Mix_Chunk* Click_Logo_Sound;
	Mix_Chunk* Spawner_Destroyed;
	Mix_Chunk* time_sound;
	Mix_Chunk* WarriorAttack_Sound;
	Mix_Chunk* walkingPainter_sound;
	Mix_Chunk* walkingWarrior_sound;
	Mix_Chunk* buy1_sound;
	Mix_Chunk* buy2_sound;
	Mix_Chunk* spawnFromHall;
	Mix_Chunk* birds_sound;
	Mix_Chunk* crickets_sound;
	Mix_Chunk* braindead_sound;
	Mix_Chunk* Transition_Sound;
	Mix_Chunk* paintExtractor_sound;
	Mix_Chunk* woodProducer_sound;

	bool logoSound;


private:

	_Mix_Music*			music = NULL;
	list<Mix_Chunk*>	fx;
	void ChunkAudioManager();
};

#endif // __j1AUDIO_H__