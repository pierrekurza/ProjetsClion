//
// Created by xeloow on 06/06/16.
//

#ifndef TD5_SONS_MUSICRECORD_HPP
#define TD5_SONS_MUSICRECORD_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class MusicRecord
{
public:

    const float TAILLE_SQUARE = 50;
    enum class Event {
        LEFT_CLICK,
        RIGHT_CLICK,
        NONE
    };

private:
    sf::Music*                   _musique;
    sf::RectangleShape*          _shape;
    Event                        _event;

public:
    MusicRecord();
    ~MusicRecord();

    void init(const sf::Vector2f& position, const string filename)
    {
        _event = Event::NONE;
        _shape->setPosition(position);
        _shape->setSize(sf::Vector2f(TAILLE_SQUARE, TAILLE_SQUARE));
        _shape->setFillColor(sf::Color::Black);
        _shape->setOutlineColor(sf::Color::White);
        _shape->setOutlineThickness(1);
    }

    //la position de la souris se trouve dans un carré
    bool contains(const sf::Vector2f& mousePos)
    {
        return _shape->getGlobalBounds().contains(mousePos);
    }

    void handleEvent(const sf::Event& evt)
    {

    }

    void update(sf::Time& delta)
    {

    }

    void draw(sf::RenderTarget& renderer) {

    }
};

typedef vector<MusicRecord>         _vecteurDeSons;
class Scene;
class Jukebox
{
private:
    Scene&                  _scene;
    _vecteurDeSons          _mesSons;

public:
    Jukebox(Scene& scene);
    ~Jukebox() {};

    void init();

    void handleEvent(const sf::Event& evt)
    {
        size_t i = 0;
        bool trouve = false;
        if(evt.type == sf::Event::MouseButtonPressed)
        {
            while( i < _vecteurDeSons.size() && !trouve)
            {
                if(_vecteurDeSons[i].contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y)))
                    trouve = true;
                else
                    i++;

                if(trouve)
                    _boxes[i].handleEvent(evt.mouseButton);
            }
        }
    }

    void update(sf::Time& delta);

    void draw(sf::RenderTarget& renderer);

};

#endif //TD5_SONS_MUSICRECORD_HPP
