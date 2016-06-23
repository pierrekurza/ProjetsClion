#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <iostream>
#include <cassert>
#include "regular_language.hpp"

using namespace std;

class EventManager
{
// Attributs
private:
	RL* _my_ptr;

// Constructeurs et destructeur	(state initial et state final)
public:
	EventManager(RL* ptr) :
		_my_ptr(ptr)
	{}

	~EventManager()
	{
		_my_ptr = nullptr;
	}

// Requêtes
public:
	string readString() const
	{
		cout << "Entrer une chaîne de caracteres dans {a,b}: ";
		string chaine;
		cin >> chaine;
		return chaine;
	}

// Transformations
public:
	// Gestion des événements
	void processEvents()
	{
		assert(_my_ptr != nullptr);

		string s = "";
		bool stop = false;
		do
		{
			_my_ptr->init();

			s = readString();
			if(s == "quit")
				stop = true;
			else
				for(size_t i = 0; i < s.size(); i++)
				{
					_my_ptr->processEvent(s[i]);
				}

			cout << _my_ptr->getState() << endl;
		} while(!stop);
	}
};

#endif
