#include "StateStack.h"

StateStack::StateStack(Context context)
: m_context(context)
{
}

State::Ptr StateStack::createState(States::ID stateID) {

	// Get the initializer function for the specified id
	auto found = m_factories.find(stateID);
	// A function should always exist, assert otherwise
	assert(found != m_factories.end());

	// Return the pointer to the newly initiated state
	return found->second();

}

void StateStack::handleEvent(const sf::Event& event) {

	// Loop through the stack reversed
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {

		// Return if a state returns false
		// This allows states to stop underlying states from handling events
		if (!(*itr)->handleEvent(event))
			break;

	}

	// Loop done, we can now modify the stack
	applyPendingChanges();

}

void StateStack::update(sf::Time dt) {

	// Loop through the stack reversed
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr) {

		// Return if a state returns false
		// This allows states to stop underlying states from updating
		if (!(*itr)->update(dt))
			break;

	}

	// Loop done, we can now modify the stack
	applyPendingChanges();

}

void StateStack::draw() {

	// Loop through the states and draw them all
	for (auto& state : m_stack)
		state->draw();

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
	
	// Perform something depending on the action
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

	// All changes applied, clear the list
	m_pendingList.clear();

}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{}