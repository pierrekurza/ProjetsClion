#ifndef PROJECT_GOOMBA_CPP
#define PROJECT_GOOMBA_CPP


#include "Goomba.hpp"
#include "Tilemap.hpp"
#include "GameSound.hpp"
#include "Character.hpp"

Goomba::Goomba() {
    // Chargement spritesheet
    if (!goombaTex.loadFromFile("graphics/goomba_tiles_32_32.png"))
        std::cerr << "Erreur lors du chargement du spritesheet du personnage" << std::endl;
    else
        goomba.setTexture(goombaTex);

    // Initialisation des variables d'un goomba
    dirX = 0;
    dirY = 0;
    x = 0;
    y = 0;
    h = 0;
    w = 0;
    frameMax = 0;
    frameNumber = 0;
    frameTimer = 0;
    state = WALKING;
    direction = 0;
    deathTimer = 0;
    saveX = 0;
    onGround = false;
    dirX = 0;
    dirY = 0;
}

int Goomba::getX() const { return x; }
int Goomba::getY() const { return y; }
int Goomba::getW() const { return w; }
int Goomba::getH() const { return h; }
int Goomba::getFrameNumber() const { return frameNumber; }
int Goomba::getFrameMax() const { return frameMax; }
int Goomba::getFrameTimer() const { return frameTimer; }
int Goomba::getState() const { return state; }
int Goomba::getDirection() const { return direction; }
bool Goomba::isOnGround() const { return onGround; }
int Goomba::getDeathTimer() const { return deathTimer; }
float Goomba::getDirX() const { return dirX; }
float Goomba::getDirY() const { return dirY; }
int Goomba::getSaveX() const { return saveX; }
bool Goomba::getOnGround() const { return onGround; }

void Goomba::initialize(int x1, int y1) {
    // Position de départ
    x = x1;
    y = y1;

    // Direction et état
    direction = RIGHT;
    state = WALKING;

    // Frame où commencer
    frameNumber = 0;

    // Timer entre frames
    frameTimer = FRAME_TIMER;

    // Frames max pour l'animation WALK (1)
    frameMax = 2;

    w = GOOMBA_WIDTH;
    h = GOOMBA_HEIGHT;

    onGround = false;
}

void Goomba::drawGoomba(Tilemap &map, RenderWindow &window) {
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

    goomba.setPosition(Vector2f(x - map.getMapStartX(), y - map.getMapStartY()));
    if (direction == LEFT) {
        goomba.setTextureRect(IntRect((frameNumber + 1) * w, state * h, -w, h));
        window.draw(goomba);
    }
    else {
        goomba.setTextureRect(IntRect(frameNumber * w, state * h, w, h));
        window.draw(goomba);
    }
}

int Goomba::updateGoomba(Tilemap &map, Character &chara, GameSound &sound) {
    if (deathTimer == 0) {
        dirX = 0;
        dirY += GRAVITY_SPEED;

        if(x + h < chara.getX())
            direction = RIGHT;
        else if (x > chara.getX())
            direction = LEFT;

        if (direction == LEFT)
            dirX -= GOOMBA_SPEED;
        else
            dirX += GOOMBA_SPEED;

        // Collisions
        mapCollideHorizontal(map, chara);
        mapCollideVertical(map, chara);

        // On détecte les collisions avec le personnage
        if (collide(chara) == 1) {
            chara.killCharacter();
        }
        else if (collide(chara) == 2) {
            sound.playKillSound();
            deathTimer = 1;

        }
    }

    // Si le monstre est mort
    if (deathTimer > 0) {
        if (--deathTimer == 0)
            return 1;
        else
            return 0;
    }
    return -1;
}

void Goomba::mapCollideHorizontal(Tilemap &map, Character &chara) {
    int i, xLU, xRD, yLU, yRD;

    // On considère qu'on est en l'air tant qu'on est sûr de pas toucher le sol
    onGround = false;

    // On va tester les mouvements horizontaux
    // On découpe le sprite en bloc de tiles
    i = TILE_SIZE;

    //while (i != GOOMBA_HEIGHT) {
        // On calcule les coins du sprite à gauche et à droite pour voir ce que ça touche
        xLU = (int) (x + dirX) / TILE_SIZE;
        xRD = (int) (x + dirX + GOOMBA_WIDTH - 1) / TILE_SIZE;

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
                    x -= GOOMBA_WIDTH + 1;
                    dirX = 0;
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
            }
        }

        /*// On passe à la portion de tile suivante (qu'on réduit si ça fait plus grand que le sprite du perso)
        i += TILE_SIZE;
        if (i > GOOMBA_HEIGHT)
            i = GOOMBA_HEIGHT;*/
    //}

    // Ensuite on applique le déplacement
    x += dirX;

}

void Goomba::mapCollideVertical(Tilemap &map, Character &chara) {
    // Et on refait pareil avec l'axe vertical (pas besoin de while car la largeur du sprite est plus petite qu'une tile
    int i = GOOMBA_WIDTH;

    int xLU = x / TILE_SIZE;
    int xRD = (x + i) / TILE_SIZE;

    int yLU = (int) (y + dirY) / TILE_SIZE;
    int yRD = (int) (y + dirY + GOOMBA_HEIGHT) / TILE_SIZE;

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
                y -= GOOMBA_HEIGHT;
                dirY = 0;
                onGround = true;
            }
        }
        //////////////////////////////
        // Déplacement vers le haut //
        //////////////////////////////
        else {
            if(dirY < 0) {
                if((map.getTile(yLU, xLU) > BLANK_TILE && map.getTile(yLU, xLU) != POWERUP_COIN &&
                    map.getTile(yLU, xLU) != POWERUP_MUSHROOM && map.getTile(yLU, xLU) != LADDER) ||
                   (map.getTile(yLU, xRD) > BLANK_TILE && map.getTile(yLU, xRD) != POWERUP_COIN &&
                    map.getTile(yLU, xRD) != POWERUP_MUSHROOM && map.getTile(yLU, xRD) != LADDER)) {

                    y = (yLU + 1) * TILE_SIZE;
                    dirY = 0;
                }
            }
        }
    }

    y += dirY;

    // Si on tombe dans un trou
    if (y > map.getMapEndY())
        deathTimer = 60;
}

int Goomba::checkFall(Tilemap &map) {
    // Test si il y a du sol sous le monstre
    // return 1 s'il doit tomber
    int Fx, Fy;
    // On regarde la direction pour savoir quel point utiliser
    if(direction == LEFT) {
        // Gauche
        Fx = (int)(x + dirX) / TILE_SIZE;
        Fy = (y + h - 1) / TILE_SIZE;

        if(Fy < 0)
            Fy = 1;

        if(Fy > MAX_Y)
            Fy = MAX_Y;

        if(Fx < 0)
            Fx = 1;

        if(Fx > MAX_X)
            Fx = MAX_X;

        // On teste si la tile sous le monstre est vide
        if(map.getTile(Fy + 1, Fx) == BLANK_TILE)
            return 1;
        else
            return 0;
    }
    else {
        // Droite
        Fx = (int)(x + w + dirX) / TILE_SIZE;
        Fy = (y + h - 1) / TILE_SIZE;

        if(Fy <= 0)
            Fy = 1;

        if(Fy >= MAX_Y)
            Fy = MAX_Y;

        if(Fx <= 0)
            Fx = 1;

        if(Fx >= MAX_X)
            Fx = MAX_X;

        if(map.getTile(Fy + 1, Fx) == BLANK_TILE)
            return 1;
        else
            return 0;
    }
}

int Goomba::collide(Character &chara) {
    // On gère les collisions monstre / joueur
    // return 0 s'il n'y a pas de collisions
    // return 1 si le joueur se fait toucher
    // return 2 si le goomba est touché

    if((chara.getX() >= x + w)
       || (chara.getX() + chara.getW() <= x)
       || (chara.getY() > y + h)
       || (chara.getY() + chara.getH() <= y)) {
        return 0;
    }

    else if (chara.getY() + chara.getH() <= y + 10) {
        chara.setDirY( -JUMP_HEIGHT);
        return 2;
    }

    else
        return 1;
}

void Goomba::copy(Goomba &goomba) {
    dirX = goomba.getDirX();
    dirY = goomba.getDirY();
    x = goomba.getX();
    y = goomba.getY();
    h = goomba.getH();
    w = goomba.getW();
    frameNumber = goomba.getFrameNumber();
    frameTimer = goomba.getFrameTimer();
    frameMax = goomba.getFrameMax();
    state = goomba.getState();
    direction = goomba.getDirection();
    onGround = goomba.getOnGround();
    saveX = goomba.getSaveX();
}

#endif