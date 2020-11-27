#pragma once

#include "Globals.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Bullet : public DisplayObject
{
public:
	Bullet();
	Bullet(glm::vec2 pos);
	~Bullet();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
private:

};

