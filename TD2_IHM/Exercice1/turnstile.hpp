#ifndef TURNSTILE_HPP
#define TURNSTILE_HPP

#include <iostream>
#include "event.hpp"
using namespace std;


class Turnstile
{
public:
    enum class State
    {
        alarmed,
        locked,
        unlocked
    };

private:
    State _my_state;

public:
// Constructeurs et destructeur	(etat initial et etat final)
    Turnstile() :
        _my_state(State::locked)
    {}

    ~Turnstile()
    {}

// Requêtes (accès à l'état courant)
public:
    string getState()	const
    {
        string res;
        if(_my_state == State::locked)
            res = "C'est bloqué ! ";
        else if( _my_state == State::alarmed)
            res = "Alarme";
        else
            res = "C'est vérouillé ! ";
        return res;
    }

// Transformations
public:
    // Gestion d'événements
    void processEvent(const Event& e)
    {
        switch(e)
        {
            case (Event::coin):
                unlock();
                break;

            case (Event::pass):
                if(_my_state == State::locked)
                    lock();
                else
                    alarm();
                break;

            case (Event::reset):
                lock();

            default:
                break;
        }
        cout << getState() << endl;
    }

    // Actions
    void lock()
    {
        _my_state = State::locked;
    }

    void unlock()
    {
        _my_state = State::unlocked;
    }

    void alarm()
    {
        _my_state = State::alarmed;
    }

    // Operateur d'affichage <<
    friend ostream & operator <<(ostream & output, const Turnstile& t)
    {
        output << t.getState() << endl;
        return output;
    }
};
#endif
