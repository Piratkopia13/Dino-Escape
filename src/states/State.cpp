#include "State.h"
#include "StateStack.h"

Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, LevelManager& levels, MusicPlayer& music, SoundPlayer& sounds, PostEffectManager& shaders)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, levels(&levels)
, music(&music)
, sounds(&sounds)
, shaders(&shaders)
{ }

State::State(StateStack& stack, Context& context) 
:  m_stack(&stack)
, m_context(context)
{

}

State::~State() {
}

void State::requestStackPush(States::ID stateID) {
	m_stack->pushState(stateID);
}
void State::requestStackPop() {
	m_stack->popState();
}
void State::requestStackClear() {
	m_stack->clearStack();
}

Context& State::getContext() {
	return m_context;
}