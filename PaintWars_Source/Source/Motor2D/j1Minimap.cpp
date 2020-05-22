//#include "j1Minimap.h"
//
//#include "j1App.h"
//#include "j1Window.h"
//#include "j1Render.h"
//#include "j1Textures.h"
//#include "j1Input.h"
//
//#include "j1Map.h"
//#include "Entity.h"
//#include "j1EntityManager.h"
//
//#include "p2Log.h"
//
//#include <list>
//
//j1Minimap::j1Minimap()
//{
//	name = "minimap";
//}
//
//j1Minimap::~j1Minimap() {}
//
//bool j1Minimap::Awake(pugi::xml_node & config)
//{
//	//You can change the values on the file to adapt the minimap to the one you want
//	//The size must be an integer and it ranges from 1 to tile_height
//	//Both are alredy declared on the minimap class
//	size = config.attribute("size").as_int();
//	position.x= config.attribute("position.x").as_int();
//	position.y= config.attribute("position.y").as_int();
//
//	return true;
//}
//
//bool j1Minimap::Start()
//{
//	display = true;
//	entities_mode = entity_display::DISPLAY_RECT;
//	Load();
//
//	return true;
//}
//
//
//bool j1Minimap::Update(float dt)
//{	
//	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
//	{
//		int map_x, map_y;
//		
//		//If we are clicking on the minimap translate the minimap coordinates to map coordinates
//		if (MinimapCoords(map_x, map_y))
//		{
//			//Remember the camera parameters are negative
//			App->render->camera.x = -map_x + App->win->width / 2;
//			App->render->camera.y = -map_y + App->win->height / 2;
//		}
//	}
//
//	return true;
//}
//
//bool j1Minimap::PostUpdate()
//{	
//	if (display) {
//		App->render->Blit(minimap_tex, position.x, position.y, NULL, false);
//		MinimapBorders();
//		switch (entities_mode) {
//		case entity_display::DISPLAY_RECT:
//			DrawEntitiesRectangle();
//			break;
//		case entity_display::DISPLAY_ENTITY:
//			DrawEntities();
//			break;
//		case entity_display::DISPLAY_ICON:
//			DrawEntitiesIcon();
//			break;
//		}
//		DrawCamera();
//	}
//	
//	return true;
//}
//
//bool j1Minimap::CleanUp()
//{
//	SDL_DestroyTexture(minimap_tex);
//
//	return true;
//}
//
//void j1Minimap::Load() {
//	if (App->map->active)
//	{
//		//The scale must always be a divider of the tile_height. 
//		//If not, we will get floats when drawing the map that will get approximated to integers when creating the SDL_Rect to blit each tile and the minimap will not be blited correctly
//		//The minimap_scale variable is already initialized on the minimap class
//		minimap_scale = (float)size / (float)App->map->data.tile_height;
//
//		float map_width = App->map->data.width * App->map->data.tile_width;
//		minimap_width = map_width * minimap_scale;
//		float map_height = App->map->data.height * App->map->data.tile_height;
//		minimap_height = map_height * minimap_scale;
//
//		//Make sure the texture accses is the corret one to make the texture accsesible for the renderer
//		//The texture size should be the minimap width and height
//		//The minimap_tex variable is already initialized on the minimap class
//		minimap_tex = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, minimap_width, minimap_height);
//		SDL_SetRenderTarget(App->render->renderer, minimap_tex);
//	}
//	DrawMinimap();
//
//	SDL_SetRenderTarget(App->render->renderer, NULL);
//	SDL_SetTextureBlendMode(minimap_tex, SDL_BLENDMODE_BLEND);
//}
//
//bool j1Minimap::MinimapCoords(int& map_x, int& map_y)
//{
//	int mouse_x, mouse_y;
//	App->input->GetMousePosition_UI(mouse_x, mouse_y);
//
//	//if we click inside the minimap
//	if (mouse_x >= position.x && mouse_x <= minimap_width +position.x	&&	mouse_y >= position.y && mouse_y <= minimap_height+position.y) 
//	{
//		//Remember that we multiply for the scale to translate from map to minimap so to translate backwards we should do the opposite
//		// Take into account that in the isometric map the position x=0 starts at the center of the map
//		// Remember to remove the offset of the position of the minimap on the screen
//		
//		if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
//			map_x = ((mouse_x - position.x) / minimap_scale);
//			map_y = ((mouse_y - position.y) / minimap_scale);
//		}
//		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
//			map_x = ((mouse_x - position.x - minimap_width / 2) / minimap_scale);
//			map_y = ((mouse_y - position.y) / minimap_scale);
//		}
//
//	}
//
//	else
//		return false;
//
//	return true;
//}
//
//void j1Minimap::DrawMinimap()
//{
//	std::list<MapLayer*>::const_iterator item = App->map->data.layers.cbegin();
//
//	for (; item != App->map->data.layers.end(); item = next(item))
//	{
//		MapLayer* layer = *item;
//
//		for (int y = 0; y < App->map->data.height; ++y)
//		{
//			for (int x = 0; x < App->map->data.width; ++x)
//			{
//				int tile_id = layer->Get(x, y);
//				if (tile_id > 0)
//				{
//					TileSet* tileset = App->map->GetTilesetFromTileId(tile_id);
//
//					SDL_Rect r = tileset->GetTileRect(tile_id);
//					fPoint pos = App->map->MapToWorld(x, y);
//					
//					//As you can see to draw the minimap we can use the same draw function as the map but with 2 changes
//					//One change is that the position where we blit the map must be scaled to the minimap one
//					pos.x *= minimap_scale;
//					pos.y *= minimap_scale;
//
//					//The change is that we won't be using the camera
//					//Remember that the pos.x=0 on the x axis for an isometric map is on the center of the map and not at the left
//					//We need to include the minimap_scale also on the blit function
//					if (App->map->data.type == MAPTYPE_ORTHOGONAL) 
//						App->render->Blit(tileset->texture, pos.x, pos.y, &r, false, App->render->renderer, minimap_scale);
//					else if (App->map->data.type == MAPTYPE_ISOMETRIC)
//						App->render->Blit(tileset->texture, pos.x + minimap_width / 2, pos.y, &r, false, App->render->renderer, minimap_scale);
//				}
//			}
//		}
//	}
//}
//
//void j1Minimap::DrawCamera()
//{
//	// Scale the camera parameters and move the minicamera to the map position
//	// Reminder: The camera position values are negative
//	// Take into account that in the isometric map the x position starts (x=0) on the center of the map
//	if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
//		SDL_Rect map_camera = { -App->render->camera.x * minimap_scale + position.x,-App->render->camera.y * minimap_scale + position.y,App->render->camera.w * minimap_scale,App->render->camera.h * minimap_scale };
//		App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
//	}
//	else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
//		SDL_Rect map_camera = { -App->render->camera.x * minimap_scale + minimap_width / 2 + position.x,-App->render->camera.y * minimap_scale + position.y,App->render->camera.w * minimap_scale,App->render->camera.h * minimap_scale };
//		App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
//	}
//}
//
//void j1Minimap::MinimapBorders()
//{
//	int isotile_x_offset = App->map->data.tile_width / 2 * minimap_scale;
//	int isotile_y_offset = App->map->data.tile_height / 2 * minimap_scale;
//
//	if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
//		App->render->DrawLine(position.x , position.y, position.x + minimap_width, position.y, 0, 0, 255, 255, false);
//		App->render->DrawLine(position.x + minimap_width, position.y, minimap_width + position.x, minimap_height + position.y, 0, 0, 255, 255, false);
//		App->render->DrawLine(position.x,minimap_height + position.y, minimap_width + position.x, minimap_height + position.y, 0, 0, 255, 255, false);
//		App->render->DrawLine(position.x, position.y, position.x, position.y + minimap_height, 0, 0, 255, 255, false);
//	}
//	else if (App->map->data.type == MAPTYPE_ISOMETRIC){
//		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + position.y + isotile_y_offset, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
//		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, isotile_y_offset + position.y, 255, 255, 255, 255, false);
//		App->render->DrawLine(minimap_width + isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
//		App->render->DrawLine(isotile_x_offset + position.x, minimap_height / 2 + isotile_y_offset + position.y, minimap_width / 2 + isotile_x_offset + position.x, minimap_height + isotile_y_offset + position.y, 255, 255, 255, 255, false);
//	}
//
//}
//
//void j1Minimap::DrawEntitiesRectangle()
//{
//	// To do so you just need to draw a square with the scaled proportions of the entity
//	// Remember that if we have moved the minimap position we also need to move the entities accordingly
//	int pos_x, pos_y, width, height;
//
//	for (std::list<Entity*>::iterator item = App->entities->activeEntities.begin(); item != App->entities->activeEntities.end(); ++item) 
//	{
//		if(App->map->data.type==MAPTYPE_ORTHOGONAL){
//			pos_x = (*item)->position.x * minimap_scale + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//			width = (int)((*item)->entity_rect.w * minimap_scale);
//			height = (int)((*item)->entity_rect.h * minimap_scale);
//		}
//		//(from the map and from the entity!!! Check the blit of the entities to know the offset that will also need to be scaled to the minimap size)
//		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
//			pos_x = (*item)->position.x * minimap_scale - (*item)->x_isometric_offset * minimap_scale + minimap_width / 2 + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//			width = (int)((*item)->entity_rect.w * minimap_scale);
//			height = (int)((*item)->entity_rect.h * minimap_scale);
//		}
//		SDL_Rect entity_rect = { pos_x,pos_y,width,height };
//
//
//		if ((*item)->type == ENTITY_TYPE::ENEMY)
//			App->render->DrawQuad(entity_rect, 255, 0, 0, 255, true, false);
//		
//		else if ((*item)->type == ENTITY_TYPE::PLAYER)
//			App->render->DrawQuad(entity_rect, 0, 255, 0, 255, true, false);
//	}
//}
//
//void j1Minimap::DrawEntities(){
//	int pos_x, pos_y;
//
//	for (std::list<j2Entity*>::iterator item = App->entity_manager->entities.begin(); item != App->entity_manager->entities.end(); ++item)
//	{
//		if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
//			pos_x = (*item)->position.x * minimap_scale + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//		}
//		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
//			pos_x = (*item)->position.x * minimap_scale - (*item)->x_isometric_offset * minimap_scale + minimap_width / 2 + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//		}
//
//		if ((*item)->type == ENTITY_TYPE::ENEMY) {
//			App->render->Blit((*item)->entity_tex, pos_x, pos_y, &(*item)->entity_rect, false, App->render->renderer, minimap_scale);
//			SDL_Rect rect = { pos_x, pos_y, (int)((*item)->entity_rect.w * minimap_scale), (int)((*item)->entity_rect.h * minimap_scale) };
//			App->render->DrawQuad(rect, 255, 0, 0, 255, false, false);
//		}
//
//		else if ((*item)->type == ENTITY_TYPE::PLAYER){
//			App->render->Blit((*item)->entity_tex, pos_x, pos_y, &(*item)->entity_rect, false, App->render->renderer, minimap_scale); 
//			SDL_Rect rect = { pos_x, pos_y, (int)((*item)->entity_rect.w * minimap_scale), (int)((*item)->entity_rect.h * minimap_scale) };
//			App->render->DrawQuad(rect, 0, 255, 0, 255, false, false);
//		}
//	}
//}
//
//
//void j1Minimap::DrawEntitiesIcon() {
//	// NOTE: WE ARE ASUMING THAT THE ENTITY ICON IS A SQUARE OF DIMENSIONS AVERAGE WIDTH AND HEIGHT OF THE ENTITY IT REPRESENTS
//	int pos_x, pos_y;
//
//	for (std::list<j2Entity*>::iterator item = App->entity_manager->entities.begin(); item != App->entity_manager->entities.end(); ++item)
//	{
//		if (App->map->data.type == MAPTYPE_ORTHOGONAL) {
//			pos_x = (*item)->position.x * minimap_scale + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//		}
//		else if (App->map->data.type == MAPTYPE_ISOMETRIC) {
//			pos_x = (*item)->position.x * minimap_scale - (*item)->x_isometric_offset * minimap_scale + minimap_width / 2 + position.x;
//			pos_y = (*item)->position.y * minimap_scale + position.y;
//		}
//
//		if ((*item)->type == ENTITY_TYPE::ENEMY) {
//			if ((*item)->minimap_icon != nullptr) {
//				int entity_average_size = ((*item)->entity_rect.w + (*item)->entity_rect.h) / 2;
//				App->render->Blit((*item)->minimap_icon, pos_x, pos_y, NULL, false, App->render->renderer, minimap_scale);
//				SDL_Rect icon = { pos_x,pos_y, entity_average_size * minimap_scale, entity_average_size * minimap_scale };
//				App->render->DrawQuad(icon, 0, 255, 0, 255, false, false);
//			}
//			else
//				App->render->Blit((*item)->entity_tex, pos_x, pos_y, &(*item)->entity_rect, false, App->render->renderer, minimap_scale);
//		}
//		else if ((*item)->type == ENTITY_TYPE::PLAYER) {
//			if ((*item)->minimap_icon != nullptr) {
//				int entity_average_size= ((*item)->entity_rect.w + (*item)->entity_rect.h) / 2;
//				App->render->Blit((*item)->minimap_icon, pos_x, pos_y, NULL, false, App->render->renderer, minimap_scale);
//				SDL_Rect icon = { pos_x,pos_y, entity_average_size * minimap_scale, entity_average_size * minimap_scale };
//				App->render->DrawQuad(icon, 0,255,0,255,false, false);
//			}
//			else
//				App->render->Blit((*item)->entity_tex, pos_x, pos_y, &(*item)->entity_rect, false, App->render->renderer, minimap_scale);
//		}
//	}
//}
//
//void j1Minimap::Scale() {
//	if (size < (App->map->data.tile_height / 2)) {
//		size += 1;
//		CleanUp();
//		Load();
//	}
//}
//
//void j1Minimap::Descale() {
//	if (size > 1) {
//		size -= 1;
//		CleanUp();
//		Load();
//	}
//}