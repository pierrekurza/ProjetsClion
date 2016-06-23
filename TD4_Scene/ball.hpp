//
// Created by xeloow on 27/04/16.
//

#ifndef TD4_SCENE_BALL_HPP
#define TD4_SCENE_BALL_HPP

#include <SFML/Graphics.hpp>
#include "scene.hpp"
//#include "scene.hpp"
using namespace std;

class Ball {
private:
    enum class State
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        MOUSE_MOVED,
        CENTER
    };

    sf::CircleShape         _shape;
    State                   _state;
    sf::Vector2f            _position, _vitesse;
    sf::Event               _event;
    sf::Vector2f            _positionSouris;
    //sf::Vector2f            _centre; //coordonnées du centre de la fenêtre
    sf::Vector2f            _tailleFenetre;
    const int rayon = 150;

public:
    Ball(sf::Vector2f tailleWindows)
    {
        _tailleFenetre = tailleWindows;
        _shape.setFillColor(sf::Color::Green);
        _shape.setRadius(rayon);
        _shape.setOrigin(rayon, rayon);
    }

    ~Ball() {};

    void init()
    {
        _state = State::NONE;
        _position = _tailleFenetre/(float)2;
        _positionSouris = _tailleFenetre/(float)2;
        _vitesse = sf::Vector2f(0,0); //on crée une variable tmp construite a partir des coordonées (0,0)

    }

    void handleEvent(const sf::Event& keyOrMouse)
    {
        switch (keyOrMouse.type)
        {
            case sf::Event::MouseLeft:
                _state = State::CENTER;
                break;
            case sf::Event::MouseMoved:
                _positionSouris = sf::Vector2f(keyOrMouse.mouseMove.x, keyOrMouse.mouseMove.y);
                break;
            case sf::Event::KeyPressed:
                switch (keyOrMouse.key.code)
                {
                    case sf::Keyboard::Z:
                        _state = State::UP;
                        break;
                    case sf::Keyboard::S:
                        _state = State::DOWN;
                        break;
                    case sf::Keyboard::Q:
                        _state = State::LEFT;
                        break;
                    case sf::Keyboard::D:
                        _state = State::RIGHT;
                        break;
                }
        }
    }

    void update(sf::Time& temps)
    {

            const float vitesse = 1.66; //190px / sec
            _vitesse = vitesse * (_positionSouris - _position);
            _position += _vitesse * temps.asSeconds();

            if(_position.x < rayon)
                _position.x = rayon;

            if(_position.y < rayon)
                _position.y = rayon;

            if(_position.x > _tailleFenetre.x - rayon)
                _position.x = _tailleFenetre.x - rayon;

            if(_position.y > _tailleFenetre.y - rayon)
                _position.y = _tailleFenetre.y - rayon;
            _shape.setPosition(_position);

    }

    void draw(sf::RenderTarget& renderer)
    {
        renderer.draw(_shape);
    }
};

#endif //TD4_SCENE_BALL_HPP
