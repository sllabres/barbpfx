
#pragma once

#include "../framework/pfx.h"
#include "../framework/core/indexsort.h"
#include "../framework/core/easing.h"
#include "gameeventhandler.h"
#include "player.h"

class Game : public Stage
{

private:	
	SpritePlane* spritePlane;	
	GameEventHandler* gameEventHandler;
	Player* player;

	Sprite* background;		
	TilemapPlane* tileMap;
	Display* display;
	bool attackLocked = false;
	int attackFrameCount = 0;
	int currentInput;

	Animation* standing;
	Animation* walking;
	Animation* spinattack;
	Animation* headless;
	AnimatedSprite* animatedSprite;
	AnimatedSprite* dummySprite;
	AnimatedSprite* head;
	const int barbarianHeight = 67;
	const int barbarianWidth = 70;	

public:
	void LoadResources() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	void Finish() override;
	void EventOccured(Event* What) override;
	void Update() override;
};