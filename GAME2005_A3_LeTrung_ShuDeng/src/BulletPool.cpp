#include "BulletPool.h"

BulletPool* BulletPool::kInstance = nullptr;

BulletPool::BulletPool() 
= default;

BulletPool::~BulletPool()
= default;

void BulletPool::Populate() {
	active_bullet_list.reserve(pool_size);
	inactive_bullet_list.reserve(pool_size);

	for (int i = 0; i < pool_size; i++) {
		inactive_bullet_list.push_back(new Bullet());
	}
}

void BulletPool::SpawnBullet()
{
	Bullet* bullet_ptr = nullptr;
	if (inactive_bullet_list.size() > 0) {
		bullet_ptr = inactive_bullet_list.back();
		bullet_ptr->SpawnAtRandomX();
		inactive_bullet_list.pop_back();
		active_bullet_list.push_back(bullet_ptr);
	}
}

void BulletPool::DespawnBullet(Bullet* bullet_ptr, int bullet_idx)
{
	bullet_ptr->Reset();
	active_bullet_list.erase(active_bullet_list.begin() + bullet_idx); //erase the i-th element
	inactive_bullet_list.push_back(bullet_ptr);
}

void BulletPool::Draw()
{
	if (active_bullet_list.size() > 0)
	{
		for (it = active_bullet_list.begin(); it != active_bullet_list.end(); it++) {
			(*it)->draw();
		}
	}
}

void BulletPool::Update()
{
	SpawnBullet();

	if (active_bullet_list.size() > 0)
	{
		int i = 0;
		for (it = active_bullet_list.begin(); it != active_bullet_list.end(); it++, i++) {
			(*it)->update();

			if ((*it)->getTransform()->position.y > (Globals::kWindowHeight + (*it)->texture_size.y)) { //out of bound
				DespawnBullet(*it, i);
				break; //continuing will cause runtime error (delete while iterating)
			}
		}
	}
}

void BulletPool::Clean()
{
}
