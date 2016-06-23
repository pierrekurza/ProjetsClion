#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP
#include <cstdlib>
#include <cassert>
#include <iostream>
#include "event.hpp"
#include "turnstile.hpp"
using namespace std;

class EventManager
{
// Attributs
private:
    Turnstile* _my_ptr;

// Constructeurs et destructeur	(state initial et state final)
public:
    EventManager(Turnstile* ptr) :
        _my_ptr(ptr)
    {}

    ~EventManager()
    {
        _my_ptr = nullptr;
    }

// Requêtes
public:
    Event getKeyboardEvent() const
    {
        cout << "Entrer un caractere: ";
        char key;
        cin >> key;

        Event e = Event::end;
        switch(key)
        {
            case 'c':
            e = Event::coin;
            break;

            case 'p':
            e = Event::pass;
            break;

            case 'r':
            e = Event::reset;
            break;

            default:
            exit(1);
            break;
        }
        return e;
    }

// Transformations
public:
    // Gestion des événements
    void processEvents()
    {
        assert(_my_ptr != nullptr);

        Event e = Event::end;
        do
        {
            e = getKeyboardEvent();
            _my_ptr->processEvent(e);
        }
        while(e != Event::end);
    }
};
#endif
