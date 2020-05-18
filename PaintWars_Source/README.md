# PAINT WARS
## by BrainDead Studios

## Description

In a world full of colour, a corruption spread, turning everything monochromatic and evil. The war started, with all colour beings trying to restore the colours on the world and with them, the peace. The destiny of those in despair is in your hands.

*Paint Wars* is an isometric single player RTS game featuring a campaign with playable units, buildable structures and manageable resources where the player will have to fight against waves of enemies trying to destroy his base. The game is located in a paint themed world where resources, units and buildings will be related to paint.

**DISCLAIMER:** This version is not the final one, so please do not mind bugs and lack of content. We are working on that! 

*Current version: v0.85*


## Key Features

 - GENERAL
     + Logo for the team (animated)
     + Logo for the game (animated)
     + FX for the Game Logo and Team Logo
     + Social Media Updated
     + Animations
     + Game resoulution at 1280x720px@60fps (Window and Full Screen supported)
     + Automatic Continuous Integration and Deployment (basic)
     + Save/Load
     + 3 different waves -not fully implemented, enemies all over the map-
     + Fog of war
     + Tutorial, Dialogs and Quests
     + Particles
 - UI and HUD
     + UI, with Main Menu (Play and Exit, Settings -music, fx, full screen, reset-, Credits -link to repository- and Map selection -continue if saved game, forest, snow and volcano-) with background
     + Life Bars, Progress bars
     + Pause menu fully working. with owered volume
     + HUD: Quests (drop-down menu), buttons on the right (in order: go to Town Hall, Shop, Pause, Start over), resources bar (with all the resources, life timer)
     + Minimap: can be made bigger/smaller with [M], shows where in the map you are, has entities -in progress-
     + Visual and acustic feedback, all menus animated
 - RESOURCES
     + 6 different resources working: paint, wood, max units, research (to improve units/buildings), metal scrap, titanium
 - ENTITIES: Allies, buildings and enemies
     + 5 different allied units (full colour): painter (collect paint from lakes), warrior (attack spawners and enemies), explorer (big vision range), ranger (attacks from a distance), knight (very tanky)
     + 9 allied buildings (full colour):
       - Town Hall: Not buildable, if destroyed LOSE, to create painters, explorers
       - Paint Extractor: To get paint (only buildable on lakes)
       - Wood Producer: To get wood
       - Barracks: To create warriors, rangers, knights
       - House: To increase unit capacity
       - Research: to get improvement on units and buildings -not fully working yet-
       - Metal Gatherer: To get metal scrap
       - Titanium Extractor: To get titanium
       - Turret: defensive building -not fully working yet-
     + 1 enemy building (black and white): Spawner (5, if destroyed WIN)
     + 4 Enemies, with AI behaviour, (black and white):
       - Slime: Melee enemy
       - Explosive Blob: Kamikaze enemy -not fully implemented-
       - Rider: similar to warrior, but enemy -not fully implemented-
       - Chroma King: Boss, Town Hall target -not fully implemented-
 - ACTIONS
     + Movement and group movement
     + Collect resources and explore
     + Run from and attack enemies 
     + Destroy spawners (with warriors)
     + Pathfinding
     + Win/Lose conditions (Town Hall destroyed OR more than 15 min LOSE, 5 Spawners destroyed WIN) with victory/lose custom messages and font and animated
 - MAPS
     + Forest Map implemented
 - SCENE MANAGER
     + Different scenes for the game, menu, win/lose, start, logos
     + Transitions (Slide for buttons, Fade for debug)
 - CAMERA
     + Camera follows the mouse on the edges
     + Starts on the Town Hall
     + It can also move with the arrows
     + Culling
 - AUDIO
     + Background music implemented different for all the scenes
     + UI feedback
     + FX 
        1 - warrior attack
        2 - spawner destroyed
        3 - painter movement
        4 - warrior movement
        5 - buying from shop (2 different ones
        6 - timer (when 10 sec left, countdown every second)
        7 - wood producer
        8 - town hall when creating a painter
        9 - barracks when creating a warrior
       10 - birds
       11 - crickets
       12 - quests
       13 - knight attack
       14 - enemy death
       15 - ranger attack 
       16 - explorer movement
       17 - ranger movement
       18 - knight movement
     + Positioning (further fx sound less)
 - DEBUG
	 + F1/F2/F3 Game Scene: Forest / Snow / Volcano
	 + F4 Save
	 + F5 Load (Load function not functional yet)
	 + F6 Full Screen
	 + F7 Direct Win
	 + F8 Direct Lose
	 + F9 Collisions
	 + F10 God Mode (add resources, buildings and units, can't lose, collisions)
		resources
		- 1 add 10 paint
		- 2 add 10 wood
		- 3 add 10 metal scrap 
		- 4 add 10 titanium 
		- 6 add 10 max housing
		- 7 add 1 level of research (units will have the upgrades already)
		units (on mouse position)
		- KP 1 add painter
		- KP 2 add warrior
		- KP 3 add ranged 
		- KP 4 add special (knight) 
		- KP 5 add explorer 
		- KP 0 kill selected units
		buildings (on mouse position)
		- Crtl + KP 1 add paint extractor
		- Crtl + KP 2 add wood producer
		- Crtl + KP 3 add barracks
		- Crtl + KP 4 add house
		- Crtl + KP 0 kill selected buildings
	 + H Go to Town Hall
	 + P Pause
	 + S/L Save/Load 
	 + ESC exit game 
	 + N/M/R Zoom In/Out/Reset
	 + KP MINUS/KP PLUS Control Framerate (+/- 10)
         + UP/DOWN/LEFT/RIGHT Camera movement


## Controls

You start with the Town Hall and some resources. From it you can create painters and upgrade units and buildings leveling up (research).
With a painter, go to a paint lake to start getting resources.
From the shop, you can get different buiuldings: 
   + paint extractor (built with wood): they collect paint faster than painters, must build them with at least one tile on a lake
   + wood producer (built with paint): to get wood. Wood is used to create paint extractors, houses and barracks
   + house (built with wood): to increase your max number of units
   + barracks (built with wood): to create warriors
Warriors are used to attack the spawners and destroy them to win the game.

 - LEFT CLICK - select
 - RIGHT CLICK - select destination / attack
 - ESC - exit game (not on Game scene)
 - RIGHT CLICK AND DRAG - multiple selection -not working-
 - CTR - multiple selection
 - UI and HUD - each button is self-explanatory, right clicking to select and hover enabled
     + SHOP - to shop, click on the "Shop Button", and select what you want to build by dragging into the map, it will take a while to build (depending on research level)
	 + F1/F2/F3 Game Scene: Forest / Snow / Volcano
	 + F4 Save
	 + F5 Load (Load function not functional yet)
	 + F6 Full Screen
	 + F7 Direct Win
	 + F8 Direct Lose
	 + F9 Collisions
	 + F10 God Mode (add resources, buildings and units, can't lose, collisions)
		resources
		- 1 add 10 paint
		- 2 add 10 wood
		- 3 add 10 metal scrap 
		- 4 add 10 titanium 
		- 6 add 10 max housing
		- 7 add 1 level of research (units will have the upgrades already)
		units (on mouse position)
		- KP 1 add painter
		- KP 2 add warrior
		- KP 3 add ranged 
		- KP 4 add special (knight) 
		- KP 5 add explorer 
		- KP 0 kill selected units
		buildings (on mouse position)
		- Crtl + KP 1 add paint extractor
		- Crtl + KP 2 add wood producer
		- Crtl + KP 3 add barracks
		- Crtl + KP 4 add house
		- Crtl + KP 0 kill selected buildings
	 + H Go to Town Hall
	 + P Pause
	 + S/L Save/Load 
	 + ESC exit game 
	 + N/M/R Zoom In/Out/Reset
	 + KP MINUS/KP PLUS Control Framerate (+/- 10)
         + UP/DOWN/LEFT/RIGHT Camera movement

## Developers

 - Enric-G. Durán - Co-Lead UI Designer, Lead Artist
      + [Github](https://github.com/EnricGDV)
      + [Linkedin](https://www.linkedin.com/in/enric-guillem-dur%C3%A1n-vilar-9a1932138/)
 - Marc Ariza - Lead Designer
      + [GitHub](https://github.com/MarcArizaAlborni)
      + [Linkedin](https://www.linkedin.com/in/marc-ariza-0b2b431a2/)
 - Tomás Carreras - Lead Coder
      + [Github](https://github.com/tomascarreras1000)
      + [Linkedin](https://www.linkedin.com/in/tom%C3%A1s-carreras-a96a99177/)
 - Alex Lopez - Lead QA
      + [Github](https://github.com/AlexLA99)
      + [Linkedin](https://www.linkedin.com/in/alex-lopez-agudo-9777741a3)
 - Núria Lamonja - **Team Leader**, Management, Community Manager, Social Media, Co-Lead UI Designer, Music
      + [Github](https://github.com/Needlesslord)
      + [Linkedin](https://es.linkedin.com/in/needlesslord)

Special thanks to Marc San José, he helped us implement the Fx for the game.
      + [Github](https://github.com/marcsjm19)
      + [Linkedin](https://www.linkedin.com/in/marc-san-jos%C3%A9-mart%C3%ADnez-6239361a3/)

## License

Copyright (c) 2020 BrainDead Studios

BrainDead Studios' games are licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](https://github.com/Needlesslord/BrainDeadStudios/blob/master/LICENSE) for further details.


###Credits

All the data used (sprites, music, fx, etc), which are free to use, will be credited as well.

The base code from where we started our game (base code) was taken from [Dolime Corporation](https://github.com/Sanmopre/DOLIME-CORP-PROJECT-II). They are also developing and RTS and we encourage you to check it out!

### Disclaimer

Our games are non-profit for educational purposes only. We do not intend to earn profit from it, since it is part of a university project taught at CITM-TTC in the degree Videogame Development and Design. All the assets (including sprites, music FX, etc) used in our games belong to their rightful owners, which will be credited.