# GUI DOCUMENT


***


## Main Index

+ [Menus (Flow Diagram)](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#menus-flow-diagram)

+ [HUD](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#hud)
  - [Technical point of view](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#technical-point-of-view)
  - [Artistic point of view](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#artistic-point-of-view)
  
+ [Sprites](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#sprites)

+ [Screens Layout](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#screens-layout)


***


## Menus (Flow Diagram)

The following flowchart diagram is the technical description of how the menus will interact with each other, with all the buttons, etc.

![Flow Diagram (Technical)](Photos_Wiki/Flow_Diagram_v03_Technical.png)


***


## HUD


### Technical point of view

We are using tools to create a HUD with is inclusive, intuitive and easy to use. For example, the "Exit" button will be always at the end of the menu. 

With everything, the design we have come up with is the following for the inside-game experience:

![HUD](https://user-images.githubusercontent.com/51851736/76066200-6fdcf300-5f8d-11ea-97ce-a5d686543a0c.png)


However, this was just a first draft we did for the GUI in general. You an see how it came together in the *Artistic poiint of view* below.



### Artistic point of view

![HUD1](https://user-images.githubusercontent.com/51851736/82118533-4fdd6300-9778-11ea-927e-3aa33b9456b8.png)
![HUD2](https://user-images.githubusercontent.com/51851736/82118535-510e9000-9778-11ea-85bd-46234709db43.png)

***


## Sprites


The sprites we are going to use are from a free GUI Pack from Unity by *Chocoball*, which can be found [here](https://assetstore.unity.com/packages/2d/gui/puzzle-stage-settings-gui-pack-147389). Some modifications will be made, however, to make it a perfect fit for our game.

Since this also allows to use different colours, we would like to implement different colours for each map, but, in case we don't have the time and it is not a priority, we would use only one of them.

| Asset | Sprite Idle | Sprite Hover |
| ----- | ----------- | ------------ | 
| Button (with strings) | . | . |
| Dialog frame | . | . |
| On | . | . |
| Off | . | . |
| Unfold (menu) | . | . |
| Fold (menu) | . | . |
| Slider + pivot | . | . |
| Keyboard selected | . | . |
| Gamepad selected | . | . |
| . | . | . |

The Font we are going to use is samble in 3 different sizes.


***


## Screens Layout

Usability is key when developing games, but usually performed too late in the game development cycle. Therefore, with the information take from the paper ["Early Usability Evaluation in Model-Driven video Game Development"](https://www.researchgate.net/figure/Screen-Navigation-metamodel_fig1_236153020), this is the strategy we are using in early stages of development. The following images below are taken from the mentioned paper above.

![Screen-Navigation-metamodel](https://user-images.githubusercontent.com/51851736/76338023-730f1080-62f8-11ea-843b-ccd151581d96.png)

![Screen-Layout-metamodel](https://user-images.githubusercontent.com/51851736/76338056-7e623c00-62f8-11ea-9659-08c24ac9e61a.png)

![Control-Mapping-metamodel](https://user-images.githubusercontent.com/51851736/76337964-625e9a80-62f8-11ea-9304-eeb95389757d.png)

The Following example is also taken from the page above:

![Street-Fighter-IV-screenshot-and-its-Screen-Layout-Diagram](https://user-images.githubusercontent.com/51851736/76337956-612d6d80-62f8-11ea-90f6-e5d8a2ad2f52.png)

For more information, please check out the [HUD](https://github.com/Needlesslord/BrainDeadStudios/blob/master/Docs/GUIDocument.md#hud), which can be found above and has all the data for the technical and artistic point of view of our game.


***









