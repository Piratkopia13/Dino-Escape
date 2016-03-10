#pragma once

#include <map>
#include <memory>

#include "Common.h"

// Owns and distributes shader resources
class PostEffectManager {

public:
	PostEffectManager();

	// Returns a shader reference by id
	sf::Shader& get(PostEffects::ID id);

	// Forces a shader reload on the next get() call. This will invalidate all old references stored.
	void reload();

private:
	// Loads the shader from the disk
	sf::Shader& load(PostEffects::ID id);

private:
	// sf::Shader mapped by the PostEffects::ID identifier
	std::map<PostEffects::ID, std::unique_ptr<sf::Shader>> m_shaderMap;
	// Shader filenames [vertex, fragment] on disk mapped by the PostEffects::ID identifier
	std::map<PostEffects::ID, std::pair<std::string, std::string>> m_filenameMap;

};
