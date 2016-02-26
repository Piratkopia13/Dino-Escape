#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <cassert>

#include "../Common.h"
#include "State.h"
#include "StateIdentifiers.h"

class StateStack {

	public:
		enum Action {
			Push,
			Pop,
			Clear
		};

	public:
		StateStack(Context context);

		template <typename T>
		void registerState(States::ID stateID);

		void handleEvent(const sf::Event& event);
		void update(sf::Time dt);
		void draw();

		void pushState(States::ID stateID);
		void popState();
		void clearStack();

		bool isEmpty() const;

	private:
		State::Ptr createState(States::ID stateID);
		void applyPendingChanges();

	private:
		struct PendingChange {
			PendingChange(Action action, States::ID stateID = States::None);

			Action action;
			States::ID stateID;
		};

	private:
		std::vector<State::Ptr> m_stack;
		std::vector<PendingChange> m_pendingList;
		Context m_context;
		std::map<States::ID, std::function<State::Ptr()>> m_factories;


};

template <typename T>
void StateStack::registerState(States::ID stateID) {
	
	m_factories[stateID] = [this]() {
		return State::Ptr(new T(*this, m_context));
	};

}