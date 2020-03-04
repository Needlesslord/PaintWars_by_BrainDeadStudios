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
After many years of peace and tranquility, citizens of the "WORLD NAME" began to lose their colours and turned into monocromatic beeings. This was due to a corruption created


## CONTROLS




## GAMEPLAY

### Objective:
The main goal of the game is to destroy all enemy bases while you defend your own base from oposing armies. The enemy will attack the player with waves of enemies, each of them being stronger than the previous one.

### Player Win
The player has two ways of wining

If the player is able to manage resources correctly, defend his base from enemy attacks and build an army that can defeat all enemy bases, he will achieve victory.

He can also decide to defend the base from the enemy waves, and if he is succesfull defending his base from every single wave, he will achieve victory.

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
.|Food|0|
.|Research|0|


### ALLIED BUILDINGS:

#### MAIN BUILDING
 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|---------
.|Town Hall | 0 | Unbuildable |500| Main base building, if it gets destroyed the player will instantly lose even if he has remanining units. Produces a small amount of Paint. 

##### HOUSING

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|---------
.|Tent | 1 | Paint |50| Tier 1 Housing Building, very cheap but gives very little capacity
.|Shack | 2 | Paint +  Wood |100| Tier 2 Housing Building, cheap and gives some capacity
.|House | 3 | Wood + Metal Scrap |150| Tier 3 Housing Building, not very cheap and gives decent capacity
.|Mansion| 4 | Paint + Wood + Metal Scrap + Titanium |250| Tier 4 Housing Building, very expensive and gives lots of capacity

##### RESOURCE BUILDINGS

**PAINT**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|-----------
.|Paint Extractor v1 | 1 | Paint |100| Tier 1 Paint Extraction, cheap and gather small amount of paint. Can only be placed in paint geysers
.|Paint Extractor v2 | 2 | Paint + Wood |100| Tier 2 Paint Extraction, gathers a regular amount of paint. Can only be placed in paint geysers
.|Paint Extractor v3 | 3 | Wood + Metal Scrap |100| Tier 3 Paint Extraction, gathers a big amount of paint. Can only be placed in paint geysers

**WOOD**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|---------
.|Lumberjack cabin | 1 | Paint |100| Tier 1 Wood Gatherer, produces small amount of wood. Needs trees and workers to work
.|Carpentry Station | 2 | Paint Wood |100| Tier 2 Wood Collector, produces regular amount of wood. Needs trees and workers to work
.|Lumbermill | 3 | Wood + Metal Scrap |100| Tier 3 Wood Collector, produces big amount of wood. Needs trees and workers to work

**METAL SCRAP**

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|--------
.|Metal Gatherer | 1 | Paint |100| Tier 1 Metal Gatherer, produces small amount of metal. Needs metal scrap piles and workers to work
.|Metal Collector | 2 | Paint Wood |100| Tier 2 Metal Collector, produces regular amount of metal. Needs metal scrap piles and workers to work
.|Metal Fabricator| 3 | Wood + Metal Scrap |100| Tier 3 Metal Collector, produces big amount of metal. Needs metal scrap piles and workers to work

**TITANIUM**

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|-----------
.|Titanium Extractor | 4 | Paint + Wood + Metal Scrap + Titanium |200| Tier 4 Titanium Extractor, produces a very small amount of titanium, can be placed anywhere, doesn't need workers (Only 1 building of this kind)

**FOOD**

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|-----------
.|Farm | 0 | Paint + Wood |50| Automatically creates Food
##### EXPLORATION 

 SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|----------
.|Watchtower | 2 | Paint + Wood |50| Tier 2 exploration tower, reveals a small area around the building, 
.|Radar | 3 | Paint + Metal Scrap |150| Tier 3 exploration tower, reveals a big area around the building
.|Atlas| 4 | Paint + Wood + Scrap + Titanium |250| Tier 4 exploration tower, reveals the entire map, very expensive to build (Only 1 building of this kind)

##### RESEARCH

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|--------
.|Library | 2 | Paint + Wood + Scrap |100| Tier 2 reasearch building, allows the player to research low/mid tier upgrades, upgrades made with paint/Wood (Only 1 building of this kind)
.|Laboratory | 3 | Paint + Wood + Scrap |150| Tier 3 research building, allows the player to research low/mid/high tier upgrades, upgrades made with Paint/Wood/metal Scrap (Only 1 building of this kind)
.|High Tech Lab| 4 | Paint + Wood + Scrap + Titanium |250| Tier 4 research building, allows the player to research low/mid/high/elite tier upgrades, upgrades made with paint/Wood/Metal Scrap/titanium (Only 1 building of this kind)


#### DEFENSIVE BUILDINGS 

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH|DAMAGE| UTILITY | TARGET
 ---------|------------ | ------------- | -----------| ---------|--------|------------------|-------------|
.|Ranger Tower | 2 | Paint + Wood |200|10| Tier 2 tower that shoots at enemies that get close, regular range and damage, low attack speed| Anything
.|Decoy | 2 | Paint + Wood |150|0| Structure that deals no damage but attracts enemies into attacking it, High HP | Anything
.|Wooden Stockade| 2 | Paint + Wood |50|0| Wooden structure that will keep enemies outside of the base, allied units can't walk through it | Grounded
.|Wooden Stockade Door| 2 | Paint + Wood |75|0| Wooden structure that will keep enemies outside of the base, works as a door for allied units | Grounded
.|Bunker|3|Paint + Metal Scrap |250|20| Tier 3 tower that has high HP and can hold enemies for some time, it has average damage and attack speed, and low range | Anything
.|Paint Dispenser|3| Paint + Metal Scrap |150|0| Tier 3 tower that throws paint to slow enemies near it, it deals no damage | Anything
.|Paint Cannon |3| Paint + Metal Scrap |200|40| Tier 3 tower that throws blobs of paint to enemies, deals AOE damage | Grounded
.|Explosive Decoy| 3 | Paint + Metal Scrap|200|100| Structure that attracts enemies into attacking it, High HP. When it is destroyed, deals High AOE damage | Anything
.|Metal Wall |3| Paint + Metal Scrap |100|0|  Metal structure that will keep enemies outside of the base, allied units can't walk through it | Grounded
.|Metal Wall Door| 3 | Paint + Metal Scrap| 125|0| Metal structure that will keep enemies outside of the base, works as a door for allied units | Grounded
.|Paint Laser| 4 | Paint + Metal Scrap + Titanium |250|50|Tier 4 tower that deals massive damage to a single target, high range and low attack speed | Anything
.|Paint MachineGun| 4 | Paint + Metal Scrap + Titanium |250|10|Tier 4 tower that deals regular damage to a single target, medium range and extremely high attack speed | Anything


### ALLIED UNITS

#### SPECIFIC ROLES 

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | CHARACTERISTIC | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Painter | 1 | Paint |20|1| Ground Unit. Recollect resources and building| Resources/Grounded
.|Explorer | 1 | Paint |35|5| Ground Unit. Very Fast | Grounded


#### INFANTRY

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | CHARACTERISTIC | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Paint Recruit | 1 | Paint |30|10| Ground Unit | Grounded
.|Paint Squire | 2 | Paint + Wood |40|15| Ground Unit | Grounded
.|Paint Knight | 3 | Paint + Metal Scrap |75|20| Ground Unit |  Grounded
.|Paint Chosen | 4 | Paint + Metal Scrap + Aluminium |150|30| Ground Unit| Grounded

#### RANGED

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | CHARACTERISTIC | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Paint Ranger | 1 | Paint |20|10| Ground Unit. Ranged (Low Range & Attack Speed) | Anything
.|Paint Sniper | 3 | Paint + Wood |30|25| Ground Unit. Ranged (High Range & Low Attack Speed) | Anything
.|Paint Trooper | 3 | Paint + Metal Scrap |60|15| Ground Unit. (Low Range & High Attack Speed) |  Anything
.|Paint Mortar | 4 | Paint + Metal Scrap + Aluminium |100|40| Ground Unit. (High Range & Slow Attack Speed, AOE Damage) | Grounded


#### SPECIAL

SPRITE|   NAME   | TIER |   REQUIRED RESOURCES | HEALTH| DAMAGE | CHARACTERISTIC | TARGET
 ---------|------------ | ------------- | -----------| ---------|-------|-------|-------
.|Blob Rider | 1 | Paint |40|15|Ground Unit | Anything
.|Paint Amalgam| 1 |Paint |75|30| Ground Unit | Anything
.|Blo-Bat | 2 | Paint |15|10| Flying unit, very fast | Anything
.|Auto-Sprinkler| 2 |200|10|Paint + Metal Scrap | Ground Unit. AOE constant Damage around the unit | Anything
.|Paintshee | 3 | Paint|30|50| Ground Unit, Extremely Fast | Grounded
.|Paint-O-Bot | 3 |Paint + Metal Scrap|150|10| Ground Unit, Acts as a basic painter but with better stats | Resources/Grounded
.|P-Rex | 4 | Paint + Metal Scrap + Titanium |400|75| Ground Unit. No colision with other units | Anything


### ENEMY
#### ENEMY BUILDINGS

SPRITE|   NAME         | TIER |   REQUIRED RESOURCES |HEALTH| UTILITY
 ---------|------------ | ------------- | -----------| ---------|----------
.|Spawner | 5 | 0|500| Enemy spawner


#### ENEMY UNITS

SPRITE|   NAME   | TIER  | HEALTH| DAMAGE | CHARACTERISTIC | TARGET
 ---------|------------ |  -----------| ---------|-------|-------|-------
.|Paint Slime | 5 | Paint |30|15| Ground Unit | Grounded
.|Dark Rider | 5 | Paint + Wood |50|25| Ground Unit | Grounded
.|Corrupted Knight | 5 | 75|40| Ground Unit | Grounded
.|Explosive Blob | 5 |50|300| Ground Unit. AOE damage around the unit, dies after it attacks| Grounded
.|Forsaken Sniper | 5 | 100|25| Ground Unit| Grounded
.|Floating Blob | 5 | 20|15| Flying| Grounded
.|Corrupted Eye | 5 | 150|30| Flying| Grounded
.|Black Executioner | 5 |300|40| Ground Unit| Grounded
.|Corruptor | 6 | (350) first two appearances, (450) 3rd and 4th appearance, (500) 5th appearance & onwards|(50) first two appearances, (100) 3rd and 4th appearance, (200) 5th appearance & onwards|BOSS. Appears every 3 waves or after destroying a spawner | Anything
.|Chroma-King | 6 | 2000| 500 |FINAL BOSS, Extremely Slow & only appears in the last wave| Town Hall












