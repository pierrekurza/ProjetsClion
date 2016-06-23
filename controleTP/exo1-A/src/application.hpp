#ifndef	APPLICATION_HPP
#define APPLICATION_HPP

#include "scene.hpp"

class Application
{
private:
	sf::RenderWindow	_window;
	Scene				_scene;// Objet graphique

private:
	sf::Vector2u getCenter()
	{
		sf::Vector2u monCentre;
		monCentre.x = _window.getSize().x / 2;
		monCentre.y = _window.getSize().y / 2;
		return monCentre;
	}

	void processEvents()
	{
		sf::Event event;
		while(_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				_window.close();
			else
				_scene.processEvent(event);
		}
	}

	void update()
	{
		_scene.update();
	}

	void render()
	{
		_window.clear();
		_scene.draw(_window);
		_window.display();
	}

public:
	Application() :
		_window(sf::VideoMode(800, 600), "Formes & Couleurs"),
		_scene(getCenter())
	{
	}

	~Application()
	{}

	void run()
	{
		do
		{
			processEvents();
			update();
			render();
		}
		while(_window.isOpen());
	}
};

#endif
