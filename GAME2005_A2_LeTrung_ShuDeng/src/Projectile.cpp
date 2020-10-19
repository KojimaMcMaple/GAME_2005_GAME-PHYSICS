#include <iostream>
using namespace std;

#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos)
{
	TextureManager::Instance()->load("../Assets/textures/nade.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(true);
}

Projectile::~Projectile() = default;

void Projectile::draw()
{
	if (isEnabled()) {
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the target
		TextureManager::Instance()->draw("nade", x, y, 0, 255, false);
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

void Projectile::reset(glm::vec2 pos)
{
	getTransform()->position = pos;
	stop();
}

void Projectile::stop()
{
	getRigidBody()->acceleration = glm::vec2(0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f);
}


