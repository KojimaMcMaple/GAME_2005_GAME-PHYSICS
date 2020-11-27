#include "Bullet.h"

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/bullet_laser.png", "bullet_laser");

	const auto size = TextureManager::Instance()->getTextureSize("bullet_laser");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(true);
}

Bullet::Bullet(glm::vec2 pos)
{
	TextureManager::Instance()->load("../Assets/textures/bullet_laser.png", "bullet_laser");

	const auto size = TextureManager::Instance()->getTextureSize("bullet_laser");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(true);
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	if (isEnabled()) {
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the target
		TextureManager::Instance()->draw("bullet_laser", x, y, 0, 255, false);
	}
}

void Bullet::update()
{
}

void Bullet::clean()
{
}
