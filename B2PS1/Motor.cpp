#include "Motor.h"

Motor::Motor() {}

void Motor::SetLevel(int index) 
{
	delete level;
	level = new Level();

	switch (index)
	{
	case 0:

		/*TEMPORAIRE*/

		level->GameElements.push_back(new Player());

		cout << "Successful Loaded Level " << index << endl;
		break;

	default:
		cout << "Failed Loading Level : Level index " << index << " out of range" << endl;
		break;
	}
}

void Motor::Play(RenderWindow &window) {

	this->window = &window;

	for (GameElement* gameElement : level->GameElements)
	{
		gameElement->Start(&events);
	}

	while (window.isOpen())
	{
		RefreshEvents();
		
		Event event;
		if (GetEvent(event, Event::Closed)) 
		{
			window.close();
		}
		if (GetEvent(event, Event::Resized))
		{
			cout << "height : " << event.size.height << " width : " << event.size.width << endl;
		}

		window.clear(Color::Black);

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->Update();
			gameElement->Draw(window);
		}

		window.display();
	}
}

void Motor::RefreshEvents()
{
	events.clear();
	
	Event event;
	int eventsCount = 0;
	
	while (window->pollEvent(event))
	{
		events.push_back(event);
	}
}

bool Motor::GetEvent(Event& _event, Event::EventType eventType)
{
	for (Event event : events)
	{
		if (event.type == eventType) 
		{
			_event = event;
			return true;
		}
	}

	return false;
}