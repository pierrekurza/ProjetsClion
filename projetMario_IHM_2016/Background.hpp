#ifndef PROJECT_BACKGROUND_HPP
#define PROJECT_BACKGROUND_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/basic_string.h>

using namespace sf;

class Background {
private:

    // Background de la map
    Texture backgroundTex;
    Sprite background;

public:

    // Constructeur de map
    Background() {
        // Background
        if(!backgroundTex.loadFromFile("graphics/background.png"))
            // Problème
            cout << "Problème lors du chargement du background." << endl;
        else
            background.setTexture(backgroundTex);
    }

    // Méthode pour construire le background
    void buildBackground(RenderWindow& window) {
        window.draw(background);
    }

};

#endif //PROJECT_BACKGROUND_HPP
