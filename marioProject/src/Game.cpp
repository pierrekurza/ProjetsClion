#ifndef PROJECT_GAME_CPP
#define PROJECT_GAME_CPP

#include "Game.hpp"

Game::Game() : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario Game") {
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
    GameSound gameSound;

}

void Game::initialize() {
    // On commence au premier niveau
    tilemap.setLevel(1);
    tilemap.changeLevel();

    // Personnage à 5 vies
    character.initialize(tilemap);
    character.setCoins(0);
    character.setLives(5);

    // Son
    gameSound.playBackgroundMusic();
}

void Game::update() {
    // Update des infos du personnage
    // Si le personnage est mort on retire les monstres qui eexistaient déjà
    if(character.updateCharacter(input, tilemap, gameSound) > 0) {
        tilemap.setGoombaNumber(0);
    }
    // Update des goomba
    for(int i = 0; i < tilemap.getGoombaNumber(); i++) {
        if(goomba[i].updateGoomba(tilemap, character, gameSound) == 1) {
            // Cas où le goomba doit mourir
            // On copie à sa place le dernier monstre avant d'en retirer un
            goomba[i].copy(goomba[tilemap.getGoombaNumber() - 1]);
            tilemap.setGoombaNumber(tilemap.getGoombaNumber() - 1);
        }
    }
}

void Game::render() {
    // Création des graphismes
    window.clear();

    // Background
    background.buildBackground(window);

    // Deuxième couche et première couche du level
    tilemap.drawLevelLayer(2, window, goomba);
    tilemap.drawLevelLayer(1, window, goomba);

    // Personnage
    character.drawCharacter(tilemap, window);

    // HUD
    hud.drawHud(character, window, tilemap);

    for (int i = 0; i < tilemap.getGoombaNumber(); i++)
        goomba[i].drawGoomba(tilemap, window);

    window.display();

}

void Game::processEvents() {
    // Gestion des inputs
    input.inputManagement(window);
}

void Game::run() {
    // On initialise les informations
    initialize();
    // Boucle principale du jeu, ne se termine pas tant que la fenêtre est ouverte
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

Game::~Game() {}


#endif