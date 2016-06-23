//
// Created by xeloow on 16/03/16.
//

#ifndef TD3_GRAPHIQUE_POLYGONS_HPP
#define TD3_GRAPHIQUE_POLYGONS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>


using namespace std;

class Polygons{
private:
    sf::CircleShape             _polygons;
    vector<sf::CircleShape>     __polygonsVect;
public:
    Polygons():
            _polygons(),
            __polygonsVect()
    {
        _polygons.setRadius(50);
        _polygons.setFillColor(sf::Color::Red);

            for(int i = 3; i < 9;i++)
            {
                _polygons.setPointCount(i);
                _polygons.setPosition(100.0 + (i*99) , 200.0);
                __polygonsVect.push_back(_polygons);
            }

    }

        ~Polygons()
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
            for(int i = 0; i < __polygonsVect.size(); i++)
                window.draw(__polygonsVect[i]);
        }

};

#endif //TD3_GRAPHIQUE_POLYGONS_HPP
