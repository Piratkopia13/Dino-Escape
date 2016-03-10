#include "PostEffectManager.h"

PostEffectManager::PostEffectManager() {

	// Map filenames to IDs
	m_filenameMap.insert({ PostEffects::ID::Vignette, {"res/shaders/vignette.vert", "res/shaders/vignette.frag"} });

}

void PostEffectManager::reload() {
	m_shaderMap.clear();
}

sf::Shader& PostEffectManager::get(PostEffects::ID id) {

	auto shader = m_shaderMap.find(id);

	// Check if the shader has not yet been loaded
	if (shader == m_shaderMap.end())
		// Load and return
		return load(id);
	else
		// Return loaded shader
		return *shader->second;

}

sf::Shader& PostEffectManager::load(PostEffects::ID id) {

	std::unique_ptr<sf::Shader> shader(new sf::Shader());

	auto& filenames = m_filenameMap.find(id)->second;

	// Check if the load failed
	if (!shader->loadFromFile(filenames.first, sf::Shader::Vertex))
		throw std::logic_error("Failed to load vertex shader: " + filenames.first);

	// Check if the load failed
	if (!shader->loadFromFile(filenames.second, sf::Shader::Fragment))
		throw std::logic_error("Failed to load fragment shader: " + filenames.second);

	// Insert and return shader reference
	auto insertedPair = m_shaderMap.insert(std::make_pair(id, std::move(shader)));
	return *insertedPair.first->second;
}
