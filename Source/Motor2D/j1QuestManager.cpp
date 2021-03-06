#include "j1QuestManager.h"
#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"
#include <vector>
#include "j1App.h"


j1QuestManager::j1QuestManager() {}


j1QuestManager::~j1QuestManager()
{
	for (std::list <Quest*>::iterator it = loaded_quests.begin(); it != loaded_quests.end(); it++)
	{
		loaded_quests.erase(it);
	}
	for (std::list <Quest*>::iterator it = active_quests.begin(); it != active_quests.end(); it++)
	{
		active_quests.erase(it);
	}
	for (std::list <Quest*>::iterator it = finished_quests.begin(); it != finished_quests.end(); it++)
	{
		finished_quests.erase(it);
	}
}


bool j1QuestManager::Awake(pugi::xml_node& config)
{
	LOG("STARTING QUEST_MANAGER");

	pugi::xml_node quest_node;
	quest_node = App->LoadQuests(quest_data);  

	if (quest_node == NULL)
	{
		LOG("Could not load quests_file.xml");
	}

	for (quest_node = quest_node.child("quest"); quest_node; quest_node = quest_node.next_sibling("quest"))
	{


		Quest* new_quest = new Quest();

		new_quest->id = quest_node.attribute("id").as_int();
		new_quest->title = quest_node.attribute("title").as_string();
		new_quest->type = quest_node.attribute("type").as_int();
		new_quest->trigger = quest_node.attribute("trigger").as_int();
		new_quest->description = quest_node.attribute("description").as_string();
		new_quest->reward = quest_node.attribute("reward").as_int();
		new_quest->requisites = quest_node.attribute("requisites").as_int();

	
		if (new_quest->trigger == 1)
		{
			active_quests.push_back(new_quest);
		}
		else
		{
			loaded_quests.push_back(new_quest);
		}

	}

	return true;
}


bool j1QuestManager::Start()
{


	return true;

}