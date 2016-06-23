#ifndef	APPLICATION_HPP
#define APPLICATION_HPP

#include "circle.hpp"
#include "square.h"
#include "polygons.hpp"
#include "triangles.hpp"
#include "Ellipse.hpp"

class Application
{
// Attributs
private:
	sf::RenderWindow	_window;// Attribut graphique
	Circle				_circle;// Objet graphique
	Square				_square;
	Polygons			_polygons;
	Triangle			_triangleRota;
	Ellipse				_ellipse;

// Méthodes
private:
	void processEvents()
	{
		sf::Event event;
		while(_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				_window.close();
			else {
				_circle.processEvent(event);
				_polygons.processEvent(event);
				_square.processEvent(event);
				_triangleRota.processEvent(event);
				_ellipse.processEvent(event);
			}
		}
	}

	void update()
	{
		_circle.update();
		_square.update();
		_polygons.update();
		_triangleRota.update();
		_ellipse.update();
	}

	void render()
	{
		_window.clear();
		_circle.draw(_window);
		_square.draw(_window);
		_polygons.draw(_window);
		_triangleRota.draw(_window);
		_ellipse.draw(_window);
		_window.display();
	}

public:
	Application() :
		_window(sf::VideoMode(1000, 1000), "Il y a plein d'objets LMAO JEEJ"),
		_circle(),
		_square(),
		_polygons(),
		_triangleRota(),
		_ellipse()
	{}

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
