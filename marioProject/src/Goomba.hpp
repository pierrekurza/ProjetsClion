#ifndef PROJECT_GOOMBA_HPP
#define PROJECT_GOOMBA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

// Pour les animations
#define FRAME_TIMER 5

// Taille du sprite du goomba
#define GOOMBA_WIDTH 32
#define GOOMBA_HEIGHT 32

// Vitesse
#define GOOMBA_SPEED 3

// Les états + la direction
#define WALKING 0
#define DEATH 1

#define RIGHT 1
#define LEFT 2

using namespace sf;

class Tilemap;
class Character;
class GameSound;

class Goomba {

private:

    Texture goombaTex;
    Sprite goomba;

    // Coordonnées de sprite
    int x, y;
    // Largeur, hauteur sprite
    int w, h;

    // Pour les animations
    int frameNumber, frameMax, frameTimer;

    // État d'un sprite, direction dans laquelle regarde un koopa
    int state, direction;

    // Pour la gestion des collisions
    bool onGround;

    // Pour la mort
    int deathTimer;

    // Déplacement temporaire avant la détection des collisions
    float dirX, dirY;

    // Sauvegarde des coordonnées de départ
    int saveX;

    /*//Les Limites des patrouilles
    bool wall = false;*/

public:
    Goomba();

    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    int getFrameNumber() const;
    int getFrameMax() const;
    int getFrameTimer() const;
    int getState() const;
    int getDirection() const;
    bool isOnGround() const;
    int getDeathTimer() const;
    float getDirX() const;
    float getDirY() const;
    int getSaveX() const;
    bool getOnGround() const;


    void initialize(int x1, int y1);

    void drawGoomba(Tilemap &map, RenderWindow &window);

    int updateGoomba(Tilemap &map, Character &chara, GameSound &sound);

    void mapCollideHorizontal(Tilemap &map, Character &chara);

    void mapCollideVertical(Tilemap &map, Character &chara);

    int collide(Character &chara);

    int checkFall(Tilemap &map);

    void copy(Goomba &goomba);

};
#endif //PROJECT_GOOMBA_HPP
