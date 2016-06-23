#include "main.hpp"

using namespace std;

int main()
{
    // Création de la fenêtre du jeu
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario Game");

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
    character.initialize(tilemap, true);
    character.setLives(5);
    character.setCoins(0);

    // On commence au premier niveau
    tilemap.setLevel(1);
    tilemap.changeLevel();

    // Boucle principale du jeu, ne se termine pas tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Gestion des inputs
        input.inputManagement(window);

        // Update des infos du personnage
        character.updateCharacter(input, tilemap);

        // Création des graphismes
        window.clear();

        // Background
        background.buildBackground(window);

        // Deuxième couche et première couche du level
        tilemap.drawLevelLayer(2, window);
        tilemap.drawLevelLayer(1, window);

        // Personnage

        character.drawCharacter(tilemap, window);

        window.display();
    }

    return 0;
}