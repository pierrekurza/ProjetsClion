//-----------------------------------------------------------------------------
//  TD IHM
//  scene.hpp
//-----------------------------------------------------------------------------

#ifndef SCENE_HPP
#define SCENE_HPP

//#include "observer.hpp"
//#include "ball.hpp"
#include "box.hpp"
#include <vector>

using namespace std;

//-----------------------------------------------------------------------------
//  Scene (gestionnaire des objets graphiques de l'application)
//-----------------------------------------------------------------------------

class Scene
{
private:
	// Graphique
	sf::View				_sceneView;
	sf::RenderWindow&		_window;

	// Logique
	//Ball					_balle;
	Box						_box;
	vector<Box>				_boxes;

public:
	// Constructeur & destructeur
	Scene(sf::RenderWindow& window):
	_sceneView(window.getDefaultView()),
	_window(window)
	{
		Box tmp;
		const int dimensionBox = 80;
		const int nbBox = 10;
		sf::Vector2u centreFenetre;
		centreFenetre.y = _window.getSize().y /2;
		centreFenetre.x = _window.getSize().x /2;
		for (int i = 0; i < nbBox; i++) {
			tmp.init(sf::Vector2f(centreFenetre.x - nbBox * dimensionBox/2+i * dimensionBox, centreFenetre.y - dimensionBox /2));
			_boxes.push_back(tmp);
		}
	}
	~Scene()
	{
	}

	// Gestion des événements
	void handleEvent(const sf::Event& evt)
	{
		size_t i = 0;
		bool trouve = false;
		if(evt.type == sf::Event::MouseButtonPressed)
		{
			while( i < _boxes.size() && !trouve)
			{
				if(_boxes[i].contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
					trouve = true;
				else
					i++;

				if(trouve)
					_boxes[i].handleEvent(evt.mouseButton);
			}
		}
	}

	// Mise à jour
	void update(sf::Time& delta)
	{
		for(size_t i = 0; i < _boxes.size(); i++)
			_boxes[i].update(delta);
	}

	// Rendu
	void draw()
	{
		for(size_t i = 0; i < _boxes.size(); i++)
			_boxes[i].draw(_window);
	}
};

#endif
