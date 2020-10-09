#include <iostream>
using namespace std;

#include "Projectile.h"

Projectile::Projectile()
{
	TextureManager::Instance()->load("../Assets/textures/planet.png", "nade");

	const auto size = TextureManager::Instance()->getTextureSize("nade");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PROJECTILE);
	setEnabled(true);
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
	if (isEnabled()) {
		glm::vec2 velo = getRigidBody()->velocity;
		glm::vec2 pos = getTransform()->position;
		velo.x = initial_velocity * cos(throw_angle * Globals::sPi / 180.0f);
		velo.y = -initial_velocity * sin(throw_angle * Globals::sPi / 180.0f);

		cout << "velo.x = " << velo.x << endl;
		cout << "velo.y = " << velo.y << endl;

		pos.x += velo.x * Globals::sDeltaTime;
		pos.y += velo.y * Globals::sDeltaTime;

		cout << "pos.x = " << pos.x << endl;
		cout << "pos.y = " << pos.y << endl;

		getTransform()->position = pos;
	}

}

void Projectile::clean()
{
}

void Projectile::StartThrow(float velo, float angle)
{
	SetInitialVelocity(velo);
	SetThrowAngle(angle);
	setEnabled(true);
	//start ticks
}

void Projectile::SetThrowAngle(float angle)
{
	throw_angle = angle;
}

void Projectile::SetInitialVelocity(float velo)
{
	initial_velocity = velo;
}
