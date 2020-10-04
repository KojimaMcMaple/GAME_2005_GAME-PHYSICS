#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"
#include "Util.h"

#include <iostream>
#include <algorithm>

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void StopMovingX();
	void StopMovingY();

	float GetDistance(GameObject* pGameObject);
	//float GetMagnitude();

private:
	//const float SPEED = 350.0f;
	const float ACCELERATION = 10.0f;
	const float DECELERATION = -10.0f;
	glm::vec2 move_direction;
};

#endif /* defined (__PLAYER__) */