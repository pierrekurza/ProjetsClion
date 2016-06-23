//
// Created by xeloow on 27/03/16.
//

#ifndef TD3_GRAPHIQUE_ELLIPSE_HPP
#define TD3_GRAPHIQUE_ELLIPSE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Ellipse {
private:
    sf::CircleShape             _ellipse;
    vector<sf::CircleShape>     __vectEllipse;

public:
    Ellipse():
            _ellipse(),
            __vectEllipse()
    {
        _ellipse.setRadius(50.0);
        _ellipse.setFillColor(sf::Color(140,045,214));
        for (int i = 0; i < 7; i++) {
            _ellipse.setPosition(140.0 + (i*100), 350.0);
            _ellipse.scale(0.5f, 1.5f);
            __vectEllipse.push_back(_ellipse);
        }
    }

    ~Ellipse() {}

    void processEvent(const sf::Event& event) {}

    void update() {}

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < __vectEllipse.size(); i++) {
            window.draw(__vectEllipse[i]);
        }
    }

};

#endif //TD3_GRAPHIQUE_ELLIPSE_HPP
