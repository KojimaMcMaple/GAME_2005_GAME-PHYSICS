#pragma once
#include <vector>
#include "Bullet.h"
#include "Globals.h"
#include "CollisionManager.h"
#include "SoundManager.h"
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

	void Populate();
	void SpawnBullet();
	void DespawnBullet(Bullet* bullet_ptr, int bullet_idx);
	void CheckBulletCollision(GameObject* checking_obj);

	int GetSizeActiveBulletList();
	int GetSizeInactiveBulletList();

	void SetSpawnMode(int mode);

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

	int spawn_mode = 0;
};

