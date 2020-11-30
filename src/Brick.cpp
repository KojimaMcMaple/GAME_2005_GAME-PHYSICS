#include "Brick.h"
#include "Globals.h"
#include "TextureManager.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/startButton.png", "wookiee");

	const auto size = TextureManager::Instance()->getTextureSize("wookiee");
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

	TextureManager::Instance()->draw("wookiee", x, y, 0, 255, false);
}

void Brick::update()
{
	getRigidBody()->velocity = (getTransform()->position - m_previousPos) / Globals::sDeltaTime;
	m_previousPos = getTransform()->position;
}

void Brick::clean()
{
}
