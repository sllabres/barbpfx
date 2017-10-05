#include "game.h"

void Game::LoadResources()
{
	display = FX->video.GetDisplay(0);
	spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;

	background = new Sprite(new Bitmap("resources/main.bmp"));
	background->position.x = display->gameresolution.w / 2;
	background->position.y = display->gameresolution.h / 2;
	background->draworigin.x = background->GetDimensions().w / 2;
	background->draworigin.y = background->GetDimensions().h / 2;
	spritePlane->sprites.Add(background);

	standing = new Animation();
	standing->frames.Add(new AnimationFrame(0, 30));
	standing->frames.Add(new AnimationFrame(1, 30));

	walking = new Animation();	
	walking->frames.Add(new AnimationFrame(2, 15));
	walking->frames.Add(new AnimationFrame(3, 15));
	walking->frames.Add(new AnimationFrame(4, 15));
	walking->frames.Add(new AnimationFrame(0, 15));

	spinattack = new Animation();
	spinattack->frames.Add(new AnimationFrame(5, 15));
	spinattack->frames.Add(new AnimationFrame(6, 15));
	spinattack->frames.Add(new AnimationFrame(7, 15));
	spinattack->frames.Add(new AnimationFrame(8, 15));
	spinattack->frames.Add(new AnimationFrame(9, 15));
	spinattack->frames.Add(new AnimationFrame(9, 15));

	headless = new Animation();
	headless->frames.Add(new AnimationFrame(10, 15));

	Size<int> tileSize(barbarianWidth, barbarianHeight);
	Atlas* tiles = new Atlas(new Bitmap("resources/barbarian-tileset.png"), tileSize);
	animatedSprite = new AnimatedSprite(tiles, standing);
	animatedSprite->position.y = display->gameresolution.h - barbarianHeight - 10;
	spritePlane->sprites.Add(animatedSprite);

	dummySprite = new AnimatedSprite(tiles, headless);
	dummySprite->position.y = display->gameresolution.h - barbarianHeight - 10;
	dummySprite->position.x = 200;	
	spritePlane->sprites.Add(dummySprite);
}

void Game::Start()
{
}

void Game::Pause()
{
}

void Game::Resume()
{
}

void Game::Finish()
{
}

void Game::EventOccured(Event* What)
{	
	if (What->type == EventTypes::EVENT_INPUT_KEYBOARD_KEYUP && attackLocked == false)
	{
		currentInput = 0;
		animatedSprite->animation = standing;
		walking->currentframe = 0;
	}
}

void Game::Update()
{
	if (attackLocked == false) {
		if (currentInput == KEYCODE_RIGHT) {
			animatedSprite->animation = walking;
			if (animatedSprite->position.x < (display->gameresolution.w - barbarianWidth))
				animatedSprite->position.x += 1;
		}
		if (currentInput == KEYCODE_LEFT) {
			animatedSprite->animation = walking;
			if (animatedSprite->position.x > 0)
				animatedSprite->position.x -= 1;
		}
	}	
	else if(spinattack->currentframe == 5) {
		attackLocked = false;
		currentInput = 0;
		animatedSprite->animation = standing;
		walking->currentframe = 0;
	} else {
		if (animatedSprite->position.x < (display->gameresolution.w - barbarianWidth) && spinattack->currentframe < 4)
			animatedSprite->position.x += 1;
	}

	if (FX->input.keyboard.IsKeyDown(KEYCODE_RIGHT)) {		
		currentInput = KEYCODE_RIGHT;
	}
	else if (FX->input.keyboard.IsKeyDown(KEYCODE_LEFT)) {
		currentInput = KEYCODE_LEFT;
	}

	else if (FX->input.keyboard.IsKeyDown(KEYCODE_SPACE)) {
		animatedSprite->animation = spinattack;
		spinattack->Start();
		attackLocked = true;
	}
}