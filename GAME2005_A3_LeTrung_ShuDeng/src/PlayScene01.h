#pragma once
#ifndef __PLAY_SCENE_01__
#define __PLAY_SCENE_01__

#include "Scene.h"
#include "Background.h"
#include "Plane.h"
#include "Player.h"
#include "BulletPool.h"
#include "Target.h"
#include "Projectile.h"
#include "Button.h"
#include "Target.h"
#include "Label.h"

class PlayScene01 : public Scene
{
public:
	PlayScene01();
	~PlayScene01();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void StartSimulation();
private:
	// IMGUI Function
	void GUI_Function();

	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Background* bkg_texture;
	Player* m_pPlayer;
	Target* m_pTarget;
	Projectile* m_pProjectile;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* no_active_bullet_label;
	Label* no_inactive_bullet_label;

	// PHYSICS VARS
	float ramp_height = 100.0f;
	float ramp_width = 100.0f;
	float ramp_theta;
	float friction_coefficient = 0.42f;

	SDL_Point m_points[4];

	bool m_touchedGround;
};

#endif /* defined (__PLAY_SCENE__) */