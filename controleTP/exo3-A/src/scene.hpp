#ifndef	SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Scene
{
private:
	sf::CircleShape							_mesCercles;
	sf::RectangleShape         	_square;
	vector<sf::CircleShape>		_circles;

public:
	Scene(const sf::Vector2u& v) :
		_square(),
		_circles(),
		_mesCercles()
	{

		sf::CircleShape  tmp;
		const int rayon = 100;

		tmp.setRadius(rayon);
		tmp.setFillColor(sf::Color::Black);
		_square.setSize(sf::Vector2f(2*rayon , 2*rayon));
		setOriginToCenter(_square);
		_square.setFillColor(sf::Color::Magenta);
		_square.setPosition(v.x, v.y);

		
		setOriginToCenter(tmp);

		for(int dx = -rayon ; dx <= rayon; dx += 2*rayon)
			for(int dy = -rayon; dy <= rayon; dy = dy + 2 *rayon )
			{
				tmp.setPosition(v.x+ dx, v.y+dy);
				_circles.push_back(tmp);
			}


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
		//window.clear();
		window.draw(_square);
		for(size_t i =0; i < _circles.size(); i++)
			window.draw(_circles[i]);
		//window.display();
	}
};

#endif
