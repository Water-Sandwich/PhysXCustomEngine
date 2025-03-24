#include "Listener.h"
#include "InputHandler.h"

Listener::Listener() {
	InputHandler::listeners.push_back(this);
	//std::sort(InputHandler::listeners.begin(), InputHandler::listeners.end());
	//InputHandler::listeners.erase(std::unique(InputHandler::listeners.begin(), InputHandler::listeners.end()), InputHandler::listeners.end());
}

Listener::~Listener() {
	if(InputHandler::listeners.size() != 0)
		InputHandler::listeners.erase(std::find(InputHandler::listeners.begin(), InputHandler::listeners.end(), this));
}