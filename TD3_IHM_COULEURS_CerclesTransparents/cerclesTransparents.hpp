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
    sf::RenderWindow	_window;// Attribut graphique

public:
    cerclesTransparents():
            _mesCercles(),
            __vectCercles()
            {
                sf::Vector2u tailleWindow = _window.getSize();
                unsigned int hauteur = tailleWindow.y;
                unsigned int largeur = tailleWindow.x;
                float rayon = 400;

                for(int i = 0 ; i < 10; i++)
                {
                    _mesCercles.setOrigin(rayon, rayon);
                    _mesCercles.setPosition(400,400);
                    _mesCercles.setRadius(rayon);
                    _mesCercles.setFillColor(sf::Color(0.0, 0.0 + (25*i) , 255 - (25*i), 127));
                    rayon -= 25;
                    __vectCercles.push_back(_mesCercles);
                }

            cout << "Taille du vect --> " <<  __vectCercles.size() << endl;
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
