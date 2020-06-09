#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "j1Video.h"
#include "j1Input.h"

j1Video::j1Video() : j1Module()
{
	name = ("video");
}

j1Video::~j1Video()
{
}

bool j1Video::Update(float dt)
{
	if (!isVideoFinished)
	{
		GrabAVIFrame();
	}else
		//Mix_PauseMusic();
	return true;
}

bool j1Video::Awake(pugi::xml_node &)
{
	return true;
}

bool j1Video::CleanUp()
{
	return true;
}

void j1Video::Initialize(char* path)
{
	OpenAVI(path);                  // Open The AVI File
}

void j1Video::OpenAVI(char* path)
{
	if (AVIStreamOpenFromFile(&pavi, path, streamtypeVIDEO, 0, OF_READ, NULL) != 0) // Opens The AVI Stream
		LOG("Failed To Open The AVI Stream");


	AVIStreamInfo(pavi, &psi, sizeof(psi));					// Reads Information About The Stream Into psi
	width = psi.rcFrame.right - psi.rcFrame.left;           // Width Is Right Side Of Frame Minus Left
	height = psi.rcFrame.bottom - psi.rcFrame.top;          // Height Is Bottom Of Frame Minus Top
	lastFrame = AVIStreamLength(pavi);						// The Last Frame Of The Stream


	pgf = AVIStreamGetFrameOpen(pavi, (LPBITMAPINFOHEADER)AVIGETFRAMEF_BESTDISPLAYFMT);              // Create The PGETFRAME Using Our Request Mode
	if (pgf == NULL)
		LOG("Failed To Open The AVI Frame");	

	isVideoFinished = false;
}

bool j1Video::GrabAVIFrame()
{
	
	LPBITMAPINFOHEADER lpbi;													// Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);					// Grab Data From The AVI Stream
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);    // Pointer To Data Returned By AVIStreamGetFrame
																				// (Skip The Header Info To Get To The Data)
																				// Convert Data To Requested Bitmap Format
	
	
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pdata, width, height, lpbi->biBitCount, width * 3, 0, 0, 0, 0);
	SDL_Texture* texture = App->tex->LoadSurface(surface);


	App->render->RenderQueueUI(2, texture, 0, 0, { 0, 0, 2560, 1440 }, SDL_FLIP_VERTICAL);


	if (i % 2 == 0)
	{
		frame++;
	}
	i++;
	if (frame >= lastFrame || App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		frame = 0;
		isVideoFinished = true; 
		Mix_HaltMusic();
	}
	
	
	App->tex->UnLoad(texture);
	SDL_FreeSurface(surface);


	
	char   title[100];                     
	mpf = AVIStreamSampleToTime(pavi, lastFrame) / lastFrame;        // Calculate Rough Milliseconds Per Frame
	wsprintf(title, "AVI Player: Width: %d, Height: %d, Frames: %d, Miliseconds per frame: %d", width, height, lastFrame, mpf);
	App->win->SetTitle(title);
	
	return true;
}

void j1Video::CloseAVI()
{
	AVIStreamGetFrameClose(pgf);                // Deallocates The GetFrame Resources

	AVIStreamRelease(pavi);                     // Release The Stream

	AVIFileExit();                              // Release The File
}
