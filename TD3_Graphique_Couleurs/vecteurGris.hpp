//
// Created by xeloow on 30/03/16.
//

#ifndef TD3_GRAPHIQUE_COULEURS_VECTEURGRIS_HPP
#define TD3_GRAPHIQUE_COULEURS_VECTEURGRIS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class vecteurGris {
private:
    sf::RectangleShape              _rectGris;
    vector<sf::RectangleShape>      __vectGris;

public:
    vecteurGris():
            _rectGris(),
            __vectGris()
    {
        sf::Uint8 r = 255;
        sf::Uint8 g = 255;
        sf::Uint8 b = 255;
        _rectGris.setSize(sf::Vector2f(50,50));
        _rectGris.setPosition(100.0, 150.0);
        for(int tailleTab = 0; tailleTab < 10; tailleTab++)
        {
            _rectGris.setPosition(100.0  +(tailleTab * 50), 150.0);
            _rectGris.setFillColor(sf::Color(r - 25*tailleTab,g - 25*tailleTab,b - 25*tailleTab));
            __vectGris.push_back(_rectGris);
        }
    }

    ~vecteurGris() {}

    void processEvent(const sf::Event& event) {}

    void update() {}

    void draw(sf::RenderWindow& window)
    {
        for(int t = 0; t < __vectGris.size(); t++)
            window.draw(__vectGris[t]);
    }
};

#endif //TD3_GRAPHIQUE_COULEURS_VECTEURGRIS_HPP
