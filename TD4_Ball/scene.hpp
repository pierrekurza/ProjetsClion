//-----------------------------------------------------------------------------
//  TD IHM
//  scene.hpp
//-----------------------------------------------------------------------------

#ifndef SCENE_HPP
#define SCENE_HPP

#include "observer.hpp"

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
	Observer				_observer;


public:
	// Constructeur & destructeur
	Scene(sf::RenderWindow& window):
	_sceneView(window.getDefaultView()),
	_window(window),
	_observer(_sceneView.getCenter())
	{
		_observer.init();
	}

	~Scene()
	{
	}

	// Gestion des événements
	void handleEvent(const sf::Event& evt)
	{
		_observer.handleEvent(evt);
	}

	// Mise à jour
	void update(sf::Time& delta)
	{
		_observer.update(delta);
	}

	// Rendu
	void draw()
	{
		_observer.draw(_window, _sceneView.getCenter());
	}
};

#endif
