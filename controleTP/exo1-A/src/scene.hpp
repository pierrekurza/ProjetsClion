#ifndef	SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Scene
{
private:
	sf::RectangleShape		_horizontal;	// Attribut graphique
	sf::RectangleShape		_vertical;		// Attribut graphique

public:
	Scene(const sf::Vector2u& v) :
		_horizontal(),
		_vertical()
	{
		_horizontal.setSize(sf::Vector2f(300,60));
		_vertical.setSize(sf::Vector2f(300,60));
		setOriginToCenter(_vertical);
		setOriginToCenter(_horizontal);
		_horizontal.setPosition(v.x, v.y);
		_horizontal.setFillColor(sf::Color::Red);
		_vertical.setPosition(v.x, v.y);
		_vertical.setFillColor(sf::Color::Red);
		_vertical.rotate(90);
	}

	~Scene()
	{}

	void processEvent(const sf::Event& event)
	{
	}

	void update()
	{
	}

	void draw(sf::RenderWindow& window)
	{
			window.clear();
			window.draw(_horizontal);
			window.draw(_vertical);
			window.display();
	}

	void setOriginToCenter(sf::Shape& shape)
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		shape.setOrigin(boundingBox.left + boundingBox.width/2.0f, boundingBox.top  + boundingBox.height/2.0f);
	}
};

#endif
