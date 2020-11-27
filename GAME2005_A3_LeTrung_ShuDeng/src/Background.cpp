#include "Background.h"

Background::Background()
{
	TextureManager::Instance()->load("../Assets/textures/main_background.jpg", "main_background");

	const auto size = TextureManager::Instance()->getTextureSize("main_background");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0.0f, 0.0f);

	setType(BKG);
}

Background::~Background() = default;

void Background::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("main_background", x, y, 0, 255, false);
}

void Background::update()
{
}

void Background::clean()
{
}
