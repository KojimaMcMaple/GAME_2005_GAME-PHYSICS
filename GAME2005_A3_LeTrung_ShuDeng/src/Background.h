#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Background : public DisplayObject
{
public:
	Background();
	~Background();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};

