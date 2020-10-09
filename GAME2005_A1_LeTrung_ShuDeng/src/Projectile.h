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
private:
	float throw_angle;
	float travel_time;
};

