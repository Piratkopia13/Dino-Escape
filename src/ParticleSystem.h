#pragma once

#include <deque>

#include "Common.h"
#include "game\world\TileMap.h"

// Struct with data for every particle
struct Particle {
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	sf::Time lifetime;

};

class ParticleSystem : public sf::Drawable {

	public:
		// Constructor to initialize the particle system as a continuous particle emitter
		ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const float speed, const sf::Color& color, const sf::Time lifetime);
		// Constructor to initalize the particle system from an image
		ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale);
		
		// Draws the particles
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		// Updates the particles
		// TileMap reference is used to check particle collisions
		void update(sf::Time dt, const TileMap& map);

		// Returns wheather or not the particle system has no more particles and should be removed
		bool shouldBeRemoved() const;
		// Returns how many particles the system has
		int getNumParticles() const;

	private:
		// Updates the vertex array
		void updateVA() const;

	private:
		// Data that all new particles emitted should get
		sf::Color m_color;
		sf::Time m_lifetime;
		sf::Vector2f m_position;
		sf::Vector2f m_scale;
		float m_speed;

		// Reference to the context
		Context& m_context;
		// Texture to be used while rendering
		// Is only used to allow custom shaders
		const sf::Texture* m_texture;

		// a double-ended queue of particles
		// A std::deque is used to allow efficient removal and appending of particles
		std::deque<Particle> m_particles;

		// The vertex array with all the rendering information
		// Mutable since it's not part of the object's logical state
		mutable sf::VertexArray m_va;
		// A flag marking if the system needs to update the vertex array
		// Mutable since it's not part of the object's logical state
		mutable bool m_needsVAUpdate;

		// Whether or not the system is constructed from an image or not
		bool m_isImageBased;

};