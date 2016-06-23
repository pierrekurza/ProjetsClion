#ifndef	CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

// Objet inerte circulaire
class Circle
{
// Attributs
private:
	sf::CircleShape		_shape;	// Attribut graphique
	sf::CircleShape		_origin;
	sf::CircleShape 	_figureUne;


// Méthodes
public:
	Circle() :
		_shape(),
		_origin(),
		_figureUne()
	{
		_shape.setRadius(50.0);
		_shape.setPosition(20.0, 20.0);
		_shape.setFillColor(sf::Color::Blue);
		//_shape.setPointCount(4);

		_origin.setRadius(1.0);
		_origin.setPosition(70.0, 70.0);
		_origin.setFillColor(sf::Color::White);

		_figureUne.setRadius(60.0);
		sf::Vector2f maPosition = _shape.getPosition();
		_figureUne.setPosition(maPosition);
		_figureUne.move(200.0, 0.0);
		_figureUne.setFillColor(sf::Color::Red);




	}

	~Circle()
	{}

	void processEvent(const sf::Event& event)
	{
	}

	void update()
	{
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(_shape);
		window.draw(_origin);
		window.draw(_figureUne);
	}
};

#endif
