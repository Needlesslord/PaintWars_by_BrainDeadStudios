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

	Warrior_Sound = Mix_LoadWAV("audio/fx/warrior_fx.wav");
	if (Warrior_Sound == NULL)
	{
		LOG("Audio Warrior IS NOT WORKING! SDL_mixer Error: %s\n", Mix_GetError());

	}

	
	//AUDIO VOLUMES & STUFF
	ChunkAudioManager();
	VolumeMusic = 5;
	Mix_VolumeMusic(VolumeMusic);

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

void j1Audio::ChunkAudioManager()
{
	Mix_VolumeChunk(Click_Button_Sound, 10);
	
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