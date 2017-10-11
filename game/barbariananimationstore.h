#pragma once
#include <array>

class BarbarianAnimationStore
{
private:
	std::array<Animation*, 10> animations;
public:
	enum BarbarianAnimationState { Walking, WalkingAway, Standing, SpinAttack };

	Animation* Get(BarbarianAnimationState state) {
		return animations[state];
	}

	BarbarianAnimationStore()
	{
		Animation* standing = new Animation();
		standing->frames.Add(new AnimationFrame(0, 30));
		standing->frames.Add(new AnimationFrame(1, 30));

		Animation* walking = new Animation();
		walking->frames.Add(new AnimationFrame(2, 15));
		walking->frames.Add(new AnimationFrame(3, 15));
		walking->frames.Add(new AnimationFrame(4, 15));
		walking->frames.Add(new AnimationFrame(0, 15));

		Animation* walkingBack = new Animation();
		walkingBack->frames.Add(new AnimationFrame(4, 15));
		walkingBack->frames.Add(new AnimationFrame(3, 15));
		walkingBack->frames.Add(new AnimationFrame(2, 15));
		walkingBack->frames.Add(new AnimationFrame(0, 15));

		Animation* spinattack = new Animation();
		spinattack->frames.Add(new AnimationFrame(5, 15));
		spinattack->frames.Add(new AnimationFrame(6, 15));
		spinattack->frames.Add(new AnimationFrame(7, 15));
		spinattack->frames.Add(new AnimationFrame(8, 15));
		spinattack->frames.Add(new AnimationFrame(9, 15));
		spinattack->frames.Add(new AnimationFrame(9, 15));
		//spinattack->loopanimation = false;

		animations[BarbarianAnimationState::Standing] = standing;
		animations[BarbarianAnimationState::Walking] = walking;
		animations[BarbarianAnimationState::WalkingAway] = walkingBack;
		animations[BarbarianAnimationState::SpinAttack] = spinattack;
	}

	~BarbarianAnimationStore()
	{
	}
};

