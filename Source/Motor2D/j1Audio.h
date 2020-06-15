#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include <vector>

#include "j1Module.h"
#include "p2Point.h"

using namespace std;

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 500						
#define RAD_TO_DEG 57.32f				
#define MAX_DISTANCE 255	

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
	uint PlayFx(unsigned int fx, int repeat = 0);

	// Play a WAV like a 3D audio reciving an fx, a channel, an angle and a distance
	bool PlaySpatialFx(uint id, uint channel_angle = 1, uint distance = 1, int repeat = 0);

	// Get the angle of the Y axis with the position of the enemy regard the player position
	uint GetAngle(fPoint player_pos, fPoint enemy_pos);

	// Get the distance with the position of the player and the enemy
	uint GetDistance(fPoint player_pos, fPoint enemy_pos);

	// Save
	bool Save(pugi::xml_node&) const;

	// Load
	bool Load(pugi::xml_node&);


	void ChunkAudioManager(int volume);

public:
	uint generalVolume = 0;
	int VolumeMusic;
	bool PlayingMenuMusic;
	bool PlayingIngameAudio;
	bool PlayingLoseMusic;
	bool PlayingWinMusic;
	bool PlayingLogoMusic;
	bool PlayingSettingsMusic;
	int CurrentMusVolume;
	int CurrentFXVolume;
	



	//AUDIO CHUNKS
	Mix_Chunk*	Click_Button_Sound;
	Mix_Chunk*	Click_Logo_Sound;
	Mix_Chunk*	Spawner_Destroyed;
	Mix_Chunk*	time_sound;
	uint		attack_Sound;//
	uint		walkingUnit2_sound;//
	uint		walkingUnit1_sound;//
	uint		knightAttack_Sound;//
	uint		enemy_sound;//
	Mix_Chunk*	buy1_sound;
	Mix_Chunk*	buy2_sound;
	Mix_Chunk*	spawnFromHall;
	Mix_Chunk*	birds_sound;
	//Mix_Chunk*	knight_sound;
	//Mix_Chunk*	explorer_sound;
	Mix_Chunk*	enemyDeath_sound;
	Mix_Chunk*	crickets_sound;
	Mix_Chunk*	braindead_sound;
	Mix_Chunk*	Transition_Sound;
	Mix_Chunk*	Quest_Audio;
	Mix_Chunk*	logo_1_sound;
	Mix_Chunk*	logo_2_sound;


	bool logoSound;


private:

	_Mix_Music*				music = NULL;
	std::vector<Mix_Chunk*>	fx;
	int						scale;
	
};

#endif // __j1AUDIO_H__