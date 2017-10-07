#pragma once
#include "barbariananimationstore.h"

class Player
{
private: 
	unsigned int currentKey;
	Point<int> position;
	std::array<std::function<void()>, 255> actions;
	std::array<Animation*, 10> animations;
	AnimatedSprite* sprite;
	BarbarianAnimationStore* animationStore;
	
	void Walk(int direction)
	{
		sprite->position.x += direction;
		sprite->animation = animationStore->Get(BarbarianAnimationState::Walking);		
				
		/*if (animatedSprite->position.x < (display->gameresolution.w - barbarianWidth))
		*/
		/*if (animatedSprite->position.x > 0)
		*/
	}

public:
	void OnKeyDown(KeyboardEventData* eventData)
	{			
		currentKey = eventData->key;
	}

	void OnKeyUp(KeyboardEventData* eventData)
	{
		if (eventData->key == currentKey) {
			currentKey = 0;
			sprite->animation->Start();
			sprite->animation = animationStore->Get(BarbarianAnimationState::Standing);
		}
	}

	void Update()
	{				
		if (currentKey < actions.max_size() && actions[currentKey] != NULL) {
			actions[currentKey]();
		}
	}


	Player(GameEventHandler* eventHandler, AnimatedSprite* animatedSprite, BarbarianAnimationStore* store)
	{		
		animationStore = store;
		sprite = animatedSprite;
		eventHandler->Subscribe(GameEventType::OnKeyDown, [&](GameEventData* eventData){ 
			this->OnKeyDown((KeyboardEventData*)eventData); 
		});

		eventHandler->Subscribe(GameEventType::OnKeyUp, [&](GameEventData* eventData){
			this->OnKeyUp((KeyboardEventData*)eventData);
		});

		actions[KEYCODE_RIGHT] = [&]() {
			this->Walk (1);
		};

		actions[KEYCODE_LEFT] = [&]() {
			this->Walk(-1);
		};
	}

	~Player()
	{
	}
};
