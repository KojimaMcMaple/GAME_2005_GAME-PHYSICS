#pragma once

#include "Globals.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Projectile : public DisplayObject
{
public:
	Projectile(glm::vec2 pos = glm::vec2(0.0f, 0.0f));
	~Projectile();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void reset(glm::vec2 pos);
	void stop();

private:
	float travel_time;
};

