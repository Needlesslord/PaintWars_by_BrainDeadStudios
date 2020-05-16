#ifndef __CUT_H__
#define __CUT_H__

#include "Transition.h"

class Cut : public Transition
{
public:
	Cut(SCENES next_scene);
	~Cut();

	void StepTransition();

private:

};

#endif // !__CUT_H__

