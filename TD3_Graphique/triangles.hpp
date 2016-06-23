//
// Created by xeloow on 23/03/16.
//

#ifndef TD3_GRAPHIQUE_TRIANGLES_HPP
#define TD3_GRAPHIQUE_TRIANGLES_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Triangle {
private:
    sf::CircleShape             _triangleRotation;
    vector<sf::CircleShape>     __vectTriangles;

public:
Triangle():
    _triangleRotation(),
    __vectTriangles()
    {
        _triangleRotation.setRadius(50);
        _triangleRotation.setPointCount(3);
        _triangleRotation.setFillColor(sf::Color::Yellow);
        for(int i = 0; i <= 6; i++)
        {
            _triangleRotation.rotate(15);
            _triangleRotation.setPosition(210 + (i*100.0), 300.0);
            __vectTriangles.push_back(_triangleRotation);
        }
    }

    ~Triangle()
    {
    }

    void processEvent(const sf::Event& event)
    {
    }

    void update()
    {
    }

    void draw(sf::RenderWindow& window)
    {
        for(int lol = 0; lol < __vectTriangles.size(); lol++)
            window.draw(__vectTriangles[lol]);
    }
};

#endif //TD3_GRAPHIQUE_TRIANGLES_HPP
