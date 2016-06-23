#ifndef PROJECT_TILEMAP_HPP
#define PROJECT_TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/basic_string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

// Nombre de tuiles sur 1 niveau, puis nombre de tuiles l/c du tileset
#define MAX_X 100
#define MAX_Y 15
#define X_NUMBER 10
#define Y_NUMBER 10

#define TILE_SIZE 32


using namespace std;
using namespace sf;


class Tilemap {

private:
    // Tileset
    Texture tilesetTex;
    Sprite tileset;

    // Point de début de la création de map
    int mapStartX, mapStartY;

    // Fin de la map
    int mapEndX, mapEndY;

    // Position de départ du personnage
    int characterBeginX, characterBeginY;

    // Tilemap
    int tile1[MAX_Y][MAX_X];

    // Tilemap2
    int tile2[MAX_Y][MAX_X];

    // Numéro du niveau
    int level;


public:

    Tilemap() {
        // Tileset
        if(!tilesetTex.loadFromFile("graphics/tileset.png"))
            // Problème
            cout << "Problème lors du chargement du niveau." << endl;
        else
            tileset.setTexture(tilesetTex);

        // Variables de map
        mapStartX = 0;
        mapStartY = 0;
        level = 1;
    }


// Accesseurs
    int getLevel() const {
        return level;
    }
    int getCharacterBeginX() const {
        return characterBeginX;
    }
    int getCharacterBeginY() const {
        return characterBeginY;
    }
    int getMapStartX() const {
        return mapStartX;
    }
    int getMapStartY() const {
        return mapStartY;
    }
    int getMapEndX() const {
        return mapEndX;
    }
    int getMapEndY() const {
        return mapEndY;
    }
    int getTile(int y, int x) const {
        return tile1[y][x];
    }


    // Setteurs
    void setMapStartX(int v) {
        mapStartX = v;
    }
    void setMapStartY(int v) {
        mapStartY = v;
    }
    void setTile(int y, int x, int v) {
        tile1[y][x] = v;
    }
    void setLevel(int v) {
        level = v;
    }

    //###############################//
    // CHARGEMENT D'UNE MAP #########//
    //###############################//

    void loadLevel(string filename) {
        // Flux pour lire les fichiers map
        fstream fic;
        int x = 0, y = 0;

        mapEndX = 0;
        mapEndY = 0;

        // Vecteur pour les lignes
        vector < vector < int > > lines;

        // Vecteur temporaire pour accéder aux lignes
        vector < int > tmpVec;

        // Chaînes de caractères temporaires
        string strTmp2, strTmp;

        // Stringstream pour gérer les chaînes
        stringstream iostream;

        // On ouvre un fichier
        fic.open(filename.c_str(), fstream::in);

        // Test pour voir si le fichier a été ouvert
        if(!fic.is_open()) {
            cerr << "Erreur de chargement de la map." << endl;
            exit(1);
        }

        // On lit tout le fichier
        while(!fic.eof()) {
            // On récupère une ligne
            getline(fic, strTmp2);

            // Si c''est une chaîne vide, on continue
            if (strTmp2.size() == 0)
                continue;

            // Sinon on réinitialise le stringstream et on y envoie le contenu de la chaine
            iostream.clear();
            iostream.str(strTmp2);

            // On réinitialise le vector line
            tmpVec.clear();

            // On boucle pour récupérer chaque numéro de tile de la map
            while(1) {
                // On récupère le numéro de tile  entre chaque espace
                getline(iostream, strTmp, ' ');

                // On le met dans le vecteur line
                tmpVec.push_back(atoi(strTmp.c_str()));

                // On quitte la boucle quand on a fini
                if(!iostream.good())
                    break;
            }

            // Si le vecteur line contient quelque chose, on l'envoie dans notre vecteur 2D
            if(tmpVec.size() != 0)
                lines.push_back(tmpVec);
        }

        // On peut fermer le fichier
        fic.close();

        // On va maintenant remplir les variables de la classe avec le vecteur 2D temporaire
        // On récupère les 2 premières valeurs de la 1ère ligne (départ du personnage)
        characterBeginX = lines[0][0];
        characterBeginY = lines[0][1];

        // On charge la première ligne (avec le décalage de 2)
        for(x = 3; x < MAX_X + 2; x++) {
            tile1[y][x - 2] = lines[y][x];
        }


        // On peut charger le reste des tiles pour la première couche
        for(y = 1; y < MAX_Y; y++)
            for(x = 0; x < MAX_X; x++) {
                // On copie la valeur du vecteur dans le tableau de tiles
                tile1[y][x] = lines[y][x];

                // On détecte si la tile est vide ou non
                if(tile1[y][x] > 0) {
                    // Si elle est vide on augmente la valeur de mapEndX ou Y
                    if(x > mapEndX)
                        mapEndX = x;
                    if(y > mapEndY)
                        mapEndY = y;
                }
            }

        // On fait la 2ème couche
        for(y = 0; y < MAX_Y; y++)
            for(x = 0; x < MAX_X; x++)
                tile2[y][x] = lines[y + MAX_Y][x];

        // On convertit les dimensions de la map en pixels
        // (on ajoute 1 car un commence à 0, les tiles sont de taille TILE_SIZE)
        mapEndX = (mapEndX + 1) * TILE_SIZE;
        mapEndY = (mapEndY + 1) * TILE_SIZE;
    }


    //###############################//
    // DESSIN D'UNE MAP #########//
    //###############################//

    void drawLevelLayer(int layer, RenderWindow& window) {
        int x, y, mapX, x1, x2, mapY, y1, y2, xSource, ySource, tileNum;

        /* On initialise mapX en tant que première colonne
         * Ça correspond aux X de la map (pixels) divisés par la taille d'une tile */
        mapX = mapStartX / TILE_SIZE;

        /* Coordonnées de départ pour l'affichage de la map
         * détermine à quelles coordonnées il faut découper la première colonne du tileset */
        x1 = (mapStartX % TILE_SIZE) * -1;

        /* Calcul des coordonnées de la fin de la map */
        x2 = x1 + WINDOW_WIDTH + TILE_SIZE;

        // Pareil pour les Y
        mapY = mapStartY / TILE_SIZE;
        y1 = (mapStartY % TILE_SIZE) * -1;
        y2 = y1 + WINDOW_HEIGHT + TILE_SIZE;
        // On dessine la carte en commençant par mapStartX et Y

        if (layer == 1) {
            for(y = y1; y < y2; y += TILE_SIZE) {
                /* A chaque début de ligne on réinitialise le mapX (qui contient la colonne 0 au début) */
                mapX = mapStartX / TILE_SIZE;

                /* A chaque colonne de tile, on dessine la bonne tile */
                for (x = x1; x < x2; x += TILE_SIZE) {
                    // Suivant le numéro de tile, on découpe le tileset
                    tileNum = tile1[mapY][mapX];

                    // Calcul pour obtenir son y et son x (tileset de 32 tiles par ligne/colonne)
                    ySource = tileNum / Y_NUMBER * TILE_SIZE;
                    xSource = tileNum % X_NUMBER * TILE_SIZE;

                    // On pose la bonne tile au bon endroit
                    tileset.setPosition(Vector2f(x, y));
                    tileset.setTextureRect(IntRect(xSource, ySource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileset);

                    mapX++;
                }
                mapY++;
            }
        }

        else if (layer == 2) {
            for(y = y1; y < y2; y += TILE_SIZE) {
                /* A chaque début de ligne on réinitialise le mapX (qui contient la colonne 0 au début) */
                mapX = mapStartX / TILE_SIZE;

                /* A chaque colonne de tile, on dessine la bonne tile */
                for (x = x1; x < x2; x += TILE_SIZE) {
                    // Suivant le numéro de tile, on découpe le tileset (a = numéro de tile)
                    tileNum = tile2[mapY][mapX];

                    // Calcul pour obtenir son y et son x (tileset de 32 tiles par ligne/colonne)
                    ySource = tileNum / Y_NUMBER * TILE_SIZE;
                    xSource = tileNum % X_NUMBER * TILE_SIZE;

                    // On pose la bonne tile au bon endroit
                    tileset.setPosition(Vector2f(x, y));
                    tileset.setTextureRect(IntRect(xSource, ySource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileset);

                    mapX++;
                }
                mapY++;
            }
        }
    }

    // Changer de niveau
    void changeLevel() {
        string filename;
        char lvl = (char) (level + '0');
        filename = "maps/map .txt";
        filename[8] = lvl;
        loadLevel(filename);
    }
};


#endif //PROJECT_TILEMAP_HPP
