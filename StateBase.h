#pragma once

class Application;

class StateBase {
public:
	StateBase(Application* app, StateBase* parent = nullptr) :
		app(app), parent(parent)
	{}

	virtual ~StateBase() = default;

	virtual void update(float updateDeltaTime) = 0;
	virtual void render(float renderDeltaTime) = 0;

	virtual void onOpen() {}
	virtual void onClose() {}
	virtual void onLeave() {}
	virtual void onResume() {}

protected:
	Application* app;
	StateBase* parent;
};