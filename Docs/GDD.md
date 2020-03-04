# GDD DOCUMENT




## OVERVIEW 

"GAME NAME" is an isometric single player RTS game featuring a campaign with playable units, buildable structures and manageable resources where the player will have to fight against waves of enemies trying to destroy his base.

The game is located in a paint themed world where resources, units and buildings will be related to paint.


## GAME PILARS

### Resource Management:
The player will have to manage resources and invest them in creating new units, building new defences and upgrading the base to be able to repel the enemy armies.

### Exploration: 
Exploring the map will reward the player with new resources and space to keep upgrading the base and adquiring new tools to defeat the enemy.

### Attack The Enemy Base: 
The player will also have to attack enemy bases distributed around the map, these bases will be protected by enemy units and will have to be destroyed to beat the game.

### Endless Waves:
Enemy waves will come constantly after a certain amount of time or specific actions are made by the player. The only way to stop them will be to destroy the enemy bases.


## PLOT



## CONTROLS




## GAMEPLAY

### Objective:
The main goal of the game is to destroy all enemy bases while you defend your own base from oposing armies. The enemy will attack the player with waves of enemies, each of them beeing stronger than previously.

### Player Win
If the player is able to manage resources correctly, defend his base from enemy attacks and build an army that can defeat all enemy bases, he will achieve victory.

### Player Lose
The player will lose if his Main Building gets destroyed, this will happen if he is not able to defeat the enemy waves that attack his base.

### Main Gameplay Characteristics

**Build & Manage Your Base:** The player will be able to build and upgrade several buildings to strengthen his base by using resrouces that he will have to manage accordingly in order to defend from the enemy armies that will attack. 

**Command Armies:** The player will have at its disposal several  buildings to strengthen his army and attack the enemy to finally stop the continuous attacks from enemy armies.

**Enemy Waves:** The player will have to defend from several waves of enemies, with increasing difficulty as the game progresses. These waves will come at certain situations in the game such as the player destroying an enemy base, or after a certain amount of time.

**Explore the map:** The map is full of scarce resources that the player will be able to collect in order to reinforce his army or upgrade even further his base.

## GAME ELEMENTS
#### RESOURCES:

SPRITE|   NAME         | TIER 
 ---------|------------ | ------------- 
.|Paint | 1 | 
.|Wood | 2 | 
.|Metal Scrap | 3 | 
.|Titanium | 4 | 


### ALLIED BUILDINGS:

##### HOUSING

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|---------
.|Tent | 1 | Paint | Tier 1 Housing Building, very cheap but gives very little capacity
.|Shack | 2 | Paint Wood | Tier 2 Housing Building, cheap and gives some capacity
.|House | 3 | Leather + Metal Scrap | Tier 3 Housing Building, not very cheap and gives decent capacity
.|Mansion| 4 | Paint + Leather + Metal Scrap + Titanium | Tier 4 Housing Building, very expensive and gives lots of capacity

##### RESOURCE BUILDINGS

**PAINT**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|-----------
.|Paint Extractor v1 | 1 | Paint |150| Tier 1 Paint Extraction, cheap and gather small amount of paint. Can only be placed in paint geysers
.|Paint Extractor v2 | 2 | Paint + Wood |200| Tier 2 Paint Extraction, gathers a regular amount of paint. Can only be placed in paint geysers
.|Paint Extractor v3 | 3 | Leather + Metal Scrap |250| Tier 3 Paint Extraction, gathers a big amount of paint. Can only be placed in paint geysers

**WOOD**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|---------
.|Lumberjack cabin | 1 | Paint |150| Tier 1 Wood Gatherer, produces small amount of wood. Needs trees and workers to work
.|Carpentry Station | 2 | Paint Wood |200| Tier 2 Wood Collector, produces regular amount of wood. Needs trees and workers to work
.|Lumbermill | 3 | Leather + Metal Scrap |250| Tier 3 Wood Collector, produces big amount of wood. Needs trees and workers to work

**METAL SCRAP**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|--------
.|Metal Gatherer | 1 | Paint |150| Tier 1 Metal Gatherer, produces small amount of metal. Needs metal scrap piles and workers to work
.|Metal Collector | 2 | Paint Wood |200| Tier 2 Metal Collector, produces regular amount of metal. Needs metal scrap piles and workers to work
.|Metal Fabricator| 3 | Leather + Metal Scrap |250| Tier 3 Metal Collector, produces big amount of metal. Needs metal scrap piles and workers to work

**TITANIUM**

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|-----------
.|Titanium Extractor | 4 | Paint + Leather + Scrap + Titanium |250| Tier 4 Titanium Extractor, produces a very small amount of titanium, can be placed anywhere, doesn't need workers (Only 1 building of this kind)


##### EXPLORATION 

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|----------
.|Watchtower | 2 | Paint + Leather |100| Tier 2 exploration tower, reveals a small area around the building, 
.|Radar | 3 | Paint + Metal Scrap |200| Tier 3 exploration tower, reveals a big area around the building
.|Atlas| 4 | Paint + Leather + Scrap + Titanium |400| Tier 4 exploration tower, reveals the entire map, very expensive to build (Only 1 building of this kind)

##### RESEARCH

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|--------
.|Library | 2 | Paint + Leather + Scrap |200| Tier 2 reasearch building, allows the player to research low/mid tier upgrades, upgrades made with paint/leather (Only 1 building of this kind)
.|Laboratory | 3 | Paint + Leather + Scrap |300| Tier 3 research building, allows the player to research low/mid/high tier upgrades, upgrades made with paint/leather/metal (Only 1 building of this kind)
.|High Tech Lab| 4 | Paint + Leather + Scrap + Titanium |400| Tier 4 research building, allows the player to research low/mid/high/elite tier upgrades, upgrades made with paint/leather/metal/titanium (Only 1 building of this kind)


#### DEFENSIVE BUILDINGS 

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH|DAMAGE| UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|--------|------------------|-------------|
.|Ranger Tower | 2 | Paint+ Leather |150|10| Tier 2 tower that shoots at enemies that get close, regular range and damage, low attack speed| Anything
.|Decoy | 2 | Paint + Wood |300|0| Structure that deals no damage but attracts enemies into attacking it, High HP | Anything
.|Wooden Stockade| 2 | Paint + Wood |50|0| Wooden structure that will keep enemies outside of the base, allied units can't walk through it | Grounded
.|Wooden Stockade Door| 2 | Paint + Wood |75|0| Wooden structure that will keep enemies outside of the base, works as a door for allied units | Grounded
.|Bunker|3|Paint + Metal Scrap |300|15| Tier 3 tower that has high HP and can hold enemies for some time, it has average damage and attack speed, and low range | Anything
.|Paint Dispenser|3| Paint + Metal Scrap |250|0| Tier 3 tower that throws paint to slow enemies near it, it deals no damage | Anything
.|Paint Cannon |3| Paint + Metal Scrap |200|25| Tier 3 tower that throws blobs of paint to enemies, deals AOE damage | Grounded
.|Explosive Decoy| 3 | Paint + Metal Scrap|400|100| Structure that attracts enemies into attacking it, High HP. When it is destroyed, deals High AOE damage | Anything
.|Metal Wall |3| Paint + Metal Scrap |100|0|  Metal structure that will keep enemies outside of the base, allied units can't walk through it | Grounded
.|Metal Wall Door| 3 | Paint + Metal Scrap| 150|0| Metal structure that will keep enemies outside of the base, works as a door for allied units | Grounded
.|Paint Laser| 4 | Paint + Metal Scrap + Titanium |300|50|Tier 4 tower that deals massive damage to a single target, high range and low attack speed | Anything
.|Paint MachineGun| 4 | Paint + Metal Scrap + Titanium |300|10|Tier 4 tower that deals regular damage to a single target, medium range and extremely high attack speed | Anything


### ALLIED UNITS

#### SPECIFIC ROLES 

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Painter | 1 | Paint |30|5| Recollect (Typical villager in RTS games), can also fight if needed to, but is weak | Resources
.|Explorer | 1 | Paint |45|5| Very fast melee unit, great for exploring and scouting, terrible at fighting | Grounded

#### INFANTRY

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Paint Recruit | 1 | Paint |50|10| Weak low tier melee unit, decent for early game, trash mid/late game | Grounded
.|Paint Squire | 2 | Paint + Wood |75|15| Regular mid tier melee unit, good early game, regular mid/late game | Grounded
.|Paint Knight | 3 | Paint + Metal Scrap |100|20| Good high tier unit, good any stage of the game |  Grounded
.|Paint Chosen | 4 | Paint + Metal Scrap + Aluminium |300|30| Elite unit, very expensive and will win any direct engagement against him | Grounded

#### RANGED

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Paint Ranger | 1 | Paint |20|10| Weak low tier melee unit, decent for early game, trash mid/late game | Anything
.|Paint Sniper | 3 | Paint + Wood |30|25| Good high tier unit, great range and damage, low attack speed | Anything
.|Paint Trooper | 3 | Paint + Metal Scrap |75|15| Good high tier unit, good any stage of the game |  Anything
.|Paint Mortar | 4 | Paint + Metal Scrap + Aluminium |100|40| Elite unit, very expensive and will win any direct engagement against him | Grounded


#### SPECIAL

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Blob Rider | 1 | Paint | Weak low tier melee unit, decent for early game, trash mid/late game | Anything
.|Paint Amalgam| 1 |Paint | Good high tier unit, great range and damage, low attack speed | Anything
.|Blo-Bat | 2 | Paint | Weak low tier melee unit, decent for early game, trash mid/late game | Anything
.|Paint-O-Bot| 2 |Paint | Good high tier unit, great range and damage, low attack speed | Anything
.|Paint-Drops | 3 | Paint | Weak low tier melee unit, decent for early game, trash mid/late game | Anything
.|Mecha-Painter | 3 |Paint| Villager and fighter |  Anything
.|P-Rex | 4 | Paint + Metal Scrap + Titanium | Elite unit, very expensive and will win any direct engagement against him | Grounded













