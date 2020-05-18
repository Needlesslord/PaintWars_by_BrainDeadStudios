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
	MinimapCameraBufferX = 0;
	MinimapCameraBufferY = 0;
	LOG("Player Started");
	Tex_Player = App->tex->Load("textures/UI/UI_mouse.png");
	App->win->GetWindowSize( win_width,win_height);
	SDL_ShowCursor(SDL_DISABLE);


	V = 0;
	


	return ret;
}

bool j1Player::PreUpdate()
{
	
	



	
	//list<Entity*>::iterator entityCount = App->entities->activeEntities.begin();
	//int B = 0;
	//int P = 0;


	//if (V != 1) {

	//	while (entityCount != App->entities->activeEntities.end()) {


	//		MiniMapEntities_Squares[B] = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { 1000,520 /*(*entityCount)->pos.x ,(*entityCount)->pos.y*/ }, { 0 , 0 }, false, true, { 4, 3, 2, 3 },
	//			nullptr, nullptr, TEXTURE::MINIMAP_ENTITIES);

	//		

	//		

	//		MiniMapEntities_Squares[B]->map_position.x = MiniMapEntities_Squares[B]->init_map_position.x + App->render->camera.x + (*entityCount)->currentTile.x;
	//		MiniMapEntities_Squares[B]->map_position.y = MiniMapEntities_Squares[B]->init_map_position.y + App->render->camera.y + (*entityCount)->currentTile.y;

	//		entityCount++;

	//		B++;
	//		
	//	}
	//	
	//}

	//if (entityCount != App->entities->activeEntities.end()) {
	//	V = 1;
	//}



	//LOG("ENTITY POSITION X,Y = %f %f", MiniMapEntities_Squares[B]->map_position.x, MiniMapEntities_Squares[B]->map_position.x);
	
	
	
	
	


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

	
	if (App->PAUSE_ACTIVE == false) {
		if (App->scenes->IN_GAME_SCENE == true) {
			p2List_item<j1UIElement*>* UI_List = App->gui->GUI_ELEMENTS.start;
			while (UI_List != NULL)
			{


				if (App->gui->GUI_ELEMENTS[z]->textureType == TEXTURE::MINIMAP_CAMERA) {



					App->gui->GUI_ELEMENTS[z]->map_position.x = App->gui->GUI_ELEMENTS[z]->init_map_position.x + App->render->camera.x - MinimapCameraBufferX;
					App->gui->GUI_ELEMENTS[z]->map_position.y = App->gui->GUI_ELEMENTS[z]->init_map_position.y + App->render->camera.y - MinimapCameraBufferY;

					
				}
				else if (App->gui->GUI_ELEMENTS[z]->textureType == TEXTURE::MINIMAP_ENTITIES) {


					

				}
				else {

					//LOG("UI COUNT IS %d", z);
					App->gui->GUI_ELEMENTS[z]->map_position.x = App->gui->GUI_ELEMENTS[z]->init_map_position.x + App->render->camera.x;
					App->gui->GUI_ELEMENTS[z]->map_position.y = App->gui->GUI_ELEMENTS[z]->init_map_position.y + App->render->camera.y;





					/*if (App->gui->GUI_ELEMENTS[z]->textureType == TEXTURE::MINIMAP_ENTITIES) {

						LOG("SQUARE POSITION X=%f, Y=%f ", App->gui->GUI_ELEMENTS[z]->map_position.x, App->gui->GUI_ELEMENTS[z]->map_position.y);
					}*/
					
				}


		

				UI_List = UI_List->next;
				++z;
			}
		}
	}
	Select_Entities(selector);


	int B = 0;
	
	
	list<Entity*>::iterator entityCount = App->entities->activeEntities.begin();
	while (entityCount != App->entities->activeEntities.end()) {

		

		/*MiniMapEntities_Squares[B] = App->gui->AddElement(TypeOfUI::GUI_IMAGE, nullptr, { (*entityCount)->pos.x ,  (*entityCount)->pos.y}, { 0 , 0 }, 
		false, true, { 4, 3, 2, 3 }, nullptr, nullptr, TEXTURE::MINIMAP_ENTITIES);
		*/


		entityCount++;
		B++;
	}




	return true;
}

bool j1Player::CleanUp()
{

	return true;

}

void j1Player::Camera_Control(float dt)
{
	int z = 0;
	if (App->scenes->current_scene->scene_name == SCENES::GAME_SCENE)
	{
		if (App->PAUSE_ACTIVE==false) {
			
			if (mouse_position.x == 0 && App->render->camera.x <= 3750)
			{
				//LOG("Camera x at %d", App->render->camera.x);
				App->render->camera.x += camera_speed * dt * 1000;
				//1242X
				//695Y
				
				MinimapCameraBufferX = MinimapCameraBufferX + 1.1;
			}

			if (mouse_position.y == 0)
			{
				//LOG("Camera y at %d", App->render->camera.y);
				App->render->camera.y += camera_speed * dt * 1000;

				if (App->render->camera.y < 50) {
					MinimapCameraBufferY = MinimapCameraBufferY + 1.1;
				}
			}


			if (mouse_position.x > (win_width - camera_offset) / App->win->scale )
			{
				//LOG("Camera x at %d", App->render->camera.x);
				App->render->camera.x -= camera_speed * dt * 1000;
				if (App->render->camera.x > -2900) {
					MinimapCameraBufferX = MinimapCameraBufferX - 1.1;
				}

			}


			if (mouse_position.y > (win_height - camera_offset) / App->win->scale)
			{
				//LOG("Camera y at %d", App->render->camera.y);
				App->render->camera.y -= camera_speed * dt * 1000;
				if (App->render->camera.y > -3150) {
					MinimapCameraBufferY = MinimapCameraBufferY - 1.1;
				}
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

				//has to update camera minimap

				if (App->scenes->Map_Forest_Active) {
					App->render->camera.x = 575;
					App->render->camera.y = -1200;
					MinimapCameraBufferX = 0;
					MinimapCameraBufferY = 0;
				}
				if (App->scenes->Map_Snow_Active) {
					App->render->camera.x = -329;
					App->render->camera.y = -608;
					MinimapCameraBufferX = -24;
					MinimapCameraBufferY = 15;
				}
				if (App->scenes->Map_Volcano_Active) {
					App->render->camera.x = 700;
					App->render->camera.y = 10;
					MinimapCameraBufferX = 4.39;
					MinimapCameraBufferY = 33;
				}
			}
		}

		
	}


	Mouse_Cursor();
}

void j1Player::Select_Entities(SDL_Rect select_area)
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




