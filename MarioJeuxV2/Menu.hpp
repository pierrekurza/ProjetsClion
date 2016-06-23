#ifndef PROJECT_MENU_HPP
#define PROJECT_MENU_HPP

#include <SFML/Graphics.hpp>
#include "KeyboardInput.hpp"
#include "Game.hpp"
#include <iostream>

using namespace sf;

class Menu {
private:
    KeyboardInput input;
    Texture choice1Tex;
    Sprite choice1;
    Texture choice2Tex;
    Sprite choice2;
public:
    Menu() {

        // Chargement du menu
        if (!choice1Tex.loadFromFile("graphics/choice1.png"))
            // Erreur
            std::cout << "Problème lors du chargement du menu (1)" << std::endl;
        else
            choice1.setTexture(choice1Tex);

        if (!choice2Tex.loadFromFile("graphics/choice2.png"))
            // Erreur
            std::cout << "Problème lors du chargement du menu (2)" << std::endl;
        else
            choice2.setTexture(choice2Tex);

        KeyboardInput input;
    }
    
};

#endif //PROJECT_MENU_HPP
