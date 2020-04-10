#include "p2Defs.h"
#include "p2Log.h"

#include "PaintExtractor.h"

#include "j1Player.h"
#include "j1SceneManager.h"
#include "j1Map.h"
#include "j1Collision.h"
#include "j1Textures.h"

PaintExtractor::PaintExtractor(fPoint pos, int damage, j1Module* listener) : Entity(pos, damage, listener, nullptr) {

	// Handle data and initialize the PE
	*(ENTITY_TYPE*)&entityType = ENTITY_TYPE_PAINT_EXTRACTOR;
	*(ENTITY_CATEGORY*)&entityCategory = ENTITY_CATEGORY_STATIC_ENTITY;
	*(ENTITY_SIZE*)&entitySize = ENTITY_SIZE_VERY_BIG;

	maxLife = 100;
	this->currLife = maxLife - damage;
	this->pos = pos;

	constructionTime = 10.0f;

	size = { 100, 100 };
	isEntityFromPlayer = true;
}

PaintExtractor::~PaintExtractor() {}