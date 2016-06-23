#ifndef    APPLICATION_HPP
#define APPLICATION_HPP

#include "paletteCouleurs.hpp"

class Application {
// Attributs
private:
    sf::RenderWindow        _window;// Attribut graphique
    paletteCouleurs         _maPalette;

// Méthodes
private:
    void processEvents() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            else {
                _maPalette.processEvent(event);
            }
        }
    }

    void update() {

    }

    void render() {
        _window.clear();
        _maPalette.draw(_window);
        _window.display();
    }

public:
    Application() :
            _window(sf::VideoMode(800, 800), "It's Beautiful ! "),
            _maPalette()
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
