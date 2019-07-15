
#include <iostream>

#include "Application.h"

class State : public StateBase {
public:
	State(Application* app, int i, char c) :
		StateBase(app)
	{

		std::cout << "Initialising " << i << " " << c << std::endl;

	}

	virtual void update(float updateDeltaTime) override {

		std::cout << "Updating " << updateDeltaTime << std::endl;

	}

	virtual void render(float renderDeltaTime) override {

		std::cout << "Rendering " << renderDeltaTime << std::endl;

	}

};

void main() {
	
	Application app;

	app.pushState<State>(1, 'c');

	while (true) 
		if (app.updateState(60))
			app.renderState();

}
