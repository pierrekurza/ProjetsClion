#ifndef    APPLICATION_HPP
#define APPLICATION_HPP

#include "cerclesTransparents.hpp"

class Application {
// Attributs
private:
    sf::RenderWindow        _window;// Attribut graphique
    cerclesTransparents     _mesCercles;

// Méthodes
private:
    void processEvents() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            else {
                _mesCercles.processEvent(event);
            }
        }
    }

    void update() {

    }

    void render() {
        _window.clear();
        _mesCercles.draw(_window);
        _window.display();
    }

public:
    Application() :
            _window(sf::VideoMode(800, 800), "WOW so much Circles"),
            _mesCercles()
    { }

    ~Application() { }

    void run() {
        do {
            processEvents();
            update();
            render();
        }
        while (_window.isOpen());
    }
};

#endif
