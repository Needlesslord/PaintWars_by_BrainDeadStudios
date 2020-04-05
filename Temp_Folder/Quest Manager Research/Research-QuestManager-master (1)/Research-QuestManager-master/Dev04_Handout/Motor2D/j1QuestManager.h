#include "j1Module.h"
#include "p2Point.h"
#include <vector>
#include <list>
#include "SDL/include/SDL_rect.h"


//TODO 0: Start by taking a look at the basis I showed you above and make sure you understand the elements of the Quest System Structure and the Quests

//TODO 1: Once you've understood this, take a bit more time to read and observe the syntax of the xml that we will be using to load the data called quest_data

class Quest
{
public:

	Quest() {};
	~Quest() ;
	
	int id; 
	int trigger;
	int reward;
	int requisites;
	int type;

	std::string title;
	std::string description;

	bool completed = false;
};


class j1QuestManager : public j1Module 
{
public:

	j1QuestManager();
	~j1QuestManager();

	bool Awake(pugi::xml_node& file);
	bool Start();

	pugi::xml_document quest_data;

	std::list<Quest*> loaded_quests;
	std::list<Quest*> active_quests;
	std::list<Quest*> finished_quests;
};


