# PAINT WARS
## by BrainDead Studios

## Description

In a world full of colour, a corruption spread, turning everything monochromatic and evil. The war started, with all colour beings trying to restore the colours on the world and with them, the peace. The destiny of those in despair is in your hands.

*Paint Wars* is an isometric single player RTS game featuring a campaign with playable units, buildable structures and manageable resources where the player will have to fight against waves of enemies trying to destroy his base. The game is located in a paint themed world where resources, units and buildings will be related to paint.

**DISCLAIMER:** This version is not the final one, so please do not mind bugs and lack of content. We are working on that! 

*Current version: v0.5*


## Key Features

 - GENERAL
     + Logo for the team
     + Logo for the game
     + FX for the Game Logo
     + Social Media Updated
     + Animations
     + Game resoulution at 1280x720px@60fps (Window and Full Screen supported)
     + Automatic Continuous Integration and Deployment
 - UI and HUD
     + Basic UI, with Main Menu (Play and Exit, Settings -not all functional, only Full Screen-, Credits -link to repository- and Map selection -all take to Forest Map-) with background
     + Life Bars
     + HUD: Quests (drop-down menu), buttons on the right (in order: go to Town Hall, Shop, Pause, Start over -only "no" functional), resources
     + Minimap: can be made bigger/smaller with [M], shows where in the map you are
     + Visual and acustic feedback
 - RESOURCES
     + 4 different resources working: paint, wood, max units, research (to improve units/buildings)
     + 3 resources not fully implemented: metal scrap, food, titanium
 - ENTITIES: Allies, buildings and enemies
     + 2 different allied units: painter (collect paint from lakes) and warrior (attack spawners)
     + 4 allied buildings:
       - Town Hall: Not buildable, if destroyed LOSE
       - Paint Extractor: To get paint (only buildable on lakes)
       - Wood Producer: To get wood
       - Barracks: To create warriors
     + 1 enemy building: Spawner (5, if destroyed WIN)
 - ACTIONS
     + Movement and group movement
     + Collect paint (with painters)
     + Collect wood 
     + Destroy spawners (with warriors)
     + Pathfinding
     + Win/Lose conditions (Town Hall destroyed OR more than 15 min LOSE, 5 Spawners destroyed WIN) with victory/lose custom messages and font
 - MAPS
     + Forest Map implemented
 - SCENE MANAGER
     + Different scenes for the game, menu, win/lose, start
     + Transitions (Slide for buttons, Fade for debug)
 - CAMERA
     + Camera follows the mouse on the edges
     + Starts on the Town Hall
     + It can also move with the arrows
     + Culling
 - AUDIO
     + Background music implemented for all the scenes
     + UI feedback
     + FX (warrior attack, spawner destroyed)
     + Positioning (further fx sound less)
 - DEBUG
     + F2 Game Scene
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
        - 3 add 10 metal scrap -not implemented yet-
        - 4 add 10 titanium -not implemented yet-
        - 5 add 10 food -not implemented yet-
        - 6 add 10 max housing
        - 7 add 1 level of research (units will have the upgrades already)
        units (on mouse position)
        - KP 1 add painter
        - KP 2 add warrior
        - KP 3 add ranged -not implemented yet-
        - KP 4 add tank -not implemented yet-
        - KP 5 add explorer -not implemented yet-
        - KP 0 kill selected units
        buildings (on mouse position)
        - Crtl + KP 1 add paint extractor 
        - Crtl + KP 2 add wood producer
        - Crtl + KP 3 add barracks
        - Crtl + KP 4 add house
        - Crtl + KP 0 kill selected buildings 


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
 - RIGHT CLICK AND DRAG - multiple selection
 - CTR - multiple selection
 - UI and HUD - each button is self-explanatory, right clicking to select and hover enabled
     + SHOP - to shop, click on the "Shop Button", and select what you want to build by dragging into the map, it will take a while to build (depending on research level)
- DEBUG
     + F2 Game Scene
     + F4 Save
     + F5 Load (Load function not functional yet)
     + F6 Full Screen
     + F7 Direct Win
     + F8 Direct Lose
     + F9 Collisions
     + F10 God Mode (add resources, buildings and units, can't lose)
        resources
        - 1 add 10 paint
        - 2 add 10 wood
        - 3 add 10 metal scrap -not implemented yet-
        - 4 add 10 titanium -not implemented yet-
        - 5 add 10 food -not implemented yet-
        - 6 add 10 max housing
        - 7 add 1 level of research (units will have the upgrades already)
        units (on mouse position)
        - KP 1 add painter
        - KP 2 add warrior
        - KP 3 add ranged -not implemented yet-
        - KP 4 add tank -not implemented yet-
        - KP 5 add explorer -not implemented yet-
        - KP 0 kill selected unit
        buildings (on mouse position)
        - Crtl + KP 1 add paint extractor 
        - Crtl + KP 2 add wood producer
        - Crtl + KP 3 add barracks
        - Crtl + KP 4 add house

## Developers

 - Marc San José - Design, QA
      + [Github](https://github.com/marcsjm19)
      + [Linkedin](https://www.linkedin.com/in/marc-san-jos%C3%A9-mart%C3%ADnez-6239361a3/)
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

## License

Copyright (c) 2020 BrainDead Studios

BrainDead Studios' games are licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](https://github.com/Needlesslord/BrainDeadStudios/blob/master/LICENSE) for further details.

All the data used (sprites, music, fx, etc) will be credited or free to use as well.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


###Credits

All the data used (sprites, music, fx, etc), which are free to use, will be credited as well.

There are several Parts in the code (Basic Code Structure, Render System with blit queue and Fonts with Text Bliting) that have been forked from DOLIME CORPORATION. 
ALL code inside the disclaimer parts indicated in the code (Render System, Text Bltiting & UI Structure (Highly modified)  and core game structure belong to: [Dolime Corporation](https://github.com/Sanmopre/DOLIME-CORP-PROJECT-II)
They are also developing and RTS and we encourage you to check it out!

### Disclaimer

Our games are non-profit for educational purposes only. We do not intend to earn profit from it, since it is part of a university project taught at CITM-TTC in the degree Videogame Development and Design. All the assets (including sprites, music FX, etc) used in our games belong to their rightful owners, which will be credited.