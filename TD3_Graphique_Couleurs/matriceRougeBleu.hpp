//
// Created by xeloow on 20/04/16.
//

#ifndef TD3_GRAPHIQUE_COULEURS_MATRICEROUGEBLEU_HPP
#define TD3_GRAPHIQUE_COULEURS_MATRICEROUGEBLEU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class matriceRougeBleu {
private:
    sf::RectangleShape              _matriceRouBleu;
    vector<sf::RectangleShape>      __vectMatriceRougeBleu;

public:
    int reduction = 25;
    matriceRougeBleu():
            _matriceRouBleu(),
            __vectMatriceRougeBleu()
    {
        _matriceRouBleu.setSize(sf::Vector2f(50,50));
        _matriceRouBleu.setPosition(200.0, 300.0);
        for(int ligne = 0 ; ligne < 10; ligne++)
        {
            for(int colonne = 0 ; colonne < 10; colonne++)
            {
                _matriceRouBleu.setFillColor(sf::Color(255 - (reduction* ligne), 0.0 , 0 + (reduction * colonne)));
                _matriceRouBleu.setPosition(50.0 + (ligne * 50), 250 + (colonne * 50));
                __vectMatriceRougeBleu.push_back(_matriceRouBleu);
            }
            __vectMatriceRougeBleu.push_back(_matriceRouBleu);
        }

        cout << "Taille du vect --> " << __vectMatriceRougeBleu.size() << endl;
    }
        ~matriceRougeBleu() { }

        void processEvent(const sf::Event& event) {}

        void update() {}

        void draw(sf::RenderWindow& window) {
            for (int i = 0; i < __vectMatriceRougeBleu.size(); i++)
                window.draw(__vectMatriceRougeBleu[i]);
        }

};

#endif //TD3_GRAPHIQUE_COULEURS_MATRICEROUGEBLEU_HPP
