
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

	int font_name_black = -1;
	int font_name_white = -1;
	int font_name_black_small = -1;
	int font_name_white_small = -1;
	int font_name_black_extra_small = -1;
	int font_name_white_extra_small = -1;
	int font_name_red = -1;
	int font_name_red_small = -1;
	int font_name_red_extra_small = -1;
};