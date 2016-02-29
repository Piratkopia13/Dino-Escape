#pragma once

#include <deque>

#include "Common.h"
#include "game\world\TileMap.h"

struct Particle {
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	sf::Time lifetime;

};

class ParticleSystem : public sf::Drawable {

	public:
		ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const float speed, const sf::Color& color, const sf::Time lifetime);
		ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale);
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time dt, const TileMap& map);

		bool shouldBeRemoved() const;
		int getNumParticles() const;

	private:
		void updateVA() const;

	private:
		sf::Color m_color;
		sf::Time m_lifetime;
		sf::Vector2f m_position;
		float m_speed;
		sf::Vector2f m_scale;

		Context& m_context;
		const sf::Texture* m_texture;

		std::deque<Particle> m_particles;

		mutable sf::VertexArray m_va;
		mutable bool m_needsVAUpdate;

		bool m_isImageBased;

};