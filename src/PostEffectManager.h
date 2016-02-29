#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class PostEffectManager {

public:
	PostEffectManager();
	~PostEffectManager();

	sf::Shader& get(PostEffects::ID id);

	void reload();

private:
	sf::Shader& load(PostEffects::ID id);

private:
	std::map<PostEffects::ID, std::unique_ptr<sf::Shader>> m_shaderMap;
	std::map<PostEffects::ID, std::pair<std::string, std::string>> m_filenameMap;

};
