//-----------------------------------------------------------------------------
//  TD IHM
//  application.hpp
//-----------------------------------------------------------------------------

#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
//  Observateur d'événements
//-----------------------------------------------------------------------------
class Scene;


class MusicPlayer
{
public:
	enum Event
	{
		NONE,
		MOUSE_ENTERED,
		MOUSE_LEFT,
	};

private:

	// Multimedia
	sf::Music			_music;

	// Logique
	Event				_event;
	Scene&				_scene;

public:
	// Constructeur & destructeur
	MusicPlayer(Scene& scene);
	~MusicPlayer(){};

	// Etat initial
	void init();

	// Gestion des événements
	void handleEvent(const sf::Event& evt);


	// Mise à jour
	void update(sf::Time& delta);


	// Rendu
	void draw(sf::RenderTarget& renderer);
};


//-----------------------------------------------------------------------------
//  Scene
//-----------------------------------------------------------------------------

class Scene
{
private:
	// Graphique
	sf::View				_sceneView;
	sf::RenderWindow&		_window;

	// Logique
	MusicPlayer				_musicPlayer;


public:
	// Constructeur & destructeur
	Scene(sf::RenderWindow& window);
	~Scene(){};

	// Gestion des événements
	void handleEvent(const sf::Event& evt);

	// Mise à jour
	void update(sf::Time& delta);

	// Rendu
	void draw();
};

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
	Application();
	void run();

protected:
	// Boucle événementielle
	void processEvents();
	void update(sf::Time& delta);
	void render();
};
#endif