#include "StateStack.h"

StateStack::StateStack(Context context)
: m_context(context)
{
}

State::Ptr StateStack::createState(States::ID stateID) {

	auto found = m_factories.find(stateID);
	assert(found != m_factories.end());

	return found->second();

}

void StateStack::handleEvent(const sf::Event& event) {

	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {

		if (!(*itr)->handleEvent(event))
			return;

	}

	applyPendingChanges();

}

void StateStack::update(sf::Time dt) {

	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {

		if (!(*itr)->update(dt))
			break;

	}

	applyPendingChanges();

}

void StateStack::draw() {

	for (auto& state : m_stack) {
		state->draw();
	}

}

void StateStack::pushState(States::ID stateID) {
	m_pendingList.push_back(PendingChange(Push, stateID));
}
void StateStack::popState() {
	m_pendingList.push_back(PendingChange(Pop));
}
void StateStack::clearStack() {
	m_pendingList.push_back(PendingChange(Clear));
}
bool StateStack::isEmpty() const {
	return m_stack.size() == 0;
}

void StateStack::applyPendingChanges() {
	
	for (auto change : m_pendingList) {
		switch (change.action) {
		case Push:
			m_stack.push_back(createState(change.stateID));
			break;

		case Pop:
			m_stack.pop_back();
			break;

		case Clear:
			m_stack.clear();
			break;
		}
	}

	m_pendingList.clear();

}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{}