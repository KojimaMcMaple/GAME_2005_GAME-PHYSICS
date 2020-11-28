#pragma once
#include <vector>
#include "Bullet.h"
using namespace std;

class BulletPool
{
public:
	static BulletPool* Instance()
	{
		if (kInstance == nullptr)
		{
			kInstance = new BulletPool();
		}
		return kInstance;
	}

	void Draw();
	void Update();
	void Clean();

private:
	BulletPool();
	~BulletPool();
	static BulletPool* kInstance;

	int pool_size = 10;
	vector<Bullet*> active_bullet_list;
	vector<Bullet*> inactive_bullet_list;
	vector<Bullet*>::iterator it;
};

