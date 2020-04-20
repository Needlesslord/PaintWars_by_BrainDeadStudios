#include "p2Defs.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1EntityManager.h"
#include "j1Window.h"
#include "j1UI_manager.h"
#include "Scene.h"
#include "j1Timer.h"



j1Player::j1Player() : j1Module()
{

	name = ("player");
}


j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;

	folder = (config.child("folder").child_value());

	camera_speed = config.child("camera").attribute("speed").as_int(1);
	camera_offset = config.child("camera").attribute("offset").as_int(10);

	node = config;
	return ret;
}


bool j1Player::Start() {
	bool ret = true;
	LOG("Player Started");
	Tex_Player = App->tex->Load("textures/Cursor3.png");
	App->win->GetWindowSize( win_width,win_height);
	SDL_ShowCursor(SDL_DISABLE);


	return ret;
}

bool j1Player::PreUpdate()
{

	return true;
}

bool j1Player::Save(pugi::xml_node& data)
{
	//PLAYER POSITION
	LOG("Loading player state");
	mouse_position.x = data.child("position").attribute("X").as_int();
	mouse_position.y = data.child("position").attribute("Y").as_int();
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	//PLAYER POSITION
	LOG("Loading player state");
	mouse_position.x = data.child("position").attribute("X").as_int();
	mouse_position.y = data.child("position").attribute("Y").as_int();
	return true;
}

bool j1Player::Update(float dt)
{
	int z = 0;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);

	Camera_Control(dt);
	Zoom();

	//This functions should always be last//
	//Mouse_Cursor();
	 

	p2List_item<j1UIElement*>* UI_List = App->gui->GUI_ELEMENTS.start;
	while (UI_List != NULL)
	{
		LOG("UI COUNT IS %d", z);
		App->gui->GUI_ELEMENTS[z]->map_position.x = App->gui->GUI_ELEMENTS[z]->init_map_position.x + App->render->camera.x;
		App->gui->GUI_ELEMENTS[z]->map_position.y = App->gui->GUI_ELEMENTS[z]->init_map_position.y + App->render->camera.y;


		UI_List = UI_List->next;
		++z;


	}

	
	return true;
}

bool j1Player::CleanUp()
{

	return true;

}

void j1Player::Camera_Control(float dt)
{
	if (App->scenes->current_scene->scene_name == SCENES::GAME_SCENE)
	{
		if (App->PAUSE_ACTIVE==false) {

			if (mouse_position.x == 0 && App->render->camera.x <= 3750)
			{
				App->render->camera.x += camera_speed * dt * 1000;
			}

			if (mouse_position.y == 0)
			{
				App->render->camera.y += camera_speed * dt * 1000;
			}


			if (mouse_position.x > (win_width - camera_offset) / App->win->scale)
			{
				App->render->camera.x -= camera_speed * dt * 1000;
			}


			if (mouse_position.y > (win_height - camera_offset) / App->win->scale)
			{
				App->render->camera.y -= camera_speed * dt * 1000;
			}

			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
				App->render->camera.y += camera_speed * dt * 1000;

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
				App->render->camera.y -= camera_speed * dt * 1000;

			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
				App->render->camera.x += camera_speed * dt * 1000;

			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
				App->render->camera.x -= camera_speed * dt * 1000;

			if (App->render->camera.x < -2900)
				App->render->camera.x = -2900;
			if (App->render->camera.x > 3800)
				App->render->camera.x = 3800;
			if (App->render->camera.y > 50)
				App->render->camera.y = 50;
			if (App->render->camera.y < -3150)
				App->render->camera.y = -3150;
			

			if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT) {

				App->render->camera.x = 0;
				App->render->camera.y = 0;
			}
		}

		//UI
		//for (int i = 0; i < 21/*App->gui->GUI_ELEMENTS.count()*/; i++)
		//{
		//	if ((i > 9) && (i < 20)) {
		//		App->gui->GUI_ELEMENTS[i]->map_position.x = App->gui->GUI_ELEMENTS[i]->init_map_position.x + App->render->camera.x;
		//		App->gui->GUI_ELEMENTS[i]->map_position.y = App->gui->GUI_ELEMENTS[i]->init_map_position.y + App->render->camera.y;
		//		/*App->gui->GUI_ELEMENTS[i]->click_rect.x=App->gui->GUI_ELEMENTS[i]->init_map_position.x + App->render->camera.x;
		//		App->gui->GUI_ELEMENTS[i]->click_rect.y = App->gui->GUI_ELEMENTS[i]->init_map_position.y + App->render->camera.y;
		//		App->gui->GUI_ELEMENTS[i]->hover_rect.x= App->gui->GUI_ELEMENTS[i]->init_map_position.x + App->render->camera.x;
		//		App->gui->GUI_ELEMENTS[i]->hover_rect.y = App->gui->GUI_ELEMENTS[i]->init_map_position.y + App->render->camera.y;*/
		//	}
		//}

		App->render->RenderQueueUI(1, App->entities->zeroLifeTexture, 550 + App->render->camera.x*-2 / 2, 50 + App->render->camera.y*-2 / 2, { 0, 0, 200, 15 }, false, true, 0);
		App->render->RenderQueueUI(1, App->entities->fullLifeTexture, 550 + App->render->camera.x*-2 / 2,  50+App->render->camera.y*-2 / 2, { 0, 0, (int)App->entities->Entity_HP, 15 }, false, true, 0);
		
		

		/*while (App->gui->GUI_ELEMENTS)
		{
			if (id < item->data->firstgid)
			{
				set = item->prev->data;
				break;
			}
			set = item->data;
			item = item->next;
		}*/
	}


	Mouse_Cursor();
}

void j1Player::Select_Entitites(SDL_Rect select_area)
{
	int buffer;
	if (select_area.x > select_area.x + select_area.w)
	{
		select_area.x = select_area.x + select_area.w;
		select_area.w *= -1;
	}

	if (select_area.y > select_area.y + select_area.h)
	{
		select_area.y = select_area.y + select_area.h;
		select_area.h *= -1;
	}
	//LOG("Ax -> %d | Ay -> %d | Aw -> %d | Ah -> %d", select_area.x, select_area.y, select_area.w, select_area.h);

}

void j1Player::Mouse_Cursor() 
{
	mouse_position.x -= App->render->camera.x / App->win->GetScale();
	mouse_position.y -= App->render->camera.y / App->win->GetScale();
	App->render->RenderQueueUI(10,Tex_Player, mouse_position.x, mouse_position.y, texture_rect);
	
}


void j1Player::Zoom()
{
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_REPEAT) //zoom IN
	{
		App->win->scale = App->win->scale + 0.001;
	}
	else if (App->input->GetKey(SDL_SCANCODE_0) == KEY_REPEAT)//zoom OUT
	{
		App->win->scale = App->win->scale - 0.001;
	}

	else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)//zoom RESET
	{
		App->win->scale = 0.5;
	}
}




