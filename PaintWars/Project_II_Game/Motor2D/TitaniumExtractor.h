#ifndef __TitaniumExtractor_H__
#define __TitaniumExtractor_H__


#include "Entity.h"

class TitaniumExtractor : public Entity
{
public:

	TitaniumExtractor(iPoint tile, int damage, j1Module* listener, Entity* creator);
	~TitaniumExtractor();
	void ExtractTitanium(float dt) override;


public:

private:

	bool startTimer = true;

};

#endif //__TitaniumExtractor_H__