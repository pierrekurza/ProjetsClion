#include "event_manager.hpp"

int main()
{
    Turnstile t;
    EventManager mgr(&t);
    mgr.processEvents();
}
