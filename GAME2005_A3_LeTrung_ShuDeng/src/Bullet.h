#pragma once

#include "Globals.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Bullet : public DisplayObject
{
	friend class BulletPool; //You can ensure that the objects can only be created by the pool. 
							//In C++, a simple way to do this is to make the pool class a friend of the object class 
							//and then make the object’s constructor private.

public:
	

private:
	Bullet();
	Bullet(int x_pos);
	Bullet(glm::vec2 pos);
	~Bullet();

	void SetXPos(int x_pos);
	void AccelerateYAtDefaultSpeed();
	void AccelerateYAtRandomSpeed();
	void SpawnAtRandomX(int mode);
	void Reset();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	glm::vec2 texture_size;
	float acceleration_speed = 80.0f;
	float max_acceleration_speed = 160.0f;
	bool is_in_use = false;
};