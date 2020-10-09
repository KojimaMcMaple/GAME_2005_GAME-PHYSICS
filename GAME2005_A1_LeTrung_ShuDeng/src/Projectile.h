#pragma once

#include "Globals.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Projectile : public DisplayObject
{
public:
	Projectile();
	~Projectile();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void StartThrow(float velo, float angle);

	void SetThrowAngle(float angle);
	void SetInitialVelocity(float velo);
private:
	float throw_angle;
	float travel_time;
	float initial_velocity;
};

