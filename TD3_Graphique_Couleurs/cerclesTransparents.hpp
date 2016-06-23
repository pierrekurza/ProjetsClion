//
// Created by xeloow on 20/04/16.
//

#ifndef TD3_GRAPHIQUE_COULEURS_CERCLESTRANSPARENTS_HPP
#define TD3_GRAPHIQUE_COULEURS_CERCLESTRANSPARENTS_HPP


#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class cerclesTransparents {
private:
    sf::CircleShape                 _mesCercles;
    vector<sf::CircleShape>         __vectCercles;

public:
    cerclesTransparents():
            _mesCercles(),
            __vectCercles()
            {
                for(int i = 0 ; i < )
                _mesCercles.setRadius(200)
            }


    ~cerclesTransparents() { }

    void processEvent(const sf::Event& event) {}

    void update() {}

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < __vectCercles.size(); i++)
            window.draw(__vectCercles[i]);
    }
};

#endif //TD3_GRAPHIQUE_COULEURS_CERCLESTRANSPARENTS_HPP
