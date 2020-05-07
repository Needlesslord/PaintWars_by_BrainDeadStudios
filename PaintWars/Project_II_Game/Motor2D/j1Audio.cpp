#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include <list>
#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1SceneManager.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

using namespace std;


j1Audio::j1Audio() : j1Module()
{
	music = NULL;
	name = ("audio");
}

// Destructor
j1Audio::~j1Audio()
{}

// Called before render is available
bool j1Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	Quest_Audio = Mix_LoadWAV("audio/fx/QuestCompletedAudio.wav");
	if (Quest_Audio == NULL)
	{
		LOG("Quest Audio  IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	Click_Button_Sound = Mix_LoadWAV("audio/fx/Click_Mouse.wav");
	if (Click_Button_Sound == NULL)
	{
		LOG("Audio Click Mouse IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());
		
	}

	Click_Logo_Sound = Mix_LoadWAV("audio/fx/logoSplash_fx.wav");
	if (Click_Logo_Sound == NULL)
	{
		LOG("Audio Hover Logo IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	WarriorAttack_Sound = Mix_LoadWAV("audio/fx/warriorAttack_fx.wav");
	if (WarriorAttack_Sound == NULL)
	{
		LOG("Audio Warrior Attack IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	Spawner_Destroyed = Mix_LoadWAV("audio/fx/spawnDestruction_fx.wav");
	if (Spawner_Destroyed == NULL)
	{
		LOG("Audio Spawner destroyed IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	time_sound = Mix_LoadWAV("audio/fx/ding_fx.wav");
	if (time_sound == NULL)
	{
		LOG("Audio time IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	walkingPainter_sound = Mix_LoadWAV("audio/fx/walkingPainter_fx.wav");
	if (walkingPainter_sound == NULL)
	{
		LOG("Audio Walking Painter IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	walkingWarrior_sound = Mix_LoadWAV("audio/fx/walkingWarrior_fx.wav");
	if (walkingWarrior_sound == NULL)
	{
		LOG("Audio Walking Warrior IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	buy1_sound = Mix_LoadWAV("audio/fx/questAchieved_fx.wav");
	if (buy1_sound == NULL)
	{
		LOG("Audio Buy1 IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	buy2_sound = Mix_LoadWAV("audio/fx/woodProducerBuy_fx.wav");
	if (buy2_sound == NULL)
	{
		LOG("Audio Buy2 IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	spawnFromHall = Mix_LoadWAV("audio/fx/advancement_fx.wav");
	if (spawnFromHall == NULL)
	{
		LOG("Audio Spawn From Hall IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	birds_sound = Mix_LoadWAV("audio/fx/birds_fx.wav");
	if (birds_sound == NULL)
	{
		LOG("Audio Birds IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	crickets_sound = Mix_LoadWAV("audio/fx/crickets_fx.wav");
	if (crickets_sound == NULL)
	{
		LOG("Audio Crickets IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	braindead_sound = Mix_LoadWAV("audio/fx/braindead.wav");
	if (braindead_sound == NULL)
	{
		LOG("Audio Braindead IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	
	//AUDIO VOLUMES & STUFF
	
	VolumeMusic = 5;
	CurrentMusVolume = 5;
	CurrentFXVolume = 5;
	Mix_VolumeMusic(CurrentMusVolume);
	ChunkAudioManager(CurrentFXVolume);
	logoSound = false;

	return ret;
}

// Called before quitting
bool j1Audio::CleanUp() {
	if (!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	list<Mix_Chunk*>::const_iterator item;
	for (item = fx.begin(); item != fx.end(); item++)
		Mix_FreeChunk(*item);

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool j1Audio::PlayMusic(const char* path, float fade_time) {
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL) {
		if(fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int j1Audio::LoadFx(const char* path) {
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == NULL) {
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else {
		fx.push_back(chunk);
		ret = fx.size();
	}

	return ret;
}

// Play WAV
bool j1Audio::PlayFx(unsigned int id, int repeat) {
	bool ret = false;

	if (!active)
		return false;

	if(id > 0 && id <= fx.size()) {
		list< Mix_Chunk*>::const_iterator it;
		it = next(fx.begin(), id - 1);
		Mix_PlayChannel(-1, *it, repeat);
	}

	return ret;
}

bool j1Audio::Load(pugi::xml_node& save) {
	if (save.child("volume").attribute("default") != NULL) {
		generalVolume = save.child("volume").attribute("default").as_int();
		Mix_VolumeMusic(generalVolume);
	}

	return true;
}

void j1Audio::ChunkAudioManager(int volume)
{
	/*Mix_VolumeChunk(Click_Button_Sound, 10);
	Mix_VolumeChunk(walkingPainter_sound, 4);
	Mix_VolumeChunk(walkingWarrior_sound, 6);
	Mix_VolumeChunk(WarriorAttack_Sound, 5);
	Mix_VolumeChunk(buy1_sound, 6);
	Mix_VolumeChunk(buy2_sound, 6);
	Mix_VolumeChunk(spawnFromHall, 5);
	Mix_VolumeChunk(time_sound, 5);
	Mix_VolumeChunk(Spawner_Destroyed, 7);
	Mix_VolumeChunk(birds_sound, 1);
	Mix_VolumeChunk(crickets_sound, 2);
	Mix_VolumeChunk(braindead_sound, 50);*/

	Mix_VolumeChunk(Click_Button_Sound, volume);
	Mix_VolumeChunk(walkingPainter_sound, volume);
	Mix_VolumeChunk(walkingWarrior_sound, volume);
	Mix_VolumeChunk(WarriorAttack_Sound, volume);
	Mix_VolumeChunk(buy1_sound, volume);
	Mix_VolumeChunk(buy2_sound, volume);
	Mix_VolumeChunk(spawnFromHall, volume);
	Mix_VolumeChunk(time_sound, volume);
	Mix_VolumeChunk(Spawner_Destroyed, volume);
	Mix_VolumeChunk(birds_sound, volume);
	Mix_VolumeChunk(crickets_sound, volume);
	Mix_VolumeChunk(braindead_sound, volume);
	
	//if (!logoSound) {
	//	Mix_VolumeChunk(Click_Logo_Sound, 50);
	//	logoSound = true;
	//}
	//else {
	//	Mix_VolumeChunk(Click_Logo_Sound, 0);
	//}
}

bool j1Audio::Save(pugi::xml_node& save) const {

	if (save.child("volume") == NULL)
		save.append_child("volume").append_attribute("default") = generalVolume;
	else
		save.child("volume").attribute("default").set_value(generalVolume);

	return true;
}