//
// Created by xeloow on 25/05/16.
//

#ifndef TD4_SCENE_MATRICEBOX_HPP
#define TD4_SCENE_MATRICEBOX_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

class Scene;
class MatriceBox
{
private:
    sf::Vector2i        _mousePos;
    sf::RectangleShape  _shape;

    enum class Event {
        INSIDE,
        OUTSIDE
    };

    enum class State {
        ACTIVE,
        INACTIVE
    };

    //Scene&      _scene;
    Event       _event;
    State       _state;

public:
    MatriceBox()
    {
        _state = State::INACTIVE;
        _event = Event::OUTSIDE;
        _shape.setSize(sf::Vector2f(20,20));
        _shape.setFillColor(sf::Color::Black);
        _shape.setOutlineColor(sf::Color::White);
        _shape.setOutlineThickness(1);
    }
    ~MatriceBox() {}

    void init(const sf::Vector2f& position)
    {
        _shape.setPosition(position);
    }

    bool contains(const sf::Vector2f& mousePosition)
    {
        return _shape.getGlobalBounds().contains(mousePosition);
    }

    void handleEvent(const sf::Event::MouseMoveEvent& mouse)
    {
        if(contains(sf::Vector2f(mouse.x, mouse.y)))
            _event = Event::INSIDE;
        else
            _event = Event::OUTSIDE;
    }

    void update(sf::Time& delta)
    {
        switch (_event)
        {
            case Event::INSIDE:
                _state = State::ACTIVE;
                break;
            case Event::OUTSIDE;
                _state = State::INACTIVE;
                break;
            default:
                break;
        }
    }

    void draw(sf::RenderTarget& renderer)
    {
        switch (_state)
        {
            case State::ACTIVE;
                _shape.setFillColor(sf::Color::Green);
                break;
            case State::INACTIVE:
                _shape.setFillColor(sf::Color::Transparent);
                break;
            default:
                break;
        }
    }


};

#endif //TD4_SCENE_MATRICEBOX_HPP
