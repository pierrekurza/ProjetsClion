//
// Created by xeloow on 11/05/16.
//

#ifndef TD4_SCENE_BOX_HPP
#define TD4_SCENE_BOX_HPP

#include <SFML/Graphics.hpp>

class Box {
private:

    sf::RectangleShape                      _square;

    enum class Event {
        None,
        LeftClick,
        RightClick
    };

    enum class State {
        Green,
        Orange,
        Red
    };

    Event       _event;
    State       _state;

public:
    //Constructeur et destructeur
    Box()
    {
        _state = State::Green;
        _event = Event::None;
        _square.setSize(sf::Vector2f(80,80));
        _square.setFillColor(sf::Color::Black);
        _square.setOutlineColor(sf::Color::Yellow);
        _square.setOutlineThickness(1);
    }
    ~Box() {};

    //etat initial
    void init(const sf::Vector2f& position)
    {
        _event = Event::None;
        _state = State::Green;
        _square.setPosition(position);
    }

    //Gestion des collisions
    bool contains(const sf::Vector2f& mousePosition)
    {
        return _square.getGlobalBounds().contains(mousePosition);
    }

    //gestion des evenements
    void handleEvent(const sf::Event::MouseButtonEvent& evt)
    {
        switch (evt.button)
        {
            case sf::Mouse::Button::Left:
                _event = Event::LeftClick;
            break;

            case sf::Mouse::Button::Right:
                _event = Event::RightClick;
            break;

            default:
            break;
        }
    }

    void update(sf::Time& delta)
    {
        switch (_event)
        {
            case Event::LeftClick:
            switch (_state)
            {
                case State::Green:
                    _state = State::Orange;
                break;

                case State::Orange:
                    _state = State::Red;
                break;
            }
            break;

            case Event::RightClick:
                switch (_state)
                {
                    case State::Red:
                        _state = State::Orange;
                    break;

                    case State::Orange:
                        _state = State::Green;
                    break;
                }
            break;

            default:
            break;
        }
        _event = Event::None;
    }

    void draw(sf::RenderTarget& renderer)
    {
        switch (_state)
        {
            case State::Green:
                _square.setFillColor(sf::Color::Green);
            break;

            case State::Orange:
                _square.setFillColor(sf::Color(251,114,0));
            break;

            case State::Red:
                _square.setFillColor(sf::Color::Red);
            break;

            default:
                break;
        }
        renderer.draw(_square);
    }

};

#endif //TD4_SCENE_BOX_HPP
