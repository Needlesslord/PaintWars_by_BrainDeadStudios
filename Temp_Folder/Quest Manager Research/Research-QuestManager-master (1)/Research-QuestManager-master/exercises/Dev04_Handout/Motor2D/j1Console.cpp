#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Gui.h"
#include "UI_Image.h"
#include "UI_InputBox.h"
#include "UI_Scrollbar.h"
#include "j1Console.h"



j1Console::j1Console() : j1Module(), commandWasFound(false)
{
	name = ("console");
}

j1Console::~j1Console()
{

}

bool j1Console::Awake(pugi::xml_node& config)
{
	//config_file = config;

	return true;
}

bool j1Console::Start()
{
	InitConsole();
	CreateConsoleElements();
	CreateConsoleCommands();

	return true;
}

bool j1Console::PreUpdate()
{	
	BROFILER_CATEGORY("Console_PreUpdate", Profiler::Color::PowderBlue);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		commandWasFound = false;
		
		for (std::list<Command*>::iterator command = commands.begin(); command != commands.end(); command++)
		{
			Command* comm = (*command);

			if (App->input->CmpStr(App->input->GetInputText(), comm->command.c_str()))
			{
				comm->callback->OnCommand(comm->command.c_str());
				commandHistory.push_back(comm);
				commandWasFound = true;
				break;
			}
		}
		
		if (!commandWasFound)
		{
			console_output->RefreshTextInput("Error: COMMAND NOT FOUND");
		}

		App->input->ClearTextInput();
	}

	if (ConsoleIsOpen())
	{
		if (App->gui->focusedElement != console_input)
		{
			App->gui->focusedElement = console_input;
		}
	}
	
	return true;
}

bool j1Console::Update(float dt)
{

	return true;
}

bool j1Console::PostUpdate()
{
	//DrawBackgroundElement();
	
	return true;
}

bool j1Console::CleanUp()
{
	for (std::list<Command*>::iterator command = commands.begin(); command != commands.end(); command++)
	{
		RELEASE((*command));
	}

	commandHistory.clear();
	commands.clear();
	
	return true;
}

void j1Console::InitConsole()
{
	config_file.load_file("config.xml");

	console = config_file.child("config").child("console");

	// --- LOADING THE CONSOLE'S VARIABLES
	// --- BACKGROUND
	bg_position.x = console.child("bg_position").attribute("x").as_int();
	bg_position.y = console.child("bg_position").attribute("y").as_int();

	bg_rect.x = console.child("bg_rect").attribute("x").as_int();
	bg_rect.y = console.child("bg_rect").attribute("y").as_int();
	bg_rect.w = console.child("bg_rect").attribute("w").as_int();
	bg_rect.h = console.child("bg_rect").attribute("h").as_int();

	bg_colour.r = console.child("bg_colour").attribute("r").as_int();
	bg_colour.g = console.child("bg_colour").attribute("g").as_int();
	bg_colour.b = console.child("bg_colour").attribute("b").as_int();
	bg_colour.a = console.child("bg_colour").attribute("a").as_int();

	bg_isVisible = console.child("bg_isVisible").attribute("value").as_bool();
	bg_isInteractible = console.child("bg_isInteractible").attribute("value").as_bool();
	bg_isDraggable = console.child("bg_isDraggable").attribute("value").as_bool();

	// --- OUTPUT
	output_position.x = console.child("output_position").attribute("x").as_int();
	output_position.y = console.child("output_position").attribute("y").as_int();

	output_rect.x = console.child("output_rect").attribute("x").as_int();
	output_rect.y = console.child("output_rect").attribute("y").as_int();
	output_rect.w = console.child("output_rect").attribute("w").as_int();
	output_rect.h = console.child("output_rect").attribute("h").as_int();
	
	output_font_path = console.child("output_font_path").attribute("path").as_string("");
	output_font_size = console.child("output_font_size").attribute("size").as_int();

	output_font_colour.r = console.child("output_font_colour").attribute("r").as_int();
	output_font_colour.g = console.child("output_font_colour").attribute("g").as_int();
	output_font_colour.b = console.child("output_font_colour").attribute("b").as_int();
	output_font_colour.a = console.child("output_font_colour").attribute("a").as_int();

	output_isVisible = console.child("output_isVisible").attribute("value").as_bool();
	output_isInteractible = console.child("output_isInteractible").attribute("value").as_bool();;
	output_isDraggable = console.child("output_isDraggable").attribute("value").as_bool();

	// --- INPUT
	input_position.x = console.child("input_position").attribute("x").as_int();
	input_position.y = console.child("input_position").attribute("y").as_int();

	input_rect.x = console.child("input_rect").attribute("x").as_int();
	input_rect.y = console.child("input_rect").attribute("y").as_int();
	input_rect.w = console.child("input_rect").attribute("w").as_int();
	input_rect.h = console.child("input_rect").attribute("h").as_int();

	input_font_path = console.child("input_font_path").attribute("path").as_string("");
	input_font_size = console.child("input_font_size").attribute("size").as_int();

	input_font_colour.r = console.child("input_font_colour").attribute("r").as_int();
	input_font_colour.g = console.child("input_font_colour").attribute("g").as_int();
	input_font_colour.b = console.child("input_font_colour").attribute("b").as_int();
	input_font_colour.a = console.child("input_font_colour").attribute("a").as_int();

	cursor_rect.x = console.child("cursor_rect").attribute("x").as_int();
	cursor_rect.y = console.child("cursor_rect").attribute("y").as_int();
	cursor_rect.w = console.child("cursor_rect").attribute("w").as_int();
	cursor_rect.h = console.child("cursor_rect").attribute("h").as_int();

	cursor_colour.r = console.child("cursor_colour").attribute("r").as_int();
	cursor_colour.g = console.child("cursor_colour").attribute("g").as_int();
	cursor_colour.b = console.child("cursor_colour").attribute("b").as_int();
	cursor_colour.a = console.child("cursor_colour").attribute("a").as_int();

	input_text_offset.x = console.child("input_text_offset").attribute("x").as_int();
	input_text_offset.y = console.child("input_text_offset").attribute("y").as_int();

	cursor_blinkFrequency = console.child("cursor_blinkFrequency").attribute("frequency").as_float();
	input_isVisible = console.child("input_isVisible").attribute("value").as_bool();
	input_isInteractible = console.child("input_isInteractible").attribute("value").as_bool();
	input_isDraggable = console.child("input_isDraggable").attribute("value").as_bool();

	// --- SCROLLBAR
	scroll_position.x = console.child("scroll_position").attribute("x").as_int();
	scroll_position.y = console.child("scroll_position").attribute("y").as_int();

	scrollbar_rect.x = console.child("scrollbar_rect").attribute("x").as_int();
	scrollbar_rect.y = console.child("scrollbar_rect").attribute("y").as_int();
	scrollbar_rect.w = console.child("scrollbar_rect").attribute("w").as_int();
	scrollbar_rect.h = console.child("scrollbar_rect").attribute("h").as_int();

	thumb_rect.x = console.child("thumb_rect").attribute("x").as_int();
	thumb_rect.y = console.child("thumb_rect").attribute("y").as_int();
	thumb_rect.w = console.child("thumb_rect").attribute("w").as_int();
	thumb_rect.h = console.child("thumb_rect").attribute("h").as_int();

	thumb_offset.x = console.child("thumb_offset").attribute("x").as_int();
	thumb_offset.y = console.child("thumb_offset").attribute("y").as_int();

	drag_area.x = console.child("drag_area").attribute("x").as_int();
	drag_area.y = console.child("drag_area").attribute("y").as_int();
	drag_area.w = console.child("drag_area").attribute("w").as_int();
	drag_area.h = console.child("drag_area").attribute("h").as_int();

	drag_factor = console.child("drag_factor").attribute("factor").as_float();
	drag_x_axis = console.child("drag_x_axis").attribute("value").as_bool();
	drag_y_axis = console.child("drag_y_axis").attribute("value").as_bool();
	inverted_scrolling = console.child("inverted_scrolling").attribute("value").as_bool();
	scroll_isVisible = console.child("scroll_isVisible").attribute("value").as_bool();
	scroll_isInteractible = console.child("scroll_isInteractible").attribute("value").as_bool();
	scroll_isDraggable = console.child("scroll_isDraggable").attribute("value").as_bool();
}

void j1Console::CreateConsoleElements()
{
	output_font = App->font->Load(output_font_path.GetString(), output_font_size);
	input_font = App->font->Load(input_font_path.GetString(), input_font_size);

	p2SString defaultString = "DefaultString";

	console_background = (UI_Image*)App->gui->CreateImage(UI_Element::EMPTY, bg_position.x, bg_position.y, bg_rect, bg_isVisible, bg_isInteractible, bg_isDraggable, NULL);
	
	console_output = (UI_Text*)App->gui->CreateText(UI_Element::TEXT, output_position.x, output_position.y, output_rect, output_font, output_font_colour,
												output_isVisible, output_isInteractible, output_isDraggable, console_background, NULL);

	console_input = (UI_InputBox*)App->gui->CreateInputBox(UI_Element::INPUTBOX, input_position.x, (console_background->GetHitbox().h - input_rect.h), input_rect, input_font, input_font_colour,
		cursor_rect, cursor_colour, input_text_offset, cursor_blinkFrequency, input_isVisible, input_isInteractible, input_isDraggable, console_background, &defaultString, true);

	console_scroll = (UI_Scrollbar*)App->gui->CreateScrollbar(UI_Element::SCROLLBAR, scroll_position.x, scroll_position.y, scrollbar_rect, thumb_rect, thumb_offset, drag_area, drag_factor,
												drag_x_axis, drag_y_axis, inverted_scrolling, scroll_isVisible, scroll_isDraggable, scroll_isInteractible, console_background,
												NULL, iPoint(0, 0), true);

	console_scroll->LinkScroll(console_output);

	if (console_background->isVisible)
	{
		App->gui->focusedElement = console_input;
	}
}

void j1Console::DrawBackgroundElement()
{
	if (console_background->isVisible)
	{
		App->render->DrawQuad(console_background->GetHitbox(), bg_colour.r, bg_colour.g, bg_colour.b, bg_colour.a, true, false);
	}
}

bool j1Console::ConsoleIsOpen()
{
	return console_background->isVisible;
}

Command::Command(const char* command, j1Module* callback, int min_arg, int max_arg)
{
	this->command = command;
	this->callback = callback;
	this->min_arg = min_arg;
	this->max_arg = max_arg;
}

Command* j1Console::CreateCommand(const char* command, j1Module* callback, int min_arg, int max_arg)
{
	Command* comm = nullptr;

	comm = new Command(command, callback, min_arg, max_arg);

	if (comm != nullptr)
	{
		commands.push_back(comm);
	}

	return comm;
}

void j1Console::CreateConsoleCommands()
{
	//CreateCommand("quit", this, 1, 1);

	// Console Commands
	command_list		= "list";
	
	// App Commands
	enable_pause		= "enable_pause";
	disable_pause		= "disable_pause";
	enableFrameCap		= "enable_frame_cap";
	disableFrameCap		= "disable_frame_cap";
	resetFrameCap		= "reset_frame_cap";
	FPS_30				= "FPS 30";									//EVERYTHING IS A LIE. JUST SMOKE AND MIRRORS.
	FPS_60				= "FPS 60";
	FPS_120				= "FPS 120";

	// Debug Commands
	enable_god_mode		= "enable_god_mode";
	disable_god_mode	= "disable_god_mode";
	
	// Map Commands
	first_map			= "map Test_map.tmx";						//(Again) EVERYTHING IS A LIE. JUST SMOKE AND MIRRORS.
	second_map			= "map Test_map_2.tmx";
	
	CreateCommand(command_list, this, 1, 1);
	
	CreateCommand(enable_pause, this, 1, 1);
	CreateCommand(disable_pause, this, 1, 1);
	CreateCommand(enableFrameCap, this, 1, 1);
	CreateCommand(disableFrameCap, this, 1, 1);
	CreateCommand(resetFrameCap, this, 1, 1);
	CreateCommand(FPS_30, this, 1, 1);
	CreateCommand(FPS_60, this, 1, 1);
	CreateCommand(FPS_120, this, 1, 1);

	CreateCommand(enable_god_mode, this, 1, 1);
	CreateCommand(disable_god_mode, this, 1, 1);

	CreateCommand(first_map, this, 1, 1);
	CreateCommand(second_map, this, 1, 1);
}

void j1Console::OnCommand(const char* command, const char* subCommand)
{
	// --- CONSOLE COMMANDS
	if (App->input->CmpStr(command, command_list))
	{
		ShellExecuteA(NULL, "open", "https://gromeu2000.wixsite.com/mutualcooperation", NULL, NULL, SW_SHOWNORMAL);
	}
	
	// --- APP COMMANDS
	if (App->input->CmpStr(command, enable_pause))						// -----------------------------------------------------------------------------------
	{
		App->pause = true;												// Enable Pause Mode
	}
	if (App->input->CmpStr(command, disable_pause))						// -----------------------------------------------------------------------------------
	{
		App->pause = false;												// Disable Pause Mode
	}
	if (App->input->CmpStr(command, enableFrameCap))					// -----------------------------------------------------------------------------------
	{
		App->framesAreCapped = true;									// Enable Frame Cap
	}
	if (App->input->CmpStr(command, disableFrameCap))					// -----------------------------------------------------------------------------------
	{
		App->framesAreCapped = false;									// Disable Frame Cap
	}
	if (App->input->CmpStr(command, resetFrameCap))						// -----------------------------------------------------------------------------------
	{
		App->frame_cap = App->original_frame_cap;						// Reset Frame Cap
	}
	if (App->input->CmpStr(command, FPS_30))							// -----------------------------------------------------------------------------------
	{
		App->frame_cap = CAP_AT_30;										// Cap Frames at 30
	}
	if (App->input->CmpStr(command, FPS_60))							// -----------------------------------------------------------------------------------
	{
		App->frame_cap = CAP_AT_60;										// Cap Frames at 60
	}
	if (App->input->CmpStr(command, FPS_120))							// -----------------------------------------------------------------------------------
	{
		App->frame_cap = CAP_AT_120;									// Cap Frames at 120
	}
																		// -----------------------------------------------------------------------------------
	// --- DEBUG COMMANDS
	if (App->input->CmpStr(command, enable_god_mode))					// -----------------------------------------------------------------------------------
	{
		App->entityManager->player->player.GodMode = true;				// Enable Player 1's God Mode.
		App->entityManager->player2->player.GodMode = true;				// Enable Player 2's God Mode.
		App->entityManager->player->player.airborne = false;				// Sets Player 1's Airborne.
		App->entityManager->player2->player.airborne = false;			// Sets Player 2's Airborne.
	}
	if (App->input->CmpStr(command, disable_god_mode))					// -----------------------------------------------------------------------------------
	{
		App->entityManager->player->player.GodMode = false;				// Disable Player 1's God Mode.
		App->entityManager->player2->player.GodMode = false;			// Disable Player 2's God Mode
		App->entityManager->player->player.airborne = true;				// Sets Player 1's Airborne.
		App->entityManager->player2->player.airborne = true;			// Sets Player 2's Airborne.
	}
																		// -----------------------------------------------------------------------------------
	// --- MAP COMMANDS
	if (App->input->CmpStr(command, first_map))							// -----------------------------------------------------------------------------------
	{
		App->map->ChangeMap("Test_map.tmx");							// Load the First Map
	}
	if (App->input->CmpStr(command, second_map))						// -----------------------------------------------------------------------------------
	{
		App->map->ChangeMap("Test_map_2.tmx");							// Load the Second Map
	}
}