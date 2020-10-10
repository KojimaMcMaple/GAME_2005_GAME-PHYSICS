#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Background.h"
#include "Plane.h"
#include "Player.h"
#include "Target.h"
#include "Projectile.h"
#include "Button.h"
#include "Target.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void UpdateTargetRange(float new_range);
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

	// PHYSICS VARS
	float target_range = 485.0f;
	float throw_velocity = 95.0f;

};

#endif /* defined (__PLAY_SCENE__) */