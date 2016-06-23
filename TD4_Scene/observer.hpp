//-----------------------------------------------------------------------------
//  TD IHM
//  observer.hpp
//-----------------------------------------------------------------------------

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

//-----------------------------------------------------------------------------
//  Observateur d'événements
//-----------------------------------------------------------------------------

class Observer
{
private:
	// Graphique
	sf::Font				_font;
	sf::Text				_text;
	sf::RectangleShape		_border;

	// Logique
	sf::String		_label;

	enum class Event {
		NONE,
		GAINED_FOCUS,
		LOST_FOCUS,
		MOUSE_LEFT,
		MOUSE_MOVED,
		TOUCHE_A
	};

	Event state;

	int _mousePosX;
	int _mousePosY;
public:
	// Constructeur & destructeur
	Observer(const sf::Vector2f& center)
	{
		//sf::Font font;
		assert(_font.loadFromFile("vera.ttf") == true);
		_text.setColor(sf::Color::White);
		_text.setFont(_font);
		_text.setCharacterSize(50);
		_text.setStyle(sf::Text::Italic);
		_border.setPosition(center);
		_border.setOutlineColor(sf::Color::White);
		_border.setOutlineThickness(2.0);
		_border.setFillColor(sf::Color::Transparent);
	}

	~Observer()
	{
	}

	// Etat initial
	void init()
	{
		state=Event::NONE;
	}

	// Gestion des événements
	void handleEvent(const sf::Event& evt)
	{
		_mousePosX = evt.mouseMove.x;
		_mousePosY = evt.mouseMove.y;
		switch (evt.type)
		{
			case sf::Event::KeyPressed:
				if(evt.key.code == sf::Keyboard::Key::A)
					state = Event::TOUCHE_A;
				break;
			case sf::Event::LostFocus:
				state=Event::LOST_FOCUS;
				break;
			case sf::Event::GainedFocus:
				state=Event::GAINED_FOCUS;
				break;
			case sf::Event::MouseLeft:
				state=Event::MOUSE_LEFT;
				break;
			case sf::Event::MouseMoved:
				state=Event::MOUSE_MOVED;
			default:
				break;
		}
	}

	// Mise à jour
	void update(sf::Time& delta)
	{
		ostringstream conversion;
		switch (state) {
			case Event::TOUCHE_A:
				_label = L"Touche A préssée";
				break;
			case Event::NONE:
				_label = L"Aucun évenement reconnu";
				break;
			case Event::LOST_FOCUS:
				_label = L"La fenêtre est passée a l'arriere plan";
				break;
			case Event::GAINED_FOCUS:
				_label = L"La fenêtre est passée au premier plan";
				break;
			case Event::MOUSE_LEFT:
				_label = L"La souris est sortie de la fenetre";
				break;
			case Event::MOUSE_MOVED:
				conversion << "X : " << _mousePosX << " || " << "Y : " << _mousePosY << endl;
				_label=conversion.str();
				break;
			default:
				break;
		}
	}

	// Rendu
	void draw(sf::RenderTarget& renderer, const sf::Vector2f& center)
	{

		sf::Vector2f position(center);
		_text.setString(_label);
		position.x -= _text.getLocalBounds().width / 2.0f;
		position.y -= _text.getLocalBounds().height / 2.0f;
		_border.setSize(sf::Vector2f(_text.getLocalBounds().width + 10,
									 _text.getLocalBounds().height + 10));
		_border.setPosition(position);

		_text.setPosition(position);
		renderer.draw(_text);
		renderer.draw(_border);
	}
};

#endif
