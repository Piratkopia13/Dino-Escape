#include "PostEffectManager.h"

PostEffectManager::PostEffectManager() {

	m_filenameMap.insert({ PostEffects::ID::Vignette, {"res/shaders/vignette.vert", "res/shaders/vignette.frag"} });

}

PostEffectManager::~PostEffectManager() {
}

void PostEffectManager::reload() {
	m_shaderMap.clear();
}

sf::Shader& PostEffectManager::get(PostEffects::ID id) {

	int size = m_shaderMap.size();

	auto shader = m_shaderMap.find(id);

	if (shader == m_shaderMap.end()) // Shader not yet loaded
		return load(id); // Load and return
	else // Shader already loaded
		return *shader->second; // Return loaded shader

}

sf::Shader& PostEffectManager::load(PostEffects::ID id) {

	std::unique_ptr<sf::Shader> shader(new sf::Shader());

	auto& filenames = m_filenameMap.find(id)->second;

	if (!shader->loadFromFile(filenames.first, sf::Shader::Vertex))
		//throw new std::exception(std::string("Failed to load vertex shader: " + filenames.first).c_str());
		throw std::runtime_error("Failed to load vertex shader: " + filenames.first);
	if (!shader->loadFromFile(filenames.second, sf::Shader::Fragment))
		//throw new std::exception("Failed to load fragment shader: " + filenames.second);
		throw std::runtime_error("Failed to load fragment shader: " + filenames.second);

	// Insert and return shader reference
	m_shaderMap.insert(std::make_pair(id, std::move(shader)));

	auto t = m_shaderMap.find(id);
	return *t->second;
}
