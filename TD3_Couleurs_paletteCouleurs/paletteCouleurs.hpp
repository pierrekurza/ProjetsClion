//
// Created by xeloow on 20/04/16.
//

#ifndef TD3_COULEURS_PALETTECOULEURS_PALETTECOULEURS_HPP
#define TD3_COULEURS_PALETTECOULEURS_PALETTECOULEURS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class paletteCouleurs {
private:
    sf::VertexArray     _carrePaletteCouleur;

public:
    paletteCouleurs():
        _carrePaletteCouleur(sf::Quads, 4)
            {
                _carrePaletteCouleur[0].position = sf::Vector2f(100, 100);
                _carrePaletteCouleur[1].position = sf::Vector2f(400, 100);
                _carrePaletteCouleur[2].position = sf::Vector2f(400, 300);
                _carrePaletteCouleur[3].position = sf::Vector2f(100, 300);

                _carrePaletteCouleur[0].color = sf::Color::Red;
                _carrePaletteCouleur[1].color = sf::Color::Yellow;
                _carrePaletteCouleur[2].color = sf::Color::Blue;
                _carrePaletteCouleur[3].color = sf::Color::Green;

            }


    ~paletteCouleurs() { }

    void processEvent(const sf::Event& event) {}

    void update() {}

    void draw(sf::RenderWindow& window) {
        window.draw(_carrePaletteCouleur);
    }
};


#endif //TD3_COULEURS_PALETTECOULEURS_PALETTECOULEURS_HPP
