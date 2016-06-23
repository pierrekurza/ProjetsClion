//-----------------------------------------------------------------------------
//  TD IHM
//  application.hpp
//-----------------------------------------------------------------------------

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "scene.hpp"
#include <vector>

//-----------------------------------------------------------------------------
//  Application
//-----------------------------------------------------------------------------

class Application
{
	// Graphique
	sf::RenderWindow		_window;

	// Logique
	Scene					_scene;

public:
	Application():
	_window(sf::VideoMode(1000, 800), sf::String(L"Evénements")),
	_scene(_window)
	{
	}

	void run()
	{
		sf::Clock clock;
		while (_window.isOpen())
		{
			sf::Time tau = clock.restart();
			processEvents();
			update(tau);
			render();
		}
	}


protected:
	// Boucle événementielle
	void processEvents()
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			_scene.handleEvent(event);

			if (event.type == sf::Event::Closed)
				_window.close();
		}

	}

	void update(sf::Time& delta)
	{
		_scene.update(delta);
	}

	void render()
	{
		_window.clear();
		_scene.draw();
		_window.display();
	}
};

#endif
