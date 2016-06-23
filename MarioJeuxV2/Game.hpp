#ifndef PROJECT_GAME_HPP
#define PROJECT_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>

#include "KeyboardInput.hpp"
#include "Background.hpp"
#include "Tilemap.hpp"
#include "Character.hpp"
#include "HUD.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

using namespace sf;


class Game {
private:
    RenderWindow    window;
    KeyboardInput   input;
    Background      background;
    Tilemap         tilemap;
    Character       character;
    HUD             hud;
    Sound           _sound;
sf::Music           _musicBackground;
public:
    Game() :
        window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario Game") {
        // Création de la fenêtre du jeu
        // Limite 60FPS et synchro verticale
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(true);

        // On instancie les classes
        // Input sert à gérer les input du clavier
        KeyboardInput input;

        // Définition de la map du jeu
        Background background;
        Tilemap tilemap;

        // Le personnage
        Character character;

        // Le HUD
        HUD hud;

        //Le Son
        Sound sound;
        Music musique;
    }

    void playBackgroundMusic()
    {
        if(!_musicBackground.openFromFile("soundsV2/bgMusic.wav"))
            cerr << L"Music Background n'a pas pu être chargé" << endl;
        else
        {
            _musicBackground.setVolume(100);
            _musicBackground.setLoop(true);
            _musicBackground.play();
        }
    }

    void initialize() {
        // On commence au premier niveau
        tilemap.setLevel(1);
        tilemap.changeLevel();

        // Personnage à 5 vies
        character.initialize(tilemap);
        character.setCoins(0);
        character.setLives(5);
    }

    void update() {
        // Update des infos du personnage
        character.updateCharacter(input, tilemap);
    }

    void render() {
        // Création des graphismes
        window.clear();

        // Background
        background.buildBackground(window);

        // Deuxième couche et première couche du level
        tilemap.drawLevelLayer(2, window);
        tilemap.drawLevelLayer(1, window);

        // Personnage
        character.drawCharacter(tilemap, window);

        // HUD
        hud.drawHud(character, window, tilemap);


        window.display();

    }

    void processEvents() {
        // Gestion des inputs
        input.inputManagement(window);
    }

    void run() {
        // On initialise les informations
        initialize();
        // Boucle principale du jeu, ne se termine pas tant que la fenêtre est ouverte
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    ~Game() { }
};

#endif //PROJECT_GAME_HPP
