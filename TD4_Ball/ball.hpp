//
// Created by xeloow on 27/04/16.
//

#ifndef TD4_SCENE_BALL_HPP
#define TD4_SCENE_BALL_HPP

#include <SFML/Graphics.hpp>
#include "scene.hpp"
using namespace std;

class Ball {
private:
    sf::CircleShape         _shape;

    enum class Event
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    Event           _evenement;
    sf::Vector2f    _position;
    Scene&          _scene;

public:
    Ball(Scene& scene);
    ~Ball() {};

    void init()
    {

    }

    void handleEvent(const sf::Event& key)
    {
        switch (key.)
        {

        }
    }

    void update(sf::Time& temps)
    {

    }

    void draw(sf::RenderTarget& renderer)
    {

    }
};

#endif //TD4_SCENE_BALL_HPP
