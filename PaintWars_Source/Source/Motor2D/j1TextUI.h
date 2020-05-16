
#include "j1UIElements.h"


class j1TextUI : public j1UIElement
{
public:

	j1TextUI();
	~j1TextUI();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


private:

	int font_name = -1;
};