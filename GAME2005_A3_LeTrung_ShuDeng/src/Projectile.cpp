#include <iostream>
using namespace std;

#include "Projectile.h"
#include "CollisionManager.h"

Projectile::Projectile(glm::vec2 position, float speed)
{
	TextureManager::Instance()->load("../Assets/textures/planet.png", "circle");
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "triangle");
	TextureManager::Instance()->load("../Assets/textures/square.png", "square");

	m_initialPosition = position;
	m_speed = speed;
	changeShape(ProjectileShape::CIRCLE);

	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(true);
}

Projectile::~Projectile() = default;

void Projectile::draw()
{
	if (isEnabled()) 
	{
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the target
		switch (m_currentShape)
		{
		case ProjectileShape::CIRCLE:
			TextureManager::Instance()->draw("circle", x, y, 0, 255, false);
			break;
		case ProjectileShape::SQUARE:
			TextureManager::Instance()->draw("square", x, y, 0, 255, false);
			break;
		case ProjectileShape::TRIANGLE:
			TextureManager::Instance()->draw("triangle", x, y, 0, 255, false);
			break;
		}	
	}
}

void Projectile::update()
{
	if (isEnabled()) {

		getRigidBody()->velocity += getRigidBody()->acceleration * Globals::sDeltaTime;

		/*cout << "velo.x = " << getRigidBody()->velocity.x << endl;
		cout << "velo.y = " << getRigidBody()->velocity.y << endl;*/

		getTransform()->position += getRigidBody()->velocity * Globals::sDeltaTime;

		/*cout << "pos.x = " << getTransform()->position.x << endl;
		cout << "pos.y = " << getTransform()->position.y << endl;*/
	}
}

void Projectile::clean()
{

}

void Projectile::changeShape(ProjectileShape shape)
{
	glm::vec2 size;
	switch (shape)
	{
	case ProjectileShape::CIRCLE:
		m_currentShape = ProjectileShape::CIRCLE;
		size = TextureManager::Instance()->getTextureSize("circle");
		break;
	case ProjectileShape::SQUARE:
		m_currentShape = ProjectileShape::SQUARE;
		size = TextureManager::Instance()->getTextureSize("square");
		break;
	case ProjectileShape::TRIANGLE:
		m_currentShape = ProjectileShape::TRIANGLE;
		size = TextureManager::Instance()->getTextureSize("triangle");
		break;
	}

	setWidth(size.x);
	setHeight(size.y);	
	startMoving(m_initialPosition);
}

Projectile::ProjectileShape Projectile::getShape()
{
	return m_currentShape;
}

void Projectile::startMoving(glm::vec2 position)
{
	getTransform()->position = position;
	float initialVelocityDirection = rand() % 360 * float(M_PI) / 180.0f;
	getRigidBody()->velocity = m_speed * glm::vec2(cos(initialVelocityDirection), sin(initialVelocityDirection));
}



