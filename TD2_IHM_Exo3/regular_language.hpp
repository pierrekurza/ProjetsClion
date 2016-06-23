#ifndef REGULAR_LANGUAGE_HPP
#define REGULAR_LANGUAGE_HPP

#include <iostream>
#include <cstdlib>
using namespace std;

class RL
{
public:
	enum class State
	{
		initial,
		middle,
		final
	};

private:
	State _my_state;

public:
	// Constructeurs et destructeur	(state initial et state final)
	RL()
	{
	}
	~RL()
	{}

// Requêtes (accès à l'état courant)
public:
	string getState()	const
	{
		string res;
		if(_my_state == State::initial)
			res = "Etat initial";
		else if(_my_state == State::middle)
			res = "Middle State -> Un seul A trouvé";
		else
			res = "Etat final -> AA ont été trouvés";
		return res;
	}

// Transformations
public:
	// Gestion d'événements
	void init()
	{
		_my_state = State::initial;
	}

	void processEvent(char e)
	{
		switch(e)
		{
			case 'a':
				if(_my_state == State::initial)
					_my_state = State::middle;
				else {
					_my_state = State::final;
					cout << getState() << endl;
					exit(2);
				}
				break;

			case 'b':
				_my_state == State::initial;
				break;

			default:
				break;
		}
	}

	// Operateur d'affichage <<
	friend ostream & operator <<(ostream & output, const RL& t)
	{
		output << t.getState() << endl;
		return output;
	}
};

#endif
