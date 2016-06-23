//
// Created by xeloow on 16/03/16.
//

#ifndef TD3_GRAPHIQUE_SQUARE_H
#define TD3_GRAPHIQUE_SQUARE_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Square {
private:
    sf::CircleShape		_carreVert;

public:
    Square():
            _carreVert()
    {
        _carreVert.setRadius(50);
        _carreVert.setPointCount(4);
        _carreVert.setFillColor(sf::Color::Green);
        _carreVert.move(100.0,0.0);
    }

    ~Square()
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
        window.draw(_carreVert);
    }
};


#endif //TD3_GRAPHIQUE_SQUARE_H
