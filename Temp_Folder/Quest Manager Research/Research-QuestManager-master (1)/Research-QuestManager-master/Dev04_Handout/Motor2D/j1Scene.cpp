#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Fruit.h"
#include "j1QuestManager.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("map.tmx");
	score = 0;
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//scoreboard
	DrawQ0();
	
	App->map->Draw();
	
	OrderEvent();
	CheckEvent();
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;


}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(graphics);

	return true;
}

void j1Scene::DrawQ0()
{
	App->render->DrawLine(936, 168, 952, 184, 150, 9, 21, 255);
	App->render->DrawLine(936, 184, 952, 168, 150, 9, 21, 255);

	App->render->DrawLine(968, 168, 984, 184, 150, 9, 21, 255);
	App->render->DrawLine(968, 184, 984, 168, 150, 9, 21, 255);

	App->render->DrawLine(1000, 168, 1016, 184, 150, 9, 21, 255);
	App->render->DrawLine(1000, 184, 1016, 168, 150, 9, 21, 255);

	App->render->DrawLine(1032, 168, 1048, 184, 150, 9, 21, 255);
	App->render->DrawLine(1032, 184, 1048, 168, 150, 9, 21, 255);

	App->render->DrawLine(1064, 168, 1080, 184, 150, 9, 21, 255);
	App->render->DrawLine(1064, 184, 1080, 168, 150, 9, 21, 255);
}

void j1Scene::DrawQ1()
{
	App->render->DrawQuad(test, 255, 0, 0, 100);
	App->render->DrawQuad(test2, 255, 127, 0, 100);
	App->render->DrawQuad(test3, 255, 255, 0, 100);
	App->render->DrawQuad(test4, 0, 255, 0, 100);
	App->render->DrawQuad(test5, 0, 0, 255, 100);
	App->render->DrawQuad(test6, 75, 0, 130, 100);
	App->render->DrawQuad(test7, 143, 0, 255, 100);
}

void j1Scene::DrawQ2()
{
	App->render->DrawQuad(ray, 255, 0, 0, 200);
	App->render->DrawQuad(ray2, 255, 127, 0, 200);
	App->render->DrawQuad(ray3, 255, 255, 0, 200);
	App->render->DrawQuad(ray4, 0, 255, 0, 200);
	App->render->DrawQuad(ray5, 0, 0, 255, 200);
	App->render->DrawQuad(ray6, 75, 0, 130, 200);
	App->render->DrawQuad(ray7, 143, 0, 255, 200);
	
}

void j1Scene::DrawQ3()
{
	App->render->DrawCircle(1008, 176, 2, 255, 0, 0, 200);
	App->render->DrawCircle(1008, 176, 4, 255, 127, 0, 200);
	App->render->DrawCircle(1008, 176, 6, 255, 255, 0, 200);
	App->render->DrawCircle(1008, 176, 10, 0, 255, 0, 200);
	App->render->DrawCircle(1008, 176, 12, 0, 255, 200);
	App->render->DrawCircle(1008, 176, 14, 75, 0, 130, 200);
	App->render->DrawCircle(1008, 176, 16, 143, 0, 255, 200);


}

void j1Scene::DrawQ4()
{
	App->render->DrawCircle(1032, 168, 4, 150, 9, 21, 255);
	App->render->DrawCircle(1048, 168, 4, 247, 225, 79, 255);
	App->render->DrawCircle(1040, 176, 4, 245, 105, 24, 255);
	App->render->DrawCircle(1032, 184, 4, 235, 14, 14, 255);
	App->render->DrawCircle(1048, 184, 4, 255, 215, 0, 255);
}

void j1Scene::DrawQ5()
{
	App->render->DrawLine(1058, 162, 1074, 178, 235, 14, 14, 255);
	App->render->DrawLine(1070, 178, 1086, 162, 235, 14, 14, 255);
	App->render->DrawLine(1058, 174, 1074, 190, 235, 14, 14, 255);
	App->render->DrawLine(1070, 190, 1086, 174, 235, 14, 14, 255);

	App->render->DrawLine(1060, 164, 1076, 180, 245, 105, 24, 255);
	App->render->DrawLine(1068, 180, 1084, 164, 245, 105, 24, 255);
	App->render->DrawLine(1060, 172, 1076, 188, 245, 105, 24, 255);
	App->render->DrawLine(1068, 188, 1084, 172, 245, 105, 24, 255);

	App->render->DrawLine(1062, 166, 1078, 182, 247, 225, 79, 255);
	App->render->DrawLine(1066, 182, 1082, 166, 247, 225, 79, 255);
	App->render->DrawLine(1062, 170, 1078, 186, 247, 225, 79, 255);
	App->render->DrawLine(1066, 186, 1082, 170, 247, 225, 79, 255);

	App->render->DrawLine(1064, 168, 1080, 184, 150, 9, 21, 255);
	App->render->DrawLine(1064, 184, 1080, 168, 150, 9, 21, 255);

}

//TODO 5: Now that we have our base working, it's time to implement it with the context, 
//therefore we are gonna create a simple function that checks the events that we are interested in. 
//The skeleton is already implemented, therefore you will only need to fill the loop that will iterate the active_quests list and checks those conditions

void j1Scene::CheckEvent()
{
	for (std::list <Quest*>::iterator it = App->quest_manager->active_quests.begin(); it != App->quest_manager->active_quests.end(); it++) 
	{
		int quest_id = (*it)->id;

		switch (quest_id)
		{
		case 1:
			if (cherry == true && banana == true && orange == true && watermelon == true && mango == true && r > -1)
			{
				(*it)->completed = true;
				r++;
				App->fruit->Restart();
				App->quest_manager->finished_quests.push_back((*it));
				App->quest_manager->active_quests.erase(it);
			}
			break;
		case 2:
			if (cherry == true && banana == true && orange == true && watermelon == true && mango == true && r > 0)
			{
				(*it)->completed = true;
				r++;
				App->fruit->Restart();
				App->quest_manager->finished_quests.push_back((*it));
				App->quest_manager->active_quests.erase(it);
			}
			break;
		case 3:
			if (cherry == true && banana == true && orange == true && watermelon == true && mango == true && r > 2)
			{
				(*it)->completed = true;
				r++;
				App->fruit->Restart();
				App->quest_manager->finished_quests.push_back((*it));
				App->quest_manager->active_quests.erase(it);
			}
			break;
		case 4:
			if (cherry == true && banana == true && orange == true && watermelon == true && mango == true && score == 4)
			{
				(*it)->completed = true;
				r++;
				App->fruit->Restart();
				App->quest_manager->finished_quests.push_back((*it));
				App->quest_manager->active_quests.erase(it);
			}
			break;
		case 5:
			if (cherry == true && banana == true && orange == true && watermelon == true && mango == true && r > 3)
			{
				(*it)->completed = true;
				App->fruit->Restart();
				App->quest_manager->finished_quests.push_back((*it));
				App->quest_manager->active_quests.erase(it);
			}
			break;
		default:
			break;
		}
		
		//TODO 6: We are almost done, we are currently correctly checking the active_quests list but we aren't doing anything with a quest
		// once it's completed, therefore we need to transfer the complete quests to the finished_quests list 
	}
	
	//TODO 7: As the final TODO, just take a look at how we are only drawing an achievement (quest completed) once they are in the finished_quests list
	// I'd also like you to take a look at how we make the 4th achievement a different quest by forcing the player to complete the side-quests in a particular order
	for (std::list <Quest*>::iterator it = App->quest_manager->finished_quests.begin(); it != App->quest_manager->finished_quests.end(); it++)
	{
		int quest_id = (*it)->id;

		switch (quest_id)
		{
		case 1:
			DrawQ1();
			break;
		case 2:
			DrawQ2();
			break;
		case 3:
			DrawQ3();
			break;
		case 4:
			DrawQ4();
			break;
		case 5:
			DrawQ5();
			break;
		default:
			break;
		}
	}
	
}

void j1Scene::OrderEvent()
{
	if (cherry == true && App->fruit->b_points == 0 && App->fruit->o_points == 0 && App->fruit->w_points == 0 && App->fruit->m_points == 0) {
		score = 1;
	}
	if (cherry == true && banana == true && App->fruit->o_points == 0 && App->fruit->w_points == 0 && App->fruit->m_points == 0) {
		score = 2;
	}
	if (cherry == true && banana == true && orange == true && App->fruit->w_points == 0 && App->fruit->m_points == 0) {
		score = 3;
	}
	if (cherry == true && banana == true && orange == true && watermelon == true && App->fruit->m_points == 0) {
		score = 4;
	}
}
