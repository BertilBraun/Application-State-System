#include "Application.h"

#include "Timer.h"

bool Application::updateState(int updatesPerSec)
{
	static Timer timer;
	static float elapsedTime = 0;

	float timePerUpdate = 1.0f / updatesPerSec;
	elapsedTime += fmin((float)timer.elapsed(), 0.15f);
	timer.reset();

	auto& state = *m_States.top();

	bool shouldRender = false;
	while (elapsedTime >= timePerUpdate) {

		// poll Input

		state.update(timePerUpdate);

		elapsedTime -= timePerUpdate;
		shouldRender = true;

		if (m_PopAllStates) {

			m_PopAllStates = false;

			for (int i = 0; i <= m_States.size(); i++) {
				state.onClose();
				m_States.pop();
			}

			if (!m_States.empty()) {
				state = *m_States.top();
				state.onResume();
			}

			break;
		}
		else if (m_PopState) {

			m_PopState = false;
			state.onClose();
			m_States.pop();

			if (!m_States.empty()) {
				state = *m_States.top();
				state.onResume();
			}

			break;
		}
	}	

	return shouldRender;
}

void Application::renderState()
{
	Timer renderTimer;
	
	if (!m_States.empty()) {

		float deltaTime = fmin((float)renderTimer.elapsed(), 0.15f);

		m_States.top()->render(deltaTime);
		
		renderTimer.reset();

		// swap buffers
	}
}
