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

	void StartSimulation();
private:
	// IMGUI Function
	void GUI_Function();

	// Lazy implementation of ramp
	void updateRamp();

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
	Label* velocity_x_label;
	Label* velocity_y_label;

	// PHYSICS VARS
	float ramp_height = 100.0f;
	float ramp_width = 100.0f;
	float ramp_theta;
	float friction_coefficient = 0.42f;

	SDL_Point m_points[4];

	bool m_touchedGround;
};

#endif /* defined (__PLAY_SCENE__) */