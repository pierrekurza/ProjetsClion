#ifndef	SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Scene
{
private:
	sf::RectangleShape         	_square;
	sf::CircleShape							_mesCercles;
	vector<sf::CircleShape>		_circles;

public:
	Scene(const sf::Vector2u& v) :
		_square(),
		_circles()
	{
		sf::CircleShape  tmp;
		const int rayon = 100;

		tmp.setRadius(rayon);
		tmp.setFillColor(sf::Color::Transparent);
		tmp.setOutlineColor(sf::Color::Green);
		tmp.setOutlineThickness(2);
		setOriginToCenter(tmp);

		tmp.setPosition(v.x-rayon, v.y-rayon);
		_circles.push_back(tmp);

		tmp.setPosition(v.x-rayon, v.y+rayon);
		_circles.push_back(tmp);

		tmp.setPosition(v.x+rayon, v.y-rayon);
		_circles.push_back(tmp);

		tmp.setPosition(v.x+rayon, v.y+rayon);
		_circles.push_back(tmp);
	}


	~Scene()
	{}

	void setOriginToCenter(sf::Shape& shape)
	{
		sf::FloatRect boundingBox = shape.getLocalBounds();
		shape.setOrigin(boundingBox.left + boundingBox.width/2.0f, boundingBox.top  + boundingBox.height/2.0f);
	}

	void processEvent(const sf::Event& event)
	{
	}

	void update()
	{
	}

	void draw(sf::RenderWindow& window)
	{
		window.clear();
		window.draw(_square);
		for(int i =0; i < _circles.size(); i++)
			window.draw(_circles[i]);
		window.display();
	}
};

#endif
