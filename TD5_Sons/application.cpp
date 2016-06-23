//-----------------------------------------------------------------------------
//  TD IHM
//  application.cpp
//-----------------------------------------------------------------------------

#include "application.hpp"
#include "MusicRecord.hpp"

//-----------------------------------------------------------------------------
//  MusicPlayer
//-----------------------------------------------------------------------------

MusicPlayer::MusicPlayer(Scene& scene) :
_scene(scene)
{
	assert(_music.openFromFile("sound/nyanCat.ogg"));
	_music.setVolume(100);
	_music.setLoop(true);
	_music.play();
}

void MusicPlayer::draw(sf::RenderTarget& renderer)
{

}

void MusicPlayer::handleEvent(const sf::Event& evt)
{
	if(evt.type == sf::Event::MouseLeft && _music.Playing)
		_music.pause();
	else if(evt.type == sf::Event::MouseEntered && _music.Paused)
		_music.play();
}

void MusicPlayer::update(sf::Time& tau)
{
}

//-----------------------------------------------------------------------------
//  Scene
//-----------------------------------------------------------------------------

Scene::Scene(sf::RenderWindow& window) :
_sceneView(window.getDefaultView()),
_window(window),
_musicPlayer(*this)
{
}

void Scene::draw()
{
	_musicPlayer.draw(_window);
}

void Scene::handleEvent(const sf::Event& evt)
{
	_musicPlayer.handleEvent(evt);
}

void Scene::update(sf::Time& tau)
{
	_musicPlayer.update(tau);
}

//-----------------------------------------------------------------------------
//  Application
//-----------------------------------------------------------------------------

Application::Application() :
_scene(_window),
_window(sf::VideoMode(1000, 1000), "Sons I")
{
}

void Application::run()
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


void Application::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		_scene.handleEvent(event);

		if (event.type == sf::Event::Closed)
			_window.close();
	}

}

void Application::update(sf::Time& tau)
{
	_scene.update(tau);
}

void Application::render()
{
	_window.clear();
	_scene.draw();
	_window.display();
}

int main()
{
	Application app;
	app.run();
	return 0;
}