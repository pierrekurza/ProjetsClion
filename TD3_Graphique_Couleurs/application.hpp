#ifndef	APPLICATION_HPP
#define APPLICATION_HPP

#include "vecteurGris.hpp"
#include "matriceRougeBleu.hpp"

class Application
{
// Attributs
private:
	sf::RenderWindow	_window;// Attribut graphique
	vecteurGris			_monVect;
	matriceRougeBleu 	_maMatriceRougeBleu;

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
				_monVect.processEvent(event);
				_maMatriceRougeBleu.processEvent(event);
			}
		}
	}

	void update()
	{
		_monVect.update();
		_maMatriceRougeBleu.update();
	}

	void render()
	{
		_window.clear();
		_monVect.draw(_window);
		_maMatriceRougeBleu.draw(_window);
		_window.display();
	}

public:
	Application() :
		_window(sf::VideoMode(1400, 1000), "Il y a plein d'objets LMAO JEEJ"),
		_monVect(),
		_maMatriceRougeBleu()
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
