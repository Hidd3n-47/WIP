#pragma once

namespace jci {

class IStateMachine;

class StateMachineManager
{
public:
	inline static StateMachineManager* Instance() { return m_instance == nullptr ? m_instance = new StateMachineManager() : m_instance; }

	void Update(float dt);

	inline void RegisterStateMachine(IStateMachine* stateMachine)	{ m_stateMachines.push_back(stateMachine); }
	inline void DeregisterStateMachine(IStateMachine* stateMachine) { Utils::RemoveFromVectorByBackCopy(stateMachine, m_stateMachines); }
private:
	StateMachineManager()	= default;
	~StateMachineManager()	= default;

	static StateMachineManager* m_instance;

	std::vector<IStateMachine*> m_stateMachines;
};

} // Namespace jci.