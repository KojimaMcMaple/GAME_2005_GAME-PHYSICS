#include "BulletPool.h"

BulletPool* BulletPool::kInstance = nullptr;

BulletPool::BulletPool() {
	active_bullet_list.reserve(pool_size);
	inactive_bullet_list.reserve(pool_size);

	for (int i = 0; i < pool_size; i++) {
		inactive_bullet_list.push_back(new Bullet());
	}
}

BulletPool::~BulletPool()
= default;



void BulletPool::Draw()
{
}

void BulletPool::Update()
{
	if (inactive_bullet_list.size() > 0) {

	}
}

void BulletPool::Clean()
{
}
