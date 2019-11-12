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

	default:
		cout << "Failed Loading Level : Level index out of range" << endl;
		return;
	}
}

void Motor::Play(RenderWindow &window) {

	this->window = &window;

	for (GameElement* gameElement : this->level->GameElements)
	{
		gameElement->Start();
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
		if (GetEvent(event, Event::KeyPressed))
		{
			//event.
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
	delete[] events;

	int eventsCount = 0;

	Event event;
	while (window->pollEvent(event))
	{
		events[eventsCount++] = event;
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

	cout << "Can't find Event in current Events" << endl;
	return false;
}