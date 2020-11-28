#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"
#include "Util.h"
#include "Globals.h"

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

	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();

	PlayerAnimationState m_currentAnimationState;

	const float acceleration_speed = 10.0f;
	const float deceleration_speed = -25.0f;
	glm::vec2 move_direction;
};

#endif /* defined (__PLAYER__) */