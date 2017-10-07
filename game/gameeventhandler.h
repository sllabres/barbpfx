#pragma once
#include <list>
#include <map>
#include <array>
#include <functional>

enum GameEventType { OnKeyDown, OnKeyUp };

class GameEventData
{
	public:
		GameEventType Type;
};

class KeyboardEventData : public GameEventData
{	
public:
	unsigned int key;	

	KeyboardEventData(unsigned int keyPressed, GameEventType eventType)
	{
		key = keyPressed;
		Type = eventType;
	}	
};

class GameEventHandler
{
private:	
	std::list<std::pair<GameEventType, std::function<void(GameEventData*)>>> events;
public:		

	void Subscribe(GameEventType eventType, std::function<void(GameEventData*)> callback)
	{
		std::pair<GameEventType, std::function<void(GameEventData*)>> map;
		map.first = eventType;
		map.second = callback;
		events.push_back(map);
	}

	void Publish(GameEventData* eventData) 
	{
		for (std::list<std::pair<GameEventType, std::function<void(GameEventData*)>>>::iterator i = events.begin(); i != events.end(); ++i)
		{			
			if (i->first == eventData->Type) {
				i->second(eventData);
			}
		}
	}

	GameEventHandler()
	{
	}

	~GameEventHandler()
	{		
	}
};