#ifndef PROJECT_CHARACTER_HPP
#define PROJECT_CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tilemap.hpp"
#include "KeyboardInput.hpp"
#include <iostream>

// Pour les animations
#define FRAME_TIMER 5

// Taille du sprite de Mario
#define CHARACTER_WIDTH 26
#define CHARACTER_HEIGHT 50

// Vitesse
#define CHARACTER_SPEED 4
#define CLIMBING_SPEED 3
// Gravité
#define GRAVITY_SPEED 0.5

// Les états + la direction
#define IDLE 0
#define WALK 1
#define JUMP 2
#define CLIMB 3

#define RIGHT 1
#define LEFT 2

#define JUMP_HEIGHT 11

// Limite du scrolling
#define LIMITE_X 300
#define LIMITE_W 100

#define BLANK_TILE 0
#define POWERUP_COIN 47
#define POWERUP_MUSHROOM 57
#define ITEM_BLOCK 11
#define NORMAL_BLOCK 60
#define LADDER 61

#define CAMERA_SPEED 4

#define LEVEL_MAX 2

using namespace sf;

class Tilemap;

class KeyboardInput;

class Character {

private:
    Texture         characterTex;
    Sprite          character;
    Sound           _sound;
    SoundBuffer     _coinSound;
    SoundBuffer     _stageClearSound;
    SoundBuffer     _oneUPsound;
    SoundBuffer     _oneUPapparition;
    SoundBuffer     _coinSoundIfCoinsEquals100;

    // Les variables joueur
    int hp;
    int lives;
    int coins; // 100 pièces : 1 vie

    // Coordonnées du personnage (point haut gauche du sprite)
    int x, y;

    // Pour les animations
    int frameNumber, frameMax, frameTimer;

    // État d'un sprite, direction dans laquelle regarde Mario
    int state, direction;

    // Pour la gestion des collisions
    bool onGround, onLadder;

    // Déplacement temporaire avant la détection des collisions
    float dirX, dirY;

    // Décompte quand on est mort
    int deathTimer;

public:
    Character() {
        // Chargement spritesheet
        if (!characterTex.loadFromFile("graphics/mario_spritesheet.png"))
            std::cerr << "Erreur lors du chargement du spritesheet du personnage" << std::endl;
        else
            character.setTexture(characterTex);

        // Initialisation des variables joueur
        dirX = 0;
        dirY = 0;
        hp = 1;
        x = 0;
        y = 300;
        frameMax = 0;
        frameNumber = 0;
        frameTimer = 0;
        state = 0;
        direction = 0;
        onGround = false;
        onLadder = false;
        dirX = 0;
        dirY = 0;
        deathTimer = 0;
    }

    // Accesseurs
    int getX() const { return x; }

    int getY() const { return y; }

    int getH() const { return CHARACTER_HEIGHT; }

    int getW() const { return CHARACTER_WIDTH; }

    float getDirX() const { return dirX; }

    float getDirY() const { return dirY; }

    int getOnGround() const { return onGround; }

    int getHp() const { return hp; }

    int getLives() const { return lives; }

    int getCoins() const { return coins; }

    int getDirection() const { return direction; }

    int getDeathTimer() const { return deathTimer; }

    // Setteurs
    void setX(int v) { x = v; }

    void setY(int v) { y = v; }

    void setDirX(float v) { dirX = v; }

    void setDirY(float v) { dirY = v; }

    void setOnGround(bool v) { onGround = v; }

    void setOnLadder(bool v) { onLadder = v; }

    void setLives(int v) { lives = v; }

    void setCoins(int v) { coins = v; }

    void setDeathTimer(int v) { deathTimer = v; }

    // Fonctions
    void initialize(Tilemap &map) {
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
        x = 0;
        y = 300;

        map.setMapStartX(0);
        map.setMapStartY(0);

        onGround = false;
        onLadder = false;
        deathTimer = 0;
    }

    void playCoinSound()
    {
        if(!_coinSound.loadFromFile("soundsV2/coin.wav"))
            cerr << L"Le son Coin n'a pas pu être chargé" << endl;
        else
        {
            _sound.setBuffer(_coinSound);
            _sound.play();
        }
    }

    void playAnOtherCoinSoundIfCoinsEquals100()
    {
        if(!_coinSoundIfCoinsEquals100.loadFromFile("soundsV2/maxCoins.wav"))
            cerr << "Le son MaxCoins n'a pas pu être chargé" << endl;
    }

    void playOneUpSound()
    {
        if(!_oneUPsound.loadFromFile("soundsV2/oneUP.wav"))
            cerr << "Le son ONE up n'a pas pu être chargé" << endl;
        else
        {
            _sound.setBuffer(_oneUPsound);
            _sound.play();
        }
    }

    void playOneUPapparition()
    {
        if(!_oneUPapparition.loadFromFile("soundsV2/powerUPApparition.wav"))
            cerr << "Le son Power UP apparition n'a pas pu être chargé" << endl;
        else
        {
            _sound.setBuffer(_oneUPapparition);
            _sound.play();
        }
    }


    void playStageClearSound()
    {
        if(!_stageClearSound.loadFromFile("sounds/stageClear.wav"))
            cerr << L"Le son pour le StageClear n'a pas pu être chargé" << endl;
        else
        {
            _sound.setBuffer(_stageClearSound);
            _sound.play();
        }
    }

    void drawCharacter(Tilemap &map, RenderWindow &window) {
        // Timer
        // Si le timer arrive à zéro
        if (frameTimer <= 0) {
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
        if (direction == LEFT) {
            character.setTextureRect(
                    IntRect((frameNumber + 1) * CHARACTER_WIDTH, state * CHARACTER_HEIGHT, -CHARACTER_WIDTH,
                            CHARACTER_HEIGHT));
            window.draw(character);
        }
        else {
            character.setTextureRect(IntRect(frameNumber * CHARACTER_WIDTH, state * CHARACTER_HEIGHT, CHARACTER_WIDTH,
                                             CHARACTER_HEIGHT));
            window.draw(character);
        }
    }

    void horizontalScrolling(Tilemap &map) {
        // On va créer une "boîte" autour du personnage, si on la dépasse, on recentre la caméra

        int xCharCoor = x + CHARACTER_WIDTH / 2;
        int xMinLim = map.getMapStartX() + LIMITE_X;
        int xMaxLim = xMinLim + LIMITE_W;

        // Si on est mort et loin de la caméra
        if (xCharCoor < map.getMapStartX())
            map.setMapStartX(map.getMapStartX() - 30);

        // Si on dépasse à gauche, on recule la caméra
        if (xCharCoor < xMinLim) {
            map.setMapStartX(map.getMapStartX() - CAMERA_SPEED);
        }
        // Si on dépasse à droite, on avance la caméra
        if (xCharCoor > xMaxLim) {
            map.setMapStartX(map.getMapStartX() + CAMERA_SPEED);
        }
        // Si on arrive au bout à gauche, on stop le scrolling
        if (map.getMapStartX() < 0)
            map.setMapStartX(0);

            // Si on arrive au bout à droite, on stop le scrolling (moitié de l'écran à droite pour pas faire un affichage buggé)
        else if (map.getMapStartX() + WINDOW_WIDTH >= map.getMapEndX())
            map.setMapStartX(map.getMapEndX() - WINDOW_WIDTH);
    }

    void moveLeft(Tilemap &map) {
        direction = LEFT;
        if (x > map.getMapStartX())
            dirX -= CHARACTER_SPEED;
        // Si on ne marchait pas déjà et qu'on était sur le sol
        if (state != WALK && onGround) {
            // On dit qu'on marche, et on reset l'animation
            state = WALK;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 4;
        }
        if (state == CLIMB && !onLadder) {
            goToIdle();
        }
    }

    void moveRight() {
        dirX += CHARACTER_SPEED;
        direction = RIGHT;

        // Si on ne marchait pas déjà et qu'on était sur le sol
        if (state != WALK && onGround) {
            // On dit qu'on marche, et on reset l'animation
            state = WALK;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 4;
        }
        if (state == CLIMB && !onLadder) {
            goToIdle();
        }
    }


    void climbLadder() {
        dirY = -CLIMBING_SPEED;
        if (state != CLIMB) {
            state = CLIMB;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 2;
        }
    }

    void downLadder() {
        dirY = CLIMBING_SPEED;
        if (state != CLIMB) {
            state = CLIMB;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 2;
        }
    }

    void goToIdle() {
        // On change l'animation si le joueur n'était pas déjà inactif
        if (state != IDLE) {
            state = IDLE;
            frameNumber = 0;
            frameTimer = FRAME_TIMER;
            frameMax = 1;
        }
    }

    void doAJump() {
        dirY -= JUMP_HEIGHT;
        onGround = false;

        state = JUMP;
        frameNumber = 0;
        frameTimer = FRAME_TIMER;
        frameMax = 1;
    }

    void powerUp(int y, int x, Tilemap &map) {
        if (map.getTile(y, x) == POWERUP_MUSHROOM) if (lives < 100)
        {
            playOneUpSound();
            lives++;
        }
        if (map.getTile(y, x) == POWERUP_COIN) {
            playCoinSound();
            if (++coins >= 100) {
                coins = 0;
                if (lives < 100)
                    lives++;
            }
        }
        map.setTile(y, x, BLANK_TILE);
    }

    void itemBlock(int y, int x, Tilemap &map) {
        // On gère le cas d'un bloc d'item
        if (map.getTile(y, x) == ITEM_BLOCK) {
            // Une chance sur 10 d'avoir une vie, sinon c'est une pièce
            int randNum = (int) random() % 10;
            if (randNum < 1) {
                // Le powerup n'apparait que si la tile sur laquelle il doit apparaitre est vide
                if (map.getTile(y - 1, x) == BLANK_TILE) {
                    map.setTile(y - 1, x, POWERUP_MUSHROOM);
                    map.setTile(y, x, NORMAL_BLOCK);
                }
            }
            else {
                // Le powerup n'apparait que si la tile sur laquelle il doit apparaitre est vide
                if (map.getTile(y - 1, x) == BLANK_TILE) {
                    map.setTile(y - 1, x, POWERUP_COIN);
                    map.setTile(y, x, NORMAL_BLOCK);
                    playOneUPapparition();
                }
            }
        }
    }

    void isOnLadder(Tilemap &map) {
        int xF = x / TILE_SIZE;
        int yF = y / TILE_SIZE;
        int yF2 = (y + CHARACTER_WIDTH + 10) / TILE_SIZE;
        onLadder = (map.getTile(yF, xF) == LADDER || map.getTile(yF2, xF) == LADDER);
    }

    void mapCollideHorizontal(Tilemap &map) {
        int i, xLU, xRD, yLU, yRD;

        // On considère qu'on est en l'air tant qu'on est sûr de pas toucher le sol
        onGround = false;
        onLadder = false;
        // On va tester les mouvements horizontaux
        // On découpe le sprite en bloc de tiles
        i = TILE_SIZE;

        while (i != CHARACTER_HEIGHT) {
            // On calcule les coins du sprite à gauche et à droite pour voir ce que ça touche
            xLU = (int) (x + dirX) / TILE_SIZE;
            xRD = (int) (x + dirX + CHARACTER_WIDTH - 1) / TILE_SIZE;

            // Pareil pour les y
            yLU = y / TILE_SIZE;
            yRD = (y + i - 1) / TILE_SIZE;

            // Ensuite, on teste les mouvements du updateCharacter (dirX et dirY)
            if (xLU >= 0 && xRD < MAX_X && yLU >= 0 && yRD < MAX_Y) {
                ///////////////////////////////
                // Si on se déplace à droite //
                ///////////////////////////////
                if (dirX > 0) {
                    // On vérifie si les tiles sont solides
                    if ((map.getTile(yLU, xRD) > BLANK_TILE && map.getTile(yLU, xRD) != POWERUP_COIN &&
                         map.getTile(yLU, xRD) != POWERUP_MUSHROOM && map.getTile(yLU, xRD) != LADDER) ||
                        (map.getTile(yRD, xRD) > BLANK_TILE && map.getTile(yRD, xRD) != POWERUP_COIN &&
                         map.getTile(yRD, xRD) != POWERUP_MUSHROOM && map.getTile(yRD, xRD) != LADDER)) {
                        // Si c'est le cas on place le perso le plus proche possible
                        x = xRD * TILE_SIZE;
                        x -= CHARACTER_WIDTH + 1;
                        dirX = 0;
                    }
                        // Si c'est un powerup, on appelle powerup et on enlève la tile
                    else if (map.getTile(yLU, xRD) == POWERUP_COIN || map.getTile(yLU, xRD) == POWERUP_MUSHROOM
                             || map.getTile(yRD, xRD) == POWERUP_COIN || map.getTile(yRD, xRD) == POWERUP_MUSHROOM) {
                        powerUp(yRD, xRD, map);
                        powerUp(yLU, xRD, map);
                        map.setTile(yRD, xRD, BLANK_TILE);
                    }
                }
                    //////////////////////////////
                    // Pareil à gauche ///////////
                    //////////////////////////////
                else if (dirX < 0) {
                    if ((map.getTile(yLU, xLU) > BLANK_TILE && map.getTile(yLU, xLU) != POWERUP_COIN &&
                         map.getTile(yLU, xLU) != POWERUP_MUSHROOM && map.getTile(yLU, xLU) != LADDER) ||
                        (map.getTile(yRD, xLU) > BLANK_TILE && map.getTile(yRD, xLU) != POWERUP_COIN &&
                         map.getTile(yRD, xLU) != POWERUP_MUSHROOM && map.getTile(yRD, xLU) != LADDER)) {
                        x = (xLU + 1) * TILE_SIZE;
                        dirX = 0;
                    }
                    else if (map.getTile(yLU, xLU) == POWERUP_COIN || map.getTile(yLU, xLU) == POWERUP_MUSHROOM
                             || map.getTile(yRD, xLU) == POWERUP_COIN || map.getTile(yRD, xLU) == POWERUP_MUSHROOM) {
                        powerUp(yRD, xLU, map);
                        powerUp(yLU, xLU, map);
                        map.setTile(yRD, xLU, BLANK_TILE);
                    }
                }
            }

            // On passe à la portion de tile suivante (qu'on réduit si ça fait plus grand que le sprite du perso)
            i += TILE_SIZE;
            if (i > CHARACTER_HEIGHT)
                i = CHARACTER_HEIGHT;
        }

        // Ensuite on applique le déplacement
        x += dirX;

    }

    void mapCollideVertical(Tilemap &map, KeyboardInput &input) {
        // Et on refait pareil avec l'axe vertical (pas besoin de while car la largeur du sprite est plus petite qu'une tile
        int i = CHARACTER_WIDTH;

        int xLU = x / TILE_SIZE;
        int xRD = (x + i) / TILE_SIZE;

        int yLU = (int) (y + dirY) / TILE_SIZE;
        int yRD = (int) (y + dirY + CHARACTER_HEIGHT) / TILE_SIZE;

        if (xLU >= 0 && xRD < MAX_X && yLU >= 0 && yRD < MAX_Y) {
            //////////////////////////////////
            // Si on se déplace vers le bas //
            //////////////////////////////////
            if (dirY > 0) {
                if ((map.getTile(yRD, xLU) > BLANK_TILE && map.getTile(yRD, xLU) != POWERUP_COIN &&
                     map.getTile(yRD, xLU) != POWERUP_MUSHROOM && map.getTile(yRD, xLU) != LADDER) ||
                    (map.getTile(yRD, xRD) > BLANK_TILE && map.getTile(yRD, xRD) != POWERUP_COIN &&
                     map.getTile(yRD, xRD) != POWERUP_MUSHROOM && map.getTile(yRD, xRD) != POWERUP_MUSHROOM &&
                     map.getTile(yRD, xRD) != LADDER)) {
                    // On colle le joueur au sol et on le déclare au sol
                    y = yRD * TILE_SIZE;
                    y -= CHARACTER_HEIGHT;
                    dirY = 0;
                    onGround = true;
                }
                else if (map.getTile(yRD, xLU) == POWERUP_COIN || map.getTile(yRD, xLU) == POWERUP_MUSHROOM
                         || map.getTile(yRD, xRD) == POWERUP_COIN || map.getTile(yRD, xRD) == POWERUP_MUSHROOM) {
                    powerUp(yRD, xLU, map);
                    powerUp(yRD, xRD, map);
                    map.setTile(yRD, xLU, BLANK_TILE);
                }
                    // Cas spécial échelles, si on est sur le haut d'une échelle et quu'on ne veut pas descendre
                else if ((map.getTile(yRD, xRD) == LADDER) &&
                         (map.getTile(yRD - 1, xRD) == BLANK_TILE) &&
                         !input.getButton().down) {
                    // On colle le joueur au sol et on le déclare au sol
                    y = yRD * TILE_SIZE;
                    y -= CHARACTER_HEIGHT;
                    dirY = 0;
                    onGround = true;
                }

            }
                //////////////////////////////
                // Déplacement vers le haut //
                //////////////////////////////
            else if (dirY < 0) if ((map.getTile(yLU, xLU) > BLANK_TILE && map.getTile(yLU, xLU) != POWERUP_COIN &&
                                    map.getTile(yLU, xLU) != POWERUP_MUSHROOM && map.getTile(yLU, xLU) != LADDER) ||
                                   (map.getTile(yLU, xRD) > BLANK_TILE && map.getTile(yLU, xRD) != POWERUP_COIN &&
                                    map.getTile(yLU, xRD) != POWERUP_MUSHROOM && map.getTile(yLU, xRD) != LADDER)) {

                // On gère les cas de collision avec un bloc item
                itemBlock(yLU, xLU, map);
                itemBlock(yLU, xRD, map);

                y = (yLU + 1) * TILE_SIZE;
                dirY = 0;
            }
            else if (map.getTile(yLU, xLU) == POWERUP_COIN || map.getTile(yLU, xLU) == POWERUP_MUSHROOM
                     || map.getTile(yLU, xRD) == POWERUP_COIN || map.getTile(yLU, xRD) == POWERUP_MUSHROOM) {
                powerUp(yLU, xLU, map);
                powerUp(yLU, xRD, map);
            }
        }

        y += dirY;

        // Si on tombe dans un trou
        if (y > map.getMapEndY())
            deathTimer = 60;
    }

    void nextLevel(Tilemap &map) {
        if(map.getLevel() < LEVEL_MAX) {
            map.setLevel(map.getLevel() + 1);
            map.changeLevel();
            initialize(map);
            playStageClearSound();
        }
    }

    void updateCharacter(KeyboardInput &input, Tilemap &map) {
        // Si le timer vaut 0, ça veut dire que le jeu a repris
        if (!deathTimer) {
            dirX = 0;
            if (state != CLIMB)
                dirY += GRAVITY_SPEED;

            // Si on va à gauche
            if (input.getButton().left)
                moveLeft(map);

                // Si on va à droite
            else if (input.getButton().right) {
                moveRight();
            }
                // Si on grimpe à une échelle
            else if (onLadder) {
                if (input.getButton().up)
                    climbLadder();
                else if (input.getButton().down)
                    downLadder();
                else if (state == CLIMB) {
                    dirY = 0;
                    frameTimer = FRAME_TIMER;
                }
                else
                    goToIdle();
            }

            else if (state == CLIMB && !onLadder)
                goToIdle();

                // Si on fait rien et qu'on est sur le sol
            else if (!input.getButton().right && !input.getButton().left && onGround)
                goToIdle();

            // Le saut
            if (input.getButton().jump && onGround)
                doAJump();

            // On gère les collisions
            mapCollideHorizontal(map);
            mapCollideVertical(map, input);
            isOnLadder(map);


            // On gère le scrolling
            horizontalScrolling(map);
        }
            // Si on est mort
        else {
            deathTimer--;
            if (deathTimer == 0) {
                lives--;
                map.changeLevel();
                initialize(map);
            }
        }
    }


};

#endif //PROJECT_CHARACTER_HPP
