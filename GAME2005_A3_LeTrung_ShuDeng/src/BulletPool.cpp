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

	SoundManager::Instance().load("../Assets/audio/laser_hit.wav", "laser_hit", SOUND_SFX);
}

void BulletPool::SpawnBullet()
{
	Bullet* bullet_ptr = nullptr;
	if (!inactive_bullet_list.empty()) {
		bullet_ptr = inactive_bullet_list.back();
		bullet_ptr->SpawnAtRandomX(spawn_mode);
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

void BulletPool::CheckBulletCollision(GameObject* checking_obj)
{
	if (!active_bullet_list.empty())
	{
		for (vector<Bullet*>::iterator it = active_bullet_list.begin(); it != active_bullet_list.end(); it++) {
			if (CollisionManager::AABBCheck((*it), checking_obj)) {
				if ((*it)->getRigidBody()->isColliding == false) {
					(*it)->getRigidBody()->isColliding = true;
					SoundManager::Instance().playSound("laser_hit");
				}
			}
			else {
				(*it)->getRigidBody()->isColliding = false;
			}
		}
	}
}

int BulletPool::GetSizeActiveBulletList()
{
	return active_bullet_list.size();
}

int BulletPool::GetSizeInactiveBulletList()
{
	return inactive_bullet_list.size();
}

void BulletPool::SetSpawnMode(int mode)
{
	spawn_mode = mode;
}

void BulletPool::Draw()
{
	if (!active_bullet_list.empty())
	{
		for (vector<Bullet*>::iterator it = active_bullet_list.begin(); it != active_bullet_list.end(); it++) {
			(*it)->draw();
		}
	}
}

void BulletPool::Update()
{
	SpawnBullet();

	if (!active_bullet_list.empty())
	{
		int i = 0;
		for (vector<Bullet*>::iterator it = active_bullet_list.begin(); it != active_bullet_list.end(); it++, i++) {
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
	for (auto& i : active_bullet_list) {
		delete i;
		i = nullptr;
	}
	active_bullet_list.clear();

	for (auto& i : inactive_bullet_list) {
		delete i;
		i = nullptr;
	}
	inactive_bullet_list.clear();
}
