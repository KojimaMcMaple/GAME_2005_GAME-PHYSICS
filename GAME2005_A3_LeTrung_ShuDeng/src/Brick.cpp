#include "Brick.h"
#include "Globals.h"
#include "TextureManager.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/brick.jpg", "brick");

	const auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(50.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(PLAYER);
}

void Brick::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("brick", x, y, 0, 255, false);
}

void Brick::update()
{
	getRigidBody()->velocity = (getTransform()->position - m_previousPos) / Globals::sDeltaTime;
	m_previousPos = getTransform()->position;
}

void Brick::clean()
{
}
