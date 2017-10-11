#include "game.h"
#include "player.h"
#include "barbariananimationstore.h"

void Game::LoadResources()
{
	gameEventHandler = new GameEventHandler();
	BarbarianAnimationStore* animationStore = new BarbarianAnimationStore();

	display = FX->video.GetDisplay(0);
	spritePlane = new SpritePlane(display);
	spritePlane->draworder = SpritePlaneDrawOrder::YPOSITION;

	background = new Sprite(new Bitmap("resources/main.bmp"));
	background->position.x = display->gameresolution.w / 2;
	background->position.y = display->gameresolution.h / 2;
	background->draworigin.x = background->GetDimensions().w / 2;
	background->draworigin.y = background->GetDimensions().h / 2;
	spritePlane->sprites.Add(background);

	/*headless = new Animation();
	headless->frames.Add(new AnimationFrame(10, 15));*/

	Size<int> tileSize(barbarianWidth, barbarianHeight);
	Atlas* tiles = new Atlas(new Bitmap("resources/barbarian-tileset.png"), tileSize);
	animatedSprite = new AnimatedSprite(tiles, animationStore->Get(BarbarianAnimationStore::BarbarianAnimationState::Standing));
	animatedSprite->position.y = display->gameresolution.h - barbarianHeight - 10;
	spritePlane->sprites.Add(animatedSprite);

	player = new Player(gameEventHandler, animatedSprite, animationStore);

	/*dummySprite = new AnimatedSprite(tiles, headless);
	dummySprite->position.y = display->gameresolution.h - barbarianHeight - 10;
	dummySprite->position.x = 200;
	spritePlane->sprites.Add(dummySprite);*/
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
	if (What->type == EventTypes::EVENT_INPUT_KEYBOARD_KEYUP)
	{
		gameEventHandler->Publish(new KeyboardEventData(What->data.input.keyboard.keycode, GameEventType::OnKeyUp));
	}

	if (What->type == EventTypes::EVENT_INPUT_KEYBOARD_KEYDOWN)
	{
		gameEventHandler->Publish(new KeyboardEventData(What->data.input.keyboard.keycode, GameEventType::OnKeyDown));
	}
}

void Game::Update()
{
	player->Update();
}