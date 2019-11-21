#include "Motor.h"

Motor::Motor() {}

void Motor::SetLevel(int index) 
{
	delete level;
	level = new Level();

	if (index == 0) 
	{
		/*TEMPORAIRE*/

		Player* p1 = new Player();
		p1->position = Vector2f(100, 100);
		level->GameElements.push_back(p1);
		level->GameElements.push_back(new Lim());
		level->GameElements.push_back(new Instructions);

		cout << "Successful Loaded Level " << index << endl;
	}
	else
	{
		cout << "Failed Loading Level : Level index " << index << " out of range" << endl;
	}
}

void Motor::Play(RenderWindow &window) {

	this->window = &window;

	for (GameElement* gameElement : level->GameElements)
	{
		gameElement->Init(&window, &events);
		gameElement->Start();
	}

	while (window.isOpen())
	{
		RefreshEvents();
		
		window.clear(Color::Black);

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->Update();
			gameElement->Draw();
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
		events.push_back(event);
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