# TDD DOCUMENT


***


## Main Menu

+ [Introduction](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#introduction)

+ [Technical Goals](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#technical-goals)
  - [Target Hardware](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#target-hardware)
  - [Performance Budgets](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#performance-budgets)

+ [Development Tools](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#development-tools)
  - [Development Hardware](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#development-hardware)
  - [Development Software](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#development-software)
  
+ [Game Mechanics](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#game-mechanics)

+ [Coding Style](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#coding-style)
  - Coding Style
  - Naming Convention
  - Variables
  - Loops
  - Conditionals
  - Classes and structs
  - XML

+ [UML](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#uml)

+ [Branching policy](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#branching-policy)
  
+ [Data Layout]()

+ [Version List](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#version-list)
  - [Planned](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#planned)
  - [Real](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#real)
  - [Scheduling]()

+ [Build Delivery Method](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/TDD.md#build-delivery-method)


***

## Introduction

"GAME NAME" is an isometric single player RTS game featuring a campaign with playable units, buildable structures and manageable resources where the player will have to fight against waves of enemies trying to destroy their base. The language used will be C++. For more about the game check out our [GDD](GDD.md).

**Development Team:**

[Nuria Lamonja](https://github.com/Needlesslord)
+ Team Leader, Management

[Tomás Carreras](https://github.com/tomascarreras1000)
+ Technical Director

[Marc Ariza](https://github.com/MarcArizaAlborni)
+ Design Director

[Enric Durán](https://github.com/EnricGDV)
+ Art Director

[Álex Lopez](https://github.com/AlexLA99)
+ QA Director

[Marc San José]()
+ Coder, Designer

***


## Technical Goals


### Target Hardware


### Performance Budgets


***


## Development Tools


### Development Hardware


### Development Software


**GitHub Commit Naming:**
Every commit should follow the following structure: Area of work + space + work done

**GitHub Branching:**
GitHub offers a feature for branching your projects in order to have a more clear and divided workspace. This feature is very useful for having different coders working in the same project without stepping on each other's toes and keeping their work divided. We will apply the following branching model:

![Image](Photos_Wiki/branching.jpg)

The master branch will be where the commits for the 4 main releases of the game will be allocated.

The versions branch will have the different milestones / sets of features that the team agreed to implement in the game.

The development branch will be the main working branch where every change implemented to the game is seen. However, smaller branches will appear so that unfinished work and uncomplete features can be uploaded without breaking the main branch and the code the rest of the team is working with. These smaller branches will also be useful for bug fixing and experimentation.

#### External Libraries


***


## Game Mechanics


***


## Coding Style

### Naming Convention

### Variables

### Loops

### Conditionals

### Classes and structs

### XML


***


## UML


***


## Version List


### Planned


### Real
  
*TO BE DELIVERED AT THE END OF THE PROJECT AND UPDATED DURING THE DEVELOPMENT*

### Scheduling

You can check this information in the [GDD Document](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GDD.md).


***


## Data Layout

The Data Layout was provided by the teacher in a template from which the GitHub Repository was created and is structured as shown below, together with the format in which every file should be stored:

+ Repository
  + Docs
      + ArtBible.md
      + AudioBible.md
      + GDD.md
      + GUIDocument.md
      + ProductionPlan.md
      + QAWorkflow.md
      + TDD.md
      + README.md
  + Screenshots
    + .png
  + Source
    + Deps
      + src
        + .hpp
        + .cpp
      + readme.txt
    + Resources
      + Audio
        + Fx
          + .wav
        + Music
          + .ogg
      + Fonts
        + LICENSE.txt
        + .tff
      + Maps
        + .tmx
      + Sprites
        + .png
      + config.xml
    + Game.vcxproj
  + LICENSE.md
  + Project.sln
  + README.md
  + RRSS.md
  
**File Naming Conventions:**
Even though there may be certain specific conventions for each type of files, the general naming conventions should be the use of     underscores to separate words and no use of capital letters. The logical naming hierarchy should go from general to particular. (i.e. tiles_terrain_grass.png)

***


## Build Delivery Method

We will be using GitHub Actions as a Continuous Integration tool to test our code every important feature commit in the Development branch in order to prove that it is functional in every possible environment in the [Target Platform(s)](TDD.md/#Target-Hardware). There will be a release for every one of these commits in GitHub.

***
