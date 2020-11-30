#pragma once
#include "DisplayObject.h"
class Brick :
    public DisplayObject
{
public:
    Brick();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	glm::vec2 m_previousPos;

};

