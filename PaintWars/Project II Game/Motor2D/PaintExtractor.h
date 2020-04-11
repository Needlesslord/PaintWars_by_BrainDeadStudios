#ifndef __PaintExtractor_H__
#define __PaintExtractor_H__


#include "Entity.h"

class PaintExtractor : public Entity
{
public:

	PaintExtractor(fPoint pos, int currLife, j1Module* listener);
	~PaintExtractor();

public:

private:

	bool startTimer = true;

};

#endif //__PaintExtractor_H__