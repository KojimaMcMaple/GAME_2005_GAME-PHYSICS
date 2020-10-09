#include "Projectile.h"

Projectile::Projectile()
{
	TextureManager::Instance()->load("../Assets/textures/nade.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0.0f, 0.0f);

	setType(PROJECTILE);

	getTransform()->position = glm::vec2(0.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setEnabled(false);
}

Projectile::~Projectile() = default;

void Projectile::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("nade", x, y, 0, 255, false);
}

void Projectile::update()
{
	if (isEnabled() && !getRigidBody()->isColliding) {

	}

}

void Projectile::clean()
{
}
