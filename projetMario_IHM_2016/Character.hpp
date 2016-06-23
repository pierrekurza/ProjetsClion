#ifndef PROJECT_CHARACTER_HPP
#define PROJECT_CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"
#include "KeyboardInput.hpp"
#include <iostream>

// Pour les animations
#define FRAME_TIMER 5

// Taille du sprite de Mario
#define CHARACTER_WIDTH 32
#define CHARACTER_HEIGHT 55

// Vitesse
#define CHARACTER_SPEED 4

// Les états + la direction
#define IDLE 0
#define WALK 1
#define JUMP 2
#define CLIMB 3

#define RIGHT 1
#define LEFT 2

#define JUMP_HEIGHT 10

// Limite du scrolling
#define LIMITE_X 300
#define LIMITE_W 100

#define CAMERA_SPEED 4

using namespace sf;

class Tilemap;
class KeyboardInput;

class Character {

private:

    Texture characterTex;
    Sprite character;

    // Les variables joueur
    int hp;
    int lives;
    int coins; // 100 pièces : 1 vie

    // Coordonnées de sprite
    int x, y;
    // Largeur, hauteur sprite
    int w, h;

    // Pour les animations
    int frameNumber, frameMax, frameTimer;

    // État d'un sprite, direction dans laquelle regarde Mario
    int state, direction;

    // Pour la gestion des collisions
    bool onGround;

    // Déplacement temporaire avant la détection des collisions
    float dirX, dirY;


public:
    Character() {
        // Chargement spritesheet
        if(!characterTex.loadFromFile("graphics/mario_spritesheet.png"))
            std::cout << "Erreur lors du chargement du spritesheet du personnage" << std::endl;
        else
            character.setTexture(characterTex);

        // Initialisation des variables joueur
        dirX = 0;
        dirY = 0;
        hp = 1;
        x = 0;
        y = 0;
        h = 0;
        w = 0;
        frameMax = 0;
        frameNumber = 0;
        frameTimer = 0;
        state = 0;
        direction = 0;
        onGround = false;
        dirX = 0;
        dirY = 0;
    }

    // Accesseurs
    int getX() const { return x; }
    int getY() const { return y; }
    int getH() const { return h; }
    int getW() const { return w; }
    float getDirX() const { return dirX; }
    float getDirY() const { return dirY; }
    int getOnGround() const { return onGround; }
    int getHp() const { return hp; }
    int getLives() const { return lives; }
    int getCoins() const { return coins; }
    int getDirection() const { return direction; }

    // Setteurs
    void setX(int v) { x = v; }
    void setY(int v) { y = v; }
    void setH(int v) { h = v; }
    void setW(int v) { w = v; }
    void setDirX(float v) { dirX = v; }
    void setDirY(float v) { dirY = v; }
    void setOnGround(bool v) { onGround = v; }
    void setLives(int v) { lives = v; }
    void setCoins(int v) { coins = v; }

    // Fonctions
    void initialize(Tilemap &map, bool newLevel) {
        // 1 PV
        hp = 1;

        // Direction et état
        direction = RIGHT;
        state = IDLE;

        // Frame où commencer
        frameNumber = 0;

        // Timer entre frames
        frameTimer = FRAME_TIMER;

        // Frames max pour l'animation IDLE (1)
        frameMax = 1;

        // Coordonnées de départ du personnage
        x = map.getCharacterBeginX();
        y = map.getCharacterBeginY();

        map.setMapStartX(0);
        map.setMapStartY(0);

        w = CHARACTER_WIDTH;
        h = CHARACTER_HEIGHT;

        onGround = false;

    }


    void drawCharacter(Tilemap &map, RenderWindow &window) {
        // Timer
        // Si le timer arrive à zéro
        if (frameTimer <= 0)
        {
            // On le reset
            frameTimer = FRAME_TIMER;

            // On augmente la variable qui compte les frames
            frameNumber++;

            // Si on dépasse la frame max, il faut revenir à la première :
            if (frameNumber >= frameMax)
                frameNumber = 0;
        }
        // Sinon, on réduit le timer
        else
            frameTimer--;

        character.setPosition(Vector2f(x - map.getMapStartX(), y - map.getMapStartY()));
        if(direction == LEFT) {
            character.setTextureRect(IntRect((frameNumber + 1) * w, state * h, -w, h));
            window.draw(character);
        }
        else {
            character.setTextureRect(IntRect(frameNumber * w, state * h, w, h));
            window.draw(character);
        }


    }

    void horizontalScrolling(Tilemap &map) {
        // On va créer une "boîte" autour du personnage, si on la dépasse, on recentre la caméra

        int xCharCoor = x + w / 2;
        int xMinLim = map.getMapStartX() + LIMITE_X;
        int xMaxLim = xMinLim + LIMITE_W;

        // Si on dépasse à gauche, on recule la caméra
        if (xCharCoor < xMinLim) {
            map.setMapStartX(map.getMapStartX() - CAMERA_SPEED);
        }
            // Si on dépasse à droite, on avance la caméra
        if(xCharCoor > xMaxLim) {
            map.setMapStartX(map.getMapStartX() + CAMERA_SPEED);
        }
        // Si on arrive au bout à gauche, on stop le scrolling
        if(map.getMapStartX() < 0)
            map.setMapStartX(0);

        // Si on arrive au bout à droite, on stop le scrolling (moitié de l'écran à droite pour pas faire un affichage buggé)
        else if(map.getMapStartX() + WINDOW_WIDTH >= map.getMapEndX())
            map.setMapStartX(map.getMapEndX() - WINDOW_WIDTH);
    }

    void moveLeft(KeyboardInput &input, Tilemap &map) {
        x -= CHARACTER_SPEED;
        direction = LEFT;

        // Si on ne marchait pas déjà et qu'on était sur le sol
        if(state != WALK && onGround) {
            // On dit qu'on marche, et on reset l'animation
            state = WALK;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 4;
        }
    }

    void moveRight(KeyboardInput &input, Tilemap &map) {
        x += CHARACTER_SPEED;
        direction = RIGHT;

        // Si on ne marchait pas déjà et qu'on était sur le sol
        if(state != WALK && onGround) {
            // On dit qu'on marche, et on reset l'animation
            state = WALK;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 4;
        }
    }

    void goToIdle(KeyboardInput &input, Tilemap &map) {
        // On change l'animation si le joueur n'était pas déjà inactif
        if(state != IDLE) {
            state = IDLE;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 1;
        }
    }

    void doAJump(KeyboardInput &input, Tilemap &map) {
        y -= JUMP_HEIGHT;
        onGround = false;

        state = JUMP;
        frameNumber = 0;
        frameTimer = FRAME_TIMER;
        frameMax = 1;
    }

    void updateCharacter(KeyboardInput &input, Tilemap &map) {
        onGround = true;
        y = 332;

        // Si on va à gauche
        if(input.getButton().left)
            moveLeft(input, map);

        // Si on va à droite
        else if(input.getButton().right)
            moveRight(input, map);

        // Si on fait rien et qu'on est sur le sol
        else if(!input.getButton().right && !input.getButton().left && onGround)
            goToIdle(input, map);

        // Le saut
        if(input.getButton().jump)
            doAJump(input, map);


        // On gère le scrolling
        horizontalScrolling(map);
    }

};

#endif //PROJECT_CHARACTER_HPP
