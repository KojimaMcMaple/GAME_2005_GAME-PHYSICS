#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Background.h"
#include "Projectile.h"
#include "Button.h"
#include "Brick.h"
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

private:
	// IMGUI Function
	void GUI_Function();

	void solveBoundaryCollision();
	void solveBrickCollision();
	void solveBrickCollisionY();
	void solveBrickCollisionX();

	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Background* bkg_texture;
	Brick* m_pPlayerBrick;
	Projectile* m_pBall;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	float m_dampingFactorNormal = 0.7f;
	float m_dampingFactorTangent = 1.0f;
	float m_amplifyingFactorTangent = 0.5f;
	float m_amplifyingFactorNormal = 1.3f;
};

#endif /* defined (__PLAY_SCENE__) */