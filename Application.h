#pragma once

#include <stack>
#include <memory>

#include "StateBase.h"

class Application {
public:
	Application() {}

	// returns whether Update happened and so if rendering is nescessary
	bool updateState(int updatesPerSec);
	void renderState();

	template<typename T, typename... Args>
	void pushState(Args&& ... args);

	inline void popState() { m_PopState = true; }
	inline void popAllStates() { m_PopAllStates = true; }

	inline StateBase& getState() { return *m_States.top(); }

private:
	std::stack<std::unique_ptr<StateBase>> m_States;
	bool m_PopState = false, m_PopAllStates = false;
};

template<typename T, typename ...Args>
inline void Application::pushState(Args&& ...args)
{
	if (m_States.size() != 0)
		m_States.top()->onLeave();
	m_States.emplace(std::make_unique<T>(this, std::forward<Args>(args)...));
	m_States.top()->onOpen();
}