#ifndef __j1VIDEO_H__
#define __j1VIDEO_H__

#include "j1Module.h"

//Video player for windows libraries
#include <dshow.h>
#include <Vfw.h>                          
#pragma comment(lib,"vfw32.lib")               


class j1Video : public j1Module
{
public:

	j1Video();

	// Destructor
	virtual ~j1Video();
	bool Update(float dt);

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	void Initialize(char* path);
	void OpenAVI(char* path);
	bool GrabAVIFrame();

	void CloseAVI();

public:
	bool				isVideoFinished = true;

private:
	// Frame Counter
	int			frame = 0;							

	AVISTREAMINFO       psi;                        // Pointer To A Structure Containing Stream Info
	PAVISTREAM			pavi;                       // Handle To An Open Stream
	PGETFRAME			pgf;                        // Pointer To A GetFrame Object

	long				lastFrame;                  // Last Frame Of The Stream
	int					width;                      // Video Width
	int					height;                     // Video Height
	char*				pdata;					    // Pointer To Texture Data
	int					mpf;                        // Will Hold Rough Milliseconds Per Frame

	int i = 1;
};

#endif // __j1Video_H__
