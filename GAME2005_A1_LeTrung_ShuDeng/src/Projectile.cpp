#include <iostream>
using namespace std;

#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos = glm::vec2(0.0f, 400.0f))
{
	TextureManager::Instance()->load("../Assets/textures/planet.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(false);
}

<<<<<<< HEAD
Projectile::Projectile(glm::vec2 pos)
{
	TextureManager::Instance()->load("../Assets/textures/planet.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(false);
}

=======
>>>>>>> deeaac4088c7bdc3cd068a5ff5a5f30157877a7c
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

void Projectile::StartThrow(float velo, float range)
{
	SetInitialVelocity(velo);
	CalculateThrowAngle(velo, range);
	setEnabled(true);
	//start ticks

	getRigidBody()->velocity.x = initial_velocity * cos(throw_angle * Globals::sPi / 180.0f);
	getRigidBody()->velocity.y = -initial_velocity * sin(throw_angle * Globals::sPi / 180.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8);
}

void Projectile::Stop()
{
	getRigidBody()->acceleration = glm::vec2(0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f);
}

void Projectile::CalculateThrowAngle(float velo, float range)
{
	SetThrowAngle((asin(range * Globals::sGravity / (velo * velo)) / 2) * 180.0f / Globals::sPi);
	//cout << "throw_angle = " << throw_angle;
}

void Projectile::SetThrowAngle(float angle)
{
	throw_angle = angle;
}

void Projectile::SetInitialVelocity(float velo)
{
	initial_velocity = velo;
}

float Projectile::GetThrowAngle()
{
	return throw_angle;
}
