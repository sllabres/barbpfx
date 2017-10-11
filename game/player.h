#pragma once
#include "barbariananimationstore.h"

class Player
{
private:
	enum PlayerState { Walking, Standing, Attacking };

	unsigned int currentKey;
	Point<int> position;
	std::array<std::function<void()>, 255> actions;
	AnimatedSprite* sprite;
	BarbarianAnimationStore* animationStore;
	bool animationLock = false;
	int xvelocity;

	PlayerState state = PlayerState::Standing;


	void Walk()
	{
		// apply movement rules
		// 1) must be within boundaries depending on direction
		// 2) must not walk through another character
		// 3) Don't apply when animation locked		

		sprite->position.x += xvelocity;
		sprite->animation = sprite->animation = animationStore->Get(xvelocity > 0 ? BarbarianAnimationStore::BarbarianAnimationState::Walking : BarbarianAnimationStore::BarbarianAnimationState::WalkingAway);


		/*if (animatedSprite->position.x < (display->gameresolution.w - barbarianWidth))
		*/
		/*if (animatedSprite->position.x > 0)
		*/
	}

	void Attack()
	{
		if (animationLock == false)
		{
			sprite->animation = animationStore->Get(BarbarianAnimationStore::BarbarianAnimationState::SpinAttack);
			sprite->animation->Start();
			animationLock = true;
		}		
		else if (sprite->animation->currentframe < 4)
		{
			sprite->position.x += xvelocity;
		}
		else if (sprite->animation->currentframe == 5)
		{
			animationLock = false;
		}
	}

	void Stand()
	{
		animationLock = false;
		currentKey = 0;
		sprite->animation->Start();
		sprite->animation = sprite->animation = animationStore->Get(BarbarianAnimationStore::BarbarianAnimationState::Standing);
	}

	bool IsWalkingLeft() {
		if (currentKey == KEYCODE_LEFT && animationLock == false) {
			return true;
		}

		return false;
	}

	bool IsWalkingRight() {
		if (currentKey == KEYCODE_RIGHT && animationLock == false) {
			return true;
		}

		return false;
	}

	bool IsStanding() {
		if (currentKey == 0 && animationLock == false) {
			return true;
		}

		return false;
	}

	bool IsAttacking() {
		if (currentKey == KEYCODE_SPACE || animationLock == true) {
			return true;
		}

		return false;
	}

public:
	void Update()
	{
		if (IsWalkingLeft()) {
			state = PlayerState::Walking;
			xvelocity = -1;
		}

		if (IsWalkingRight()) {
			state = PlayerState::Walking;
			xvelocity = 1;
		}

		if (IsAttacking()) {
			state = PlayerState::Attacking;
			xvelocity = 1;
		}

		if (IsStanding()) {
			state = PlayerState::Standing;
			xvelocity = 0;
		}

		actions[state]();
	}

	void OnKeyDown(KeyboardEventData* eventData)
	{
		currentKey = eventData->key;
	}

	void OnKeyUp(KeyboardEventData* eventData)
	{
		if (eventData->key == currentKey) {
			currentKey = 0;
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

		actions[PlayerState::Walking] = [&]() {
			this->Walk();
		};

		actions[PlayerState::Standing] = [&]() {
			this->Stand();
		};

		actions[PlayerState::Attacking] = [&]() {
			this->Attack();
		};
	}

	~Player()
	{
	}
};