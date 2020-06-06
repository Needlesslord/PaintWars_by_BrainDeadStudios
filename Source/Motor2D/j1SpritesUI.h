
#include "j1UIElements.h"

class j1UISprites : public j1UIElement
{
public:

	j1UISprites();
	~j1UISprites();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


private:

	
};