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
#include "j1GUI.h"


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
	Tex_Player = App->tex->Load("textures/Cursor.png");
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
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);

	Camera_Control(dt);
	Zoom();

	//This functions should always be last//
	Mouse_Cursor();
	Drag_Mouse(); 
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
		if (mouse_position.x == 0 && App->render->camera.x <= 3750)
			App->render->camera.x += camera_speed * dt * 1000;

		if (mouse_position.y == 0)
			App->render->camera.y += camera_speed * dt * 1000;

		if (mouse_position.x > (win_width - camera_offset) / App->win->scale)
			App->render->camera.x -= camera_speed * dt * 1000;

		if (mouse_position.y > (win_height - camera_offset) / App->win->scale)
			App->render->camera.y -= camera_speed * dt * 1000;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->render->camera.y += camera_speed * dt * 1000;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->render->camera.y -= camera_speed * dt * 1000;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->render->camera.x += camera_speed * dt * 1000;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->render->camera.x -= camera_speed * dt * 1000;

		if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_REPEAT) {

			App->render->camera.x = 0;
			App->render->camera.y = 0;
		}
	}
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
	App->render->AddBlitEvent(5,Tex_Player, mouse_position.x, mouse_position.y, texture_rect);
}

void j1Player::Drag_Mouse()
{

	if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		App->input->GetMousePosition(start_mouse_position.x, start_mouse_position.y);
		start_mouse_position.x -= App->render->camera.x / App->win->GetScale();
		start_mouse_position.y -= App->render->camera.y / App->win->GetScale();
	}

	if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
	{
		selector = { (int)start_mouse_position.x, (int)start_mouse_position.y, (int)(mouse_position.x - start_mouse_position.x), (int)(mouse_position.y - start_mouse_position.y) };
		App->render->AddBlitEvent(2, nullptr, 0,0, selector, false, false, 0.0f, 0u, 255u, 0u, 25u);
	}

	if (App->input->GetMouseButtonDown(1) == KEY_UP)
	{
		if (selector.w > 1)
			App->entities->SelectGroupEntities(selector);
		//Select_Entitites(selector);
	}

}

void j1Player::Zoom()
{
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT) //zoom IN
	{
		App->win->scale = App->win->scale + 0.001;
	}
	else if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)//zoom OUT
	{
		App->win->scale = App->win->scale - 0.001;
	}

	else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)//zoom RESET
	{
		App->win->scale = 0.5;
	}
}




