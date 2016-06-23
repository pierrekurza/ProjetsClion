#include "event_manager.hpp"

int main()
{
	RL rl;
	EventManager mgr(&rl);
	mgr.processEvents();
}
