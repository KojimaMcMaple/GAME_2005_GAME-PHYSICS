#pragma once

#include "Globals.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Projectile : public DisplayObject
{
public:
	Projectile(glm::vec2 position = glm::vec2(0.0f, 0.0f), float speed = 0.0f);
	~Projectile();

	enum class ProjectileShape
	{
		SQUARE,
		TRIANGLE,
		CIRCLE
	};

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void changeShape(ProjectileShape shape);
	ProjectileShape getShape();

private:
	void startMoving(glm::vec2 position);

	glm::vec2 m_initialPosition;
	ProjectileShape m_currentShape;
	float m_speed;
};

