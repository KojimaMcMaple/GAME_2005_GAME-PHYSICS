#include <iostream>
using namespace std;

#include "Projectile.h"

Projectile::Projectile(glm::vec2 position, float speed)
{
	TextureManager::Instance()->load("../Assets/textures/nade.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = position;
	float initialVelocityDirection = rand() % 360 * float(M_PI) / 180.0f;
	getRigidBody()->velocity = speed * glm::vec2(cos(initialVelocityDirection), sin(initialVelocityDirection));
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



