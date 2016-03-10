#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const float speed, const sf::Color& color, const sf::Time lifetime)
: m_position(centerPosition)
, m_speed(speed)
, m_color(color)
, m_lifetime(lifetime)
, m_scale(2.f, 2.f)
, m_isImageBased(false)
, m_context(context)
, m_texture(&m_context.textures->get(Textures::Default))
{
	// Set the primitive type
	m_va.setPrimitiveType(sf::Quads);
}

ParticleSystem::ParticleSystem(Context& context, const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale)
: m_speed(1.f)
, m_lifetime(sf::seconds(4.f))
, m_scale(scale)
, m_isImageBased(true)
, m_context(context) 
, m_texture(&m_context.textures->get(Textures::Default))
{
	// Set the primitive type
	m_va.setPrimitiveType(sf::Quads);

	// Loop through all pixels in the image and create a particle from each one

	for (int y = imageRect.top; y < imageRect.top + imageRect.height; y++) {

		for (int x = imageRect.left; x < imageRect.left + imageRect.width; x++) {

			// Get the color of the pixel
			sf::Color c = image.getPixel(x, y);
			
			// Only create particles from pixels that are visible (alpha > 0)
			if (c.a > 0u) {

				// Create the particle

				Particle particle;
				particle.color = c;
				particle.position.x = (x - imageRect.left) * scale.x + centerPosition.x - imageRect.width * scale.x / 2.f;
				particle.position.y = (y - imageRect.top) * scale.y + centerPosition.y - imageRect.height * scale.y / 2.f;
				//particle.velocity = sf::Vector2f(Utils::random(-.1f, .1f), Utils::random(-.2f, -.5f)); // Option 1, without collision detection, fast
				particle.velocity = sf::Vector2f(Utils::random(-.5f, .5f), Utils::random(-1.0f, -1.5f)); // Option 2, needs collision detection

				// Add the particle to the list
				m_particles.push_back(particle);

			}

		}

	}

	// Flag that the VA needs to update
	m_needsVAUpdate = true;

}

void ParticleSystem::update(sf::Time dt, const TileMap& map) {

	// Check if the system is not image based and therefore should emit new particles
	if (!m_isImageBased) {

		// Add 20 new particles
		for (int i = 0; i < 20; i++) {

			Particle particle;
			particle.color = m_color;
			particle.position = m_position;

			particle.velocity = sf::Vector2f( Utils::random(-1, 1), Utils::random(-1, 1));
			particle.velocity = Utils::normalize(particle.velocity);

			m_particles.push_back(particle);

		}

	}

	// Remove old particles
	while (!m_particles.empty() && m_particles.front().lifetime >= m_lifetime)
		m_particles.pop_front();

	// Update particles
	for (auto& p : m_particles) {

		// Increase the lifetime counter
		p.lifetime += dt;

		// Collision detection with map
		if (map.isPointColliding(p.position))
			// Particle has collided, dont move any more
			p.velocity = sf::Vector2f(.0f, .0f);
		else
			// Apply gravity
			p.velocity.y += 8.f * dt.asSeconds();

		// Update position from the velocity
		p.position += p.velocity;
		// Update the alpha value of the color to fade particles out
		p.color.a = sf::Uint8(std::max(255u - p.lifetime.asSeconds() / m_lifetime.asSeconds() * 255u, 0.f));

	}

	// Flag that the VA needs to update
	m_needsVAUpdate = true;

}

void ParticleSystem::updateVA() const {

	// Store half the size of the particles
	float halfSizeX = m_scale.x / 2.f;
	float halfSizeY = m_scale.y / 2.f;

	// Clear the VA
	m_va.clear();

	// Loop through all particles and add new vertices for each
	for (auto& p : m_particles) {

		m_va.append(sf::Vertex(sf::Vector2f(p.position.x - halfSizeX, p.position.y - halfSizeY), p.color));
		m_va.append(sf::Vertex(sf::Vector2f(p.position.x + halfSizeX, p.position.y - halfSizeY), p.color));
		m_va.append(sf::Vertex(sf::Vector2f(p.position.x + halfSizeX, p.position.y + halfSizeY), p.color));
		m_va.append(sf::Vertex(sf::Vector2f(p.position.x - halfSizeX, p.position.y + halfSizeY), p.color));

	}

}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Update the VA if needed
	if (m_needsVAUpdate) {
		updateVA();
		m_needsVAUpdate = false;
	}
	
	// Bind the texture and render
	states.texture = m_texture;
	target.draw(m_va, states);

}

bool ParticleSystem::shouldBeRemoved() const {
	return m_particles.size() == 0;
}
int ParticleSystem::getNumParticles() const {
	return m_particles.size();
}